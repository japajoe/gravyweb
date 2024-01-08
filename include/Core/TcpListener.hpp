#ifndef TCP_LISTENER_HPP
#define TCP_LISTENER_HPP

#include "gravy_tcp.h"
#include <openssl/ssl.h>
#include <string>
#include "TcpListenerSettings.hpp"
#include "TcpClient.hpp"

class TcpListener
{
private:
    gravy_tcp_socket socket;
    uint16_t port;
    int32_t backlog;
    SSL_CTX *sslContext;
    void Create();
    bool SetOptions();
    bool Bind();
    bool SetSSL(const TcpListenerSettings &settings);
public:
    TcpListener(const TcpListenerSettings &settings);
    bool Start();
    bool Accept(TcpClient *client);
    void Close();
};

#endif