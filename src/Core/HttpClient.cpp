#include "HttpClient.hpp"
#include "StringUtility.hpp"
#include <iostream>
#include <regex>

void HttpClient::SetResponseHandler(const HttpClientResponseHandler &handler)
{
    this->responseHandler = handler;
}

void HttpClient::Get(const std::string &url)
{
    std::string uri = StringUtility::TrimStart(url);
    std::string service;

    if(StringUtility::StartsWith(uri, "http://"))
    {
        StringUtility::Replace(uri, "http://", "");
        service = "http://";
    }
    else if(StringUtility::StartsWith(uri, "https://"))
    {
        StringUtility::Replace(uri, "https://", "");
        service = "https://";
    }

    std::string path;

    if(!ExtractPathFromUrl(url, path))
    {
        std::cout << "Failed to extract path\n";
        return;
    }

    if(!ExtractHostnameFromUrl(url, uri))
    {
        std::cout << "Failed to extract host name\n";
        return;        
    }

    std::string request = 
    "GET " + path + " HTTP/1.1\r\n"
    "Host: " + uri + "\r\n"
    "Accept: */*\r\n"
    "Connection: close\r\n\r\n";

    TcpConnectionInfo info;
    if(!TcpConnectionInfo::CreateFromURL(service + uri, info))
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
        while ((received_bytes = client.Receive(buffer, 0, 1023)) > 0) 
        {
            if(responseHandler)
                responseHandler(buffer, received_bytes);
        }
    }

    client.Close();
}

bool HttpClient::ExtractPathFromUrl(const std::string& url, std::string &path)
{
    std::regex urlPattern("https?://[^/]+(/.*)?");

    std::smatch match;

    if (std::regex_match(url, match, urlPattern)) 
    {
        path = match[1].str().empty() ? "/" : match[1].str();
        return true;
    }
    else 
    {
        return false;
    }
}

bool HttpClient::ExtractHostnameFromUrl(const std::string& url, std::string &hostName)
{
    std::regex urlPattern("https?://([^/]+)(/.*)?");
    std::smatch match;

    if (std::regex_match(url, match, urlPattern)) {
        hostName = match[1].str();
        return true;
    }
    else
    {
        return false;
    }
}