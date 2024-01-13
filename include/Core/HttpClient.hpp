#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include "gravy_tcp.h"
#include "TcpConnectionInfo.hpp"
#include <string>
#include <functional>
#include <cstdlib>

using HttpClientResponseHandler = std::function<void(unsigned char *buffer, size_t numBytesReceived)>;

class HttpClient
{
private:
    gravy_tcp_socket socket;
    SSL_CTX *sslContext;
    SSL *ssl;
    HttpClientResponseHandler responseHandler;
    bool Connect(const TcpConnectionInfo &connectionInfo);
public:
    HttpClient();
    ~HttpClient();
    void Close();
    void SetResponseHandler(const HttpClientResponseHandler &handler);
    bool Get(const std::string &url);
};

#endif