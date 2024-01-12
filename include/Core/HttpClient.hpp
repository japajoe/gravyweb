#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include "TcpClient.hpp"
#include <string>
#include <functional>

using HttpClientResponseHandler = std::function<void(unsigned char *buffer, size_t numBytesReceived)>;

class HttpClient
{
private:
    TcpClient client;
    HttpClientResponseHandler responseHandler;
    static bool ExtractPathFromUrl(const std::string& url, std::string &path);
    static bool ExtractHostnameFromUrl(const std::string& url, std::string &hostName);
public:
    void Get(const std::string &url);
    void SetResponseHandler(const HttpClientResponseHandler &handler);
};

#endif