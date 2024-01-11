#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include "gravy_tcp.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>

class TcpClient
{
private:
    gravy_tcp_socket socket;
    SSL *ssl;
    SSL_CTX *sslContext;
public:
    TcpClient();
    TcpClient(gravy_tcp_socket socket, SSL *ssl = nullptr);
    ssize_t Receive(unsigned char *buffer, size_t offset, size_t count);
    ssize_t Send(unsigned char *buffer, size_t offset, size_t count);
    bool Connect(const std::string &host, uint16_t port, bool secure);
    void Close();
    bool IsSecureConnection() const;
    bool IsConnected() const;
};

#endif