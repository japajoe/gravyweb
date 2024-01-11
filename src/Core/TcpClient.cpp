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

bool TcpClient::Connect(const std::string &host, uint16_t port, bool secure)
{
    if(socket.fd >= 0 || sslContext != nullptr || ssl != nullptr)
        return false;

    socket = gravy_tcp_socket_create();

    if(socket.fd < 0)
        return false;

    if(!gravy_tcp_socket_connect(&socket, host.c_str(), port))
    {
        std::cout << "Failed to connect\n";
        Close();
        return false;
    }

    if(secure)
    {
        //OpenSSL_add_all_algorithms();

        sslContext = SSL_CTX_new(TLS_method());
        
        if (sslContext == nullptr)
        {
            Close();
            return false;
        }

        // // Set the cipher list
        // if (SSL_CTX_set_cipher_list(sslContext, "AES256-SHA") != 1) {
        //     fprintf(stderr, "Error setting cipher list\n");
        //     ERR_print_errors_fp(stderr);
        //     Close();
        //     return false;
        // }

        ssl = SSL_new(sslContext);
        SSL_set_fd(ssl, socket.fd);

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