#include "TcpListener.hpp"
#include <iostream>

TcpListener::TcpListener(const TcpListenerSettings &settings)
{
    this->port = settings.port;
    this->backlog = settings.backlog;
    this->sslContext = nullptr;

    Create();
    
    if(!SetOptions())
    {
        gravy_tcp_socket_close(&socket);
        exit(1);
    }
    
    if(!Bind())
    {
        gravy_tcp_socket_close(&socket);
        exit(1);
    }

    if(settings.UseSSL())
        SetSSL(settings);
}

void TcpListener::Create()
{
    socket = gravy_tcp_socket_create();
}

bool TcpListener::SetOptions()
{
    int reuse = 1;
    if(gravy_tcp_socket_set_option(&socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0)
    {
        std::cout << "Failed to set socket options\n";
        return false;
    }
    return true;
}

bool TcpListener::Bind()
{
    if(!gravy_tcp_socket_bind(&socket, port))
    {
        std::cout << "Failed to bind socket on port " << port << '\n';
        return false;
    }
    return true;
}

bool TcpListener::SetSSL(const TcpListenerSettings &settings)
{
    SSL_load_error_strings();

    sslContext = SSL_CTX_new(TLS_server_method());
    
    if (SSL_CTX_use_certificate_file(sslContext, settings.certificatePath.c_str(), SSL_FILETYPE_PEM) <= 0) 
    {
        gravy_tcp_socket_close(&socket);
        return false;
    }

    if (SSL_CTX_use_PrivateKey_file(sslContext, settings.privateKeyPath.c_str(), SSL_FILETYPE_PEM) <= 0) 
    {
        gravy_tcp_socket_close(&socket);
        return false;
    }

    // Check if the private key matches the certificate
    if (!SSL_CTX_check_private_key(sslContext)) 
    {
        gravy_tcp_socket_close(&socket);
        return false;
    }

    return true;
}

bool TcpListener::Start()
{
    if(!gravy_tcp_socket_listen(&socket, backlog))
    {
        std::cout << "Failed to start listening\n";
        return false;
    }

    return true;
}

bool TcpListener::Accept(TcpClient *client)
{
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
    }

    if(sslContext) 
    {
        SSL_CTX_free(sslContext);
        sslContext = nullptr;

        CRYPTO_set_locking_callback(nullptr);
        CRYPTO_THREADID_set_callback(nullptr);
    }
}