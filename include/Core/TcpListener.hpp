#ifndef TCP_LISTENER_HPP
#define TCP_LISTENER_HPP

#include "gravy_tcp.h"
#include "TcpListenerSettings.hpp"
#include "TcpClient.hpp"
#include <openssl/ssl.h>
#include <string>

class TcpListener
{
private:
    gravy_tcp_socket socket;
    TcpListenerSettings settings;
    SSL_CTX *sslContext;
public:
    TcpListener(const TcpListenerSettings &settings);
    bool Start();
    bool Accept(TcpClient *client);
    void Close();
};

#endif