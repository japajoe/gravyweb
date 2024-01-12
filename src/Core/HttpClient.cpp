#include "HttpClient.hpp"
#include "StringUtility.hpp"
#include "URI.hpp"
#include "Console.hpp"
#include <regex>

void HttpClient::SetResponseHandler(const HttpClientResponseHandler &handler)
{
    this->responseHandler = handler;
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

    TcpConnectionInfo info;

    if(!TcpConnectionInfo::CreateFromURL(scheme + host, info))
    {
        Console::WriteError("Failed to create connection info from URL");
        return false;
    }
    
    if(!client.Connect(info))
    {
        return false;
    }

    std::string request = 
    "GET " + path + " HTTP/1.1\r\n"
    "Host: " + host + "\r\n"
    "Accept: */*\r\n"
    "Connection: close\r\n\r\n";

    unsigned char *pRequest = reinterpret_cast<unsigned char*>(const_cast<char*>(request.c_str()));

    size_t bytesToSend = request.size();
    size_t bytesSent = 0;

    while(bytesSent < bytesToSend)
    {
        size_t numBytes = client.Send(&pRequest[bytesSent], 0, 1024);
        if(numBytes > 0)
            bytesSent += numBytes;
    }

    unsigned char buffer[1024];
    memset(buffer, 0, 1024);

    ssize_t bytesReceived = 0;
    while ((bytesReceived = client.Receive(buffer, 0, 1023)) > 0) 
    {
        if(responseHandler)
            responseHandler(buffer, bytesReceived);
    }

    client.Close();

    return true;
}