#include "HttpServer.hpp"
#include "HttpSettings.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "MemoryStream.hpp"
#include "StringUtility.hpp"
#include "Console.hpp"
#include "Signal.hpp"
#include <memory>
#include <future>

HttpServer::HttpServer(const HttpConfig &config)
{
    if(config.useHttps)
    {
        if(!File::Exists(config.certificatePath))
        {
            Console::WriteError("Certificate file not found: " + config.certificatePath);
            exit(1);
        }

        if(!File::Exists(config.privateKeyPath))
        {
            Console::WriteError("Private key file not found: " + config.privateKeyPath);
            exit(1);
        }
    }

    if(!Directory::Exists(config.privateHtml))
    {
        Console::WriteError("Private html directory does not exist: " + config.privateHtml);
        exit(1);
    }

    if(!Directory::Exists(config.publicHtml))
    {
        Console::WriteError("Public html directory does not exist: " + config.publicHtml);
        exit(1);
    }

    //Sets up SIGINT and SIGPIPE handlers
    Signal::RegisterHandler();

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
    int32_t backlog = HttpSettings::GetMaxConnections();

    if(backlog <= 0)
        backlog = TCP_LISTENER_MAX_CONNECTIONS;

    TcpListenerSettings settings(HttpSettings::GetPort(), HttpSettings::GetBindAddress(), backlog);
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
        }
    }

    listener.Close();
}

void HttpServer::HandleHttps()
{
    int32_t backlog = HttpSettings::GetMaxConnections();

    if(backlog <= 0)
        backlog = TCP_LISTENER_MAX_CONNECTIONS;

    TcpListenerSettings settings(HttpSettings::GetSslPort(), HttpSettings::GetBindAddress(), backlog, HttpSettings::GetCertificatePath(), HttpSettings::GetPrivateKeyPath());
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
        }
    }

    listener.Close();
}

void HttpServer::HandleRequest(HttpStream stream)
{
    while(stream.GetClient()->IsConnected())
    {
        std::string header;
        int32_t headerSize = ReadHeader(&stream, header);

        if(headerSize <= 0 || headerSize > HttpSettings::GetMaxHeaderSize())
        {
            if(headerSize <= 0)
            {
                //This may happen if a client has not sent any data for a while
                //It may also happen when a client very frequently refreshes a page (like holding F5 in the browser)
                Console::WriteError("Received an unexpected EOF or 0 bytes from the transport stream");
            }
            else
            {
                HttpResponse response(HttpStatusCode::RequestHeaderFieldsTooLarge);
                response.Send(&stream);
                Console::WriteLog("[RES] " + std::to_string(static_cast<int>(response.GetStatusCode())));
            }

            stream.Close();
            return;
        }

        HttpRequest request;    

        if(!HttpRequest::TryParse(header, request))
        {
            HttpResponse response(HttpStatusCode::BadRequest, HttpContentType(HttpMediaType::TextPlain), "Invalid HTTP request header");
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
                //If a client requests so, we should still upgrade the connection
                if(HttpSettings::GetUseHttpsForwarding() || request.GetUpgradeInsecureRequests())
                {
                    std::string location = "https://" + HttpSettings::GetHost() + ":" + std::to_string(HttpSettings::GetSslPort()) + request.GetURL();
                    HttpResponse response(HttpStatusCode::MovedPermanently);
                    response.AddHeader("Location", location);
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

        try 
        {
            HttpResponse response = result.get();
            response.Send(&stream);
            Console::WriteLog("[RES] " + std::to_string(static_cast<int>(response.GetStatusCode())));
        } 
        catch (const std::exception& e) 
        {
            std::string message(e.what());
            Console::WriteError("Exception caught: " + message);
            stream.Close();
            return;
        }

        if(request.GetConnection() != "keep-alive")
            stream.Close();
    }
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