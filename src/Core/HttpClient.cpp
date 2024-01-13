#include "HttpClient.hpp"
#include "URI.hpp"
#include "Console.hpp"
#include <cstring>

HttpClient::HttpClient()
{
    std::memset(&socket, 0, sizeof(gravy_tcp_socket));
    socket.fd = -1;
    sslContext = nullptr;
    ssl = nullptr;
}

HttpClient::~HttpClient()
{
    Close();
}

void HttpClient::Close()
{
    if(socket.fd >= 0)
        gravy_tcp_socket_close(&socket);

    if(ssl)
    {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        ssl = nullptr;           
    }
    if(sslContext)
    {
        SSL_CTX_free(sslContext);
        sslContext = nullptr;
    }
}

void HttpClient::SetResponseHandler(const HttpClientResponseHandler &handler)
{
    this->responseHandler = handler;
}

bool HttpClient::Connect(const TcpConnectionInfo &connectionInfo)
{
    if(socket.fd >= 0)
        return false;

    socket = gravy_tcp_socket_create();

    if(socket.fd < 0)
        return false;
    
    if(!gravy_tcp_socket_connect(&socket, connectionInfo.ip.c_str(), connectionInfo.port))
    {
        Console::WriteError("Failed to connect");
        Close();
        return false;
    }

    if(connectionInfo.secure)
    {
        sslContext = SSL_CTX_new(TLS_method());
        
        if (sslContext == nullptr)
        {
            Close();
            return false;
        }

        ssl = SSL_new(sslContext);
        SSL_set_fd(ssl, socket.fd);
        
        SSL_ctrl(ssl, SSL_CTRL_SET_TLSEXT_HOSTNAME, TLSEXT_NAMETYPE_host_name, (void*)connectionInfo.hostName.c_str());

        if (SSL_connect(ssl) != 1) 
        {
            Close();
            return false;
        }
    }

    return true;
}

bool HttpClient::Get(const std::string &url)
{
    if(!responseHandler)
    {
        Console::WriteError("Response handler not assigned");
        return false;
    }

    URI uri(url);

    std::string path;
    std::string host;
    std::string scheme;

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

    TcpConnectionInfo connectionInfo;

    if(!TcpConnectionInfo::CreateFromURL(scheme + host, connectionInfo))
    {
        Console::WriteError("Failed to create connection info from URL");
        return false;
    }

    if(!Connect(connectionInfo))
        return false;

    std::string request = 
    "GET " + path + " HTTP/1.1\r\n"
    "Host: " + host + "\r\n"
    "Accept: */*\r\n"
    "Connection: close\r\n\r\n";

    unsigned char *pRequest = reinterpret_cast<unsigned char*>(const_cast<char*>(request.c_str()));

    ssize_t bytesToSend = request.size();
    ssize_t bytesSent = 0;
    ssize_t bytesReceived = 0;

    unsigned char buffer[1024];
    memset(buffer, 0, 1024);

    if(ssl)
    {
        while(bytesSent < bytesToSend)
        {
            size_t numBytes = SSL_write(ssl, &pRequest[bytesSent], 1024);
            if(numBytes > 0)
                bytesSent += numBytes;
        }
        
        while ((bytesReceived = SSL_read(ssl, buffer, 1023)) > 0) 
        {
            if(responseHandler)
                responseHandler(buffer, bytesReceived);
        }
    }
    else
    {
        while(bytesSent < bytesToSend)
        {
            size_t numBytes = gravy_tcp_socket_send(&socket, &pRequest[bytesSent], 1024);
            if(numBytes > 0)
                bytesSent += numBytes;
        }
        while ((bytesReceived = gravy_tcp_socket_receive(&socket, buffer, 1023)) > 0) 
        {
            if(responseHandler)
                responseHandler(buffer, bytesReceived);
        }
    }

    Close();
    return true;
}