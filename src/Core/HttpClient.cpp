#include "HttpClient.hpp"
#include "StringUtility.hpp"
#include <iostream>

void HttpClient::Get(const std::string &url)
{
    std::string uri = StringUtility::TrimStart(url);

    if(StringUtility::StartsWith(uri, "http://"))
        StringUtility::Replace(uri, "http://", "");
    else if(StringUtility::StartsWith(uri, "https://"))
        StringUtility::Replace(uri, "https://", "");

    std::string request = 
    "GET / HTTP/1.1\r\nHost: " + uri + "\r\n"
    "Accept: */*\r\n"
    "Connection: close\r\n\r\n";

    TcpConnectionInfo info;
    if(!TcpConnectionInfo::CreateFromURL(url, info))
        return;
    
    if(!client.Connect(info))
    {
        return;
    }

    unsigned char *pRequest = reinterpret_cast<unsigned char*>(const_cast<char*>(request.c_str()));

    unsigned char buffer[1024];
    memset(buffer, 0, 1024);
    
    if(client.Send(pRequest, 0, request.size()) > 0)
    {
        ssize_t received_bytes;
        while ((received_bytes = client.Receive(buffer, 0, 1023)) > 0) {
            std::cout << buffer;
        }
    }

    client.Close();
}