#include "HttpClient.hpp"
#include "URI.hpp"
#include "Console.hpp"
#include <cstring>

HttpClientConnection::HttpClientConnection()
{
    std::memset(&socket, 0, sizeof(gravy_tcp_socket));
    socket.fd = -1;
    ssl = nullptr;
}

HttpClientConnection::~HttpClientConnection()
{
    Close();
}

bool HttpClientConnection::Connect(const TcpConnectionInfo &connectionInfo, SSL_CTX *sslContext)
{
    if(socket.fd >= 0)
    {
        Console::WriteError("Failed to connect, socket already in use");
        return false;
    }

    socket = gravy_tcp_socket_create();

    if(socket.fd < 0)
    {
        Console::WriteError("Failed to create socket");
        return false;
    }
    
    if(!gravy_tcp_socket_connect(&socket, connectionInfo.ip.c_str(), connectionInfo.port))
    {
        Console::WriteError("Failed to connect to " + connectionInfo.ip);
        Close();
        return false;
    }

    if(sslContext)
    {
        ssl = SSL_new(sslContext);
        SSL_set_fd(ssl, socket.fd);
        
        SSL_ctrl(ssl, SSL_CTRL_SET_TLSEXT_HOSTNAME, TLSEXT_NAMETYPE_host_name, (void*)connectionInfo.hostName.c_str());

        if (SSL_connect(ssl) != 1) 
        {
            Console::WriteError("Failed to SSL connect");
            Close();
            return false;
        }
    }

    return true;
}

ssize_t HttpClientConnection::Read(void *buffer, size_t size)
{
    if(ssl)
        return SSL_read(ssl, buffer, size);
    else
        return gravy_tcp_socket_receive(&socket, buffer, size);
}

ssize_t HttpClientConnection::Write(const void *buffer, size_t size)
{
    if(ssl)
        return SSL_write(ssl, buffer, size);
    else
        return gravy_tcp_socket_send(&socket, buffer, size);
}

void HttpClientConnection::Close()
{
    if(socket.fd >= 0)
        gravy_tcp_socket_close(&socket);

    if(ssl)
    {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        ssl = nullptr;           
    }
}

HttpClient::HttpClient()
{
    sslContext = nullptr;
    handler = nullptr;
    userData = nullptr;
}

HttpClient::~HttpClient()
{
    if(sslContext)
    {
        SSL_CTX_free(sslContext);
        sslContext = nullptr;
    }
}

bool HttpClient::CreateSSLContext()
{
    if(sslContext)
        return true;

    if(sslContext == nullptr)
    {
        sslContext = SSL_CTX_new(TLS_method());
    }

    if (sslContext == nullptr)
    {
        Console::WriteError("Failed to create SSL context");
        return false;
    }

    return true;
}

bool HttpClient::Get(const std::string &url)
{
    if(!handler)
    {
        Console::WriteError("No response handler was set");
        return false;
    }

    if(!CreateSSLContext())
        return false;

    std::string path;
    std::string host;
    std::string scheme;

    if(!GetURIComponents(url, path, host, scheme))
        return false;

    TcpConnectionInfo connectionInfo;

    if(!TcpConnectionInfo::CreateFromURL(scheme + host, connectionInfo))
    {
        Console::WriteError("Failed to create connection info from URL");
        return false;
    }

    HttpClientConnection connection;
    
    if(!connection.Connect(connectionInfo, connectionInfo.secure ? sslContext : nullptr))
    {
        return false;
    }

    std::string request = 
    "GET " + path + " HTTP/1.1\r\n"
    "Host: " + host + "\r\n"
    "Accept: */*\r\n"
    "Connection: close\r\n\r\n";

    char *pRequest = const_cast<char*>(request.c_str());

    ssize_t bytesToSend = request.size();
    ssize_t bytesSent = 0;
    ssize_t bytesReceived = 0;

    unsigned char buffer[1024];
    memset(buffer, 0, 1024);

    while(bytesSent < bytesToSend)
    {
        size_t numBytes = connection.Write(&pRequest[bytesSent], 1024);
        if(numBytes > 0)
            bytesSent += numBytes;
    }
    
    while ((bytesReceived = connection.Read(buffer, 1023)) > 0) 
    {
        handler(buffer, bytesReceived, userData);
    }

    connection.Close();
    return true;
}

bool HttpClient::GetURIComponents(const std::string &url, std::string &path, std::string &host, std::string &scheme)
{
    URI uri(url);

    if(!uri.GetHost(host))
    {
        Console::WriteError("Failed to get host from URL");
        return false;
    }

    if(!uri.GetPath(path))
    {
        Console::WriteError("Failed to get path from URL");
        return false;
    }

    if(!uri.GetScheme(scheme))
    {
        Console::WriteError("Failed to get scheme from URL");
        return false;
    }

    if(path.size() == 0)
        path = "/";

    scheme += "://";

    return true;
}

void HttpClient::SetResponseHandler(const HttpClientResponseHandler &handler, void *userData)
{
    this->handler = handler;
    this->userData = userData;
}