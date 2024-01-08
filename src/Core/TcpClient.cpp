#include "TcpClient.hpp"

TcpClient::TcpClient()
{
    ssl = nullptr;
}

TcpClient::TcpClient(gravy_tcp_socket socket, SSL *ssl)
{
    this->socket = socket;
    this->ssl = ssl;
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
}

bool TcpClient::IsSecureConnection() const
{
    return ssl != nullptr;
}

bool TcpClient::IsConnected() const
{
    return socket.fd >= 0;
}