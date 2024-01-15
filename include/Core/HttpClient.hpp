#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include "gravy_tcp.h"
#include "TcpConnectionInfo.hpp"
#include "HttpContentType.hpp"
#include "Stream.hpp"
#include <string>
#include <functional>
#include <cstdlib>

using HttpClientResponseHandler = std::function<void(unsigned char *buffer, size_t numBytesReceived, void *userData)>;

class HttpClientConnection
{
private:
    gravy_tcp_socket socket;
    SSL *ssl;
public:
    HttpClientConnection();
    ~HttpClientConnection();
    bool Connect(const TcpConnectionInfo &connectionInfo, SSL_CTX *sslContext = nullptr);
    void Close();
    ssize_t Read(void *buffer, size_t size);
    ssize_t Write(const void *buffer, size_t size);
};

class HttpClient
{
private:
    SSL_CTX *sslContext;
    HttpClientResponseHandler handler;
    void *userData;
    bool CreateSSLContext();
    bool GetURIComponents(const std::string &url, std::string &path, std::string &host, std::string &scheme);
    bool Send(HttpClientConnection *connection, Stream *data);
public:
    HttpClient();
    ~HttpClient();
    void SetResponseHandler(const HttpClientResponseHandler &handler, void *userData = nullptr);
    bool Get(const std::string &url);
    bool Post(const std::string &url, const HttpContentType &contentType, Stream *content);
};

#endif