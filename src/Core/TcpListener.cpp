#include "TcpListener.hpp"
#include <iostream>

TcpListener::TcpListener(const TcpListenerSettings &settings)
{
    this->settings = settings;
    this->sslContext = nullptr;
    this->socket.fd = -1;
}

bool TcpListener::Start()
{
    if(socket.fd >= 0)
    {
        std::cout << "Socket already created\n";
        return false;
    }

    socket = gravy_tcp_socket_create();

    int reuse = 1;
    if(!gravy_tcp_socket_set_option(&socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
    {
        gravy_tcp_socket_close(&socket);
        std::cout << "Failed to set socket options\n";
        return false;
    }

    if(!gravy_tcp_socket_bind(&socket, settings.bindAddress.c_str(), settings.port))
    {
        gravy_tcp_socket_close(&socket);
        std::cout << "Failed to bind socket on port " << settings.port << '\n';
        return false;
    }
    
    if(settings.UseSSL())
    {
        SSL_load_error_strings();

        sslContext = SSL_CTX_new(TLS_server_method());
        
        if (SSL_CTX_use_certificate_file(sslContext, settings.certificatePath.c_str(), SSL_FILETYPE_PEM) <= 0) 
        {
            gravy_tcp_socket_close(&socket);
            SSL_CTX_free(sslContext);
            sslContext = nullptr;
            std::cout << "Failed to use certificate file\n";
            return false;
        }

        if (SSL_CTX_use_PrivateKey_file(sslContext, settings.privateKeyPath.c_str(), SSL_FILETYPE_PEM) <= 0) 
        {
            gravy_tcp_socket_close(&socket);
            SSL_CTX_free(sslContext);
            sslContext = nullptr;
            std::cout << "Failed to use private key file\n";
            return false;
        }

        if (!SSL_CTX_check_private_key(sslContext)) 
        {
            gravy_tcp_socket_close(&socket);
            SSL_CTX_free(sslContext);
            sslContext = nullptr;
            std::cout << "Failed to check private key\n";
            return false;
        }
    }

    if(!gravy_tcp_socket_listen(&socket, settings.backlog))
    {
        gravy_tcp_socket_close(&socket);
        std::cout << "Failed to start listening\n";
        return false;
    }

    return true;
}

bool TcpListener::Accept(TcpClient *client)
{
    if(socket.fd < 0)
        return false;

    gravy_tcp_socket newConnection = {0};
    
    if(gravy_tcp_socket_accept(&socket, &newConnection))
    {
        SSL *ssl = nullptr;

        if(sslContext) 
        {
            ssl = SSL_new(sslContext);

            if (!ssl) 
            {
                gravy_tcp_socket_close(&newConnection);
                return false;
            }

            SSL_set_fd(ssl, newConnection.fd);

            if (SSL_accept(ssl) <= 0) 
            {
                SSL_shutdown(ssl);
                SSL_free(ssl);
                gravy_tcp_socket_close(&newConnection);
                return false;
            }
        }

        *client = TcpClient(newConnection, ssl);
        return true;
    }
    return false;
}

void TcpListener::Close()
{
    if(socket.fd >= 0)
    {
        gravy_tcp_socket_close(&socket);

        if(sslContext)
        {
            SSL_CTX_free(sslContext);
            sslContext = nullptr;
        }
    }
}