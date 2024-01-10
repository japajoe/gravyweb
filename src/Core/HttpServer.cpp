#include "HttpServer.hpp"
#include "HttpSettings.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "MemoryStream.hpp"
#include "StringUtility.hpp"
#include "Console.hpp"
#include <memory>
#include <future>
#include <signal.h>

static void HandleSignal(int signum)
{
    if(signum == SIGINT)
    {
        gravy_tcp_library_uninit();
        exit(signum);
    }
    else if (signum == SIGPIPE) 
    {
        std::cout << "Unable to write data to the transport connection: Broken pipe\n";
    }
}

HttpServer::HttpServer(const HttpConfig &config)
{
    if(config.useHttps)
    {
        if(!File::Exists(config.certificatePath))
        {
            std::cout << "Certificate file not found: " << config.certificatePath << '\n';
            exit(1);
        }

        if(!File::Exists(config.privateKeyPath))
        {
            std::cout << "Private key file not found: " << config.privateKeyPath << '\n';
            exit(1);
        }
    }

    if(!Directory::Exists(config.privateHtml))
    {
        std::cout << "Private html directory does not exist: " << config.privateHtml << '\n';
        exit(1);
    }

    if(!Directory::Exists(config.publicHtml))
    {
        std::cout << "Public html directory does not exist: " << config.publicHtml << '\n';
        exit(1);
    }

    //Needed to handle an interrupt request and shut down the library
    if (signal(SIGINT, HandleSignal) == SIG_ERR) 
    {
        std::cout << "Error setting up SIGINT handler\n";
        exit(1);
    }

    //Needed to handle a broken pipe signal, otherwise the program just closes
    //Disconnected sockets can cause this signal to be fired so we must capture it
    if (signal(SIGPIPE, HandleSignal) == SIG_ERR)
    {
        std::cout << "Error setting up SIGPIPE handler\n";
        exit(1);
    }

    gravy_tcp_library_init();

    HttpSettings::LoadFromConfig(config);
}

void HttpServer::Run()
{
    isRunning = true;

    auto task1 = std::async(std::launch::async, &HttpServer::HandleHttp, this);
    if(HttpSettings::GetUseHttps())
        auto task2 = std::async(std::launch::async, &HttpServer::HandleHttps, this);
}

void HttpServer::SetRequestHandler(HttpRequestCallback callback)
{
    this->requestCallback = callback;
}

void HttpServer::HandleHttp()
{
    TcpListenerSettings settings(HttpSettings::GetPort());
    TcpListener listener(settings);

    if(!listener.Start())
    {
        listener.Close();
        exit(1);
    }

    Console::WriteLog("Server started listening on http://" + HttpSettings::GetHost() + ":" + std::to_string(HttpSettings::GetPort()));

    while(isRunning)
    {
        TcpClient client;
        
        if(listener.Accept(&client))
        {
            HttpStream stream(client);
            auto result = std::async(std::launch::async, &HttpServer::HandleRequest, this, stream);
            result.wait();
        }
    }

    listener.Close();
}

void HttpServer::HandleHttps()
{
    TcpListenerSettings settings(HttpSettings::GetSslPort(), HttpSettings::GetCertificatePath(), HttpSettings::GetPrivateKeyPath());
    TcpListener listener(settings);

    if(!listener.Start())
    {
        listener.Close();
        exit(1);
    }

    Console::WriteLog("Server started listening on https://" + HttpSettings::GetHost() + ":" + std::to_string(HttpSettings::GetSslPort()));

    while(isRunning)
    {
        TcpClient client;
        
        if(listener.Accept(&client))
        {
            HttpStream stream(client);
            auto result = std::async(std::launch::async, &HttpServer::HandleRequest, this, stream);
            result.wait();
        }
    }

    listener.Close();
}

void HttpServer::HandleRequest(HttpStream stream)
{
    std::string header;
    int32_t headerSize = ReadHeader(&stream, header);

    HttpResponse response;

    if(headerSize <= 0 || headerSize > HttpSettings::GetMaxHeaderSize())
    {
        if(headerSize <= 0)
        {
            Console::WriteLog("Received an unexpected EOF or 0 bytes from the transport stream");
        }
        else
        {
            response = HttpResponse(HttpStatusCode::RequestHeaderFieldsTooLarge);
            response.Send(&stream);
            Console::WriteLog("[RES] " + std::to_string(static_cast<int>(response.GetStatusCode())));
        }

        stream.Close();
        return;
    }

    HttpRequest request;    

    if(!HttpRequest::TryParse(header, request))
    {
        response = HttpResponse(HttpStatusCode::BadRequest, HttpContentType(HttpMediaType::TextPlain), "Invalid HTTP request header");
        response.Send(&stream);
        stream.Close();
        Console::WriteLog("[RES] " + std::to_string(static_cast<int>(response.GetStatusCode())));
        return;
    }

    Console::WriteLog("[REQ] " + request.GetMethodAsString() + ": " + request.GetRawURL());

    if(!stream.GetClient()->IsSecureConnection())
    {
        if(HttpSettings::GetUseHttps())
        {
            if(HttpSettings::GetUseHttpsForwarding())
            {
                response = HttpResponse(HttpStatusCode::MovedPermanently);
                response.AddHeader("Location", "https://" + HttpSettings::GetHost() + ":" + std::to_string(HttpSettings::GetSslPort()));
                response.AddHeader("Connection", "close");
                response.Send(&stream);
                stream.Close();
                Console::WriteLog("[RES] " + std::to_string(static_cast<int>(response.GetStatusCode())));
                return;
            }
        }
    }

    HttpContext context(stream, request);
    HttpContext *ctx = &context;

    // Use std::async to call the registered callback asynchronously
    auto result = std::async(std::launch::async, [this, ctx]() {
        if (requestCallback)
            return requestCallback(ctx);
        else
            return HttpResponse(HttpStatusCode::OK);
    });

    // Wait for the asynchronous operation to complete
    response = result.get();
    response.Send(&stream);

    stream.Close();
    
    Console::WriteLog("[RES] " + std::to_string(static_cast<int>(response.GetStatusCode())));
}

int32_t HttpServer::ReadHeader(HttpStream *stream, std::string &header)
{
    // Read the header byte by byte until you encounter a double CRLF ("\r\n\r\n") indicating the end of the header
    // Reading can also stop when the maximum header size has been exceeded
    std::vector<char> headerBuilder;
    unsigned char prevByte = 0;
    unsigned char currentByte = 0;
    int curByte = 0;
    int headerSize = 0;

    while ((curByte = stream->ReadByte()) != -1)
    {
        currentByte = static_cast<unsigned char>(curByte);
        headerBuilder.push_back(static_cast<char>(currentByte));
        headerSize++;

        if(headerSize > HttpSettings::GetMaxHeaderSize())
            break;

        // Check for the end of the header (double CRLF)
        if (prevByte == '\r' && currentByte == '\n')
        {
            std::string str(headerBuilder.begin(), headerBuilder.end());

            if(StringUtility::EndsWith(str, "\r\n\r\n"))
            {
                break;
            }
        }

        prevByte = currentByte;
    }

    // At this point, headerBuilder contains the entire HTTP header
    header = std::string(headerBuilder.begin(), headerBuilder.end());
    return headerSize;
}