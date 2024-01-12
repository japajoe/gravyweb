#include "TcpClient.hpp"
#include <iostream>

TcpClient::TcpClient()
{
    socket.fd = -1;
    ssl = nullptr;
    sslContext = nullptr;
}

TcpClient::TcpClient(gravy_tcp_socket socket, SSL *ssl)
{
    this->socket = socket;
    this->ssl = ssl;
    sslContext = nullptr;
}

ssize_t TcpClient::Receive(unsigned char *buffer, size_t offset, size_t count)
{
    if(ssl)
        return SSL_read(ssl, &buffer[offset], count);
    else
        return gravy_tcp_socket_receive(&socket, &buffer[offset], count);
}

ssize_t TcpClient::Send(unsigned char *buffer, size_t offset, size_t count)
{
    if(ssl)
        return SSL_write(ssl, &buffer[offset], count);
    else
        return gravy_tcp_socket_send(&socket, &buffer[offset], count);
}

bool TcpClient::Connect(const TcpConnectionInfo &connectionInfo)
{
    if(socket.fd >= 0 || sslContext != nullptr || ssl != nullptr)
        return false;

    socket = gravy_tcp_socket_create();

    if(socket.fd < 0)
        return false;

    if(!gravy_tcp_socket_connect(&socket, connectionInfo.ip.c_str(), connectionInfo.port))
    {
        std::cout << "Failed to connect\n";
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

void TcpClient::Close()
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

bool TcpClient::IsSecureConnection() const
{
    return ssl != nullptr;
}

bool TcpClient::IsConnected() const
{
    return socket.fd >= 0;
}

std::string TcpClient::GetIP() const
{
    char ipString[INET_ADDRSTRLEN];  // or INET6_ADDRSTRLEN for IPv6
    inet_ntop(AF_INET, &socket.address.ipv4.sin_addr, ipString, sizeof(ipString));

    std::string ip(ipString);
    return ip;
}

int TcpClient::GetPort() const
{
    int port = ntohs(socket.address.ipv4.sin_port);
    return port;
}