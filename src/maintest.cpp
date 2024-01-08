#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <signal.h>

#define PORT 8081
#define CERT_FILE "cert.pem"
#define KEY_FILE "key.pem"

volatile int server_running = 1;

void handle_signal(int signo) {
    if (signo == SIGINT) {
        fprintf(stderr, "Received SIGINT. Shutting down gracefully...\n");
        server_running = 0;
    } else if (signo == SIGPIPE) {
        fprintf(stderr, "Received SIGPIPE. Ignoring...\n");
    }
}

void handle_error(const char *msg) {
    perror(msg);
    ERR_print_errors_fp(stderr);
}

void handle_client(SSL *ssl) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, Secure World!\r\n";

    if (SSL_write(ssl, response, strlen(response)) <= 0) {
        handle_error("Error sending response");
        SSL_shutdown(ssl);
        SSL_free(ssl);
        return;
    }

    char buffer[1024];
    int bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);

    if (bytes > 0) {
        buffer[bytes] = '\0';
        //printf("Received: %s", buffer);
        printf("Received \n");
    } else if (bytes == 0) {
        printf("Connection closed by client\n");
    } else {
        handle_error("Error receiving data");
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
}

int main2() {
    SSL_CTX *ctx;
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Initialize OpenSSL
    SSL_library_init();    

    ctx = SSL_CTX_new(SSLv23_server_method());

    if (!ctx) {
        handle_error("Error creating SSL context");
        return EXIT_FAILURE;
    }

    // Load certificate and private key
    if (SSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0) {
        handle_error("Error loading certificate or private key");
        SSL_CTX_free(ctx);
        return EXIT_FAILURE;
    }

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        handle_error("Error creating socket");
        SSL_CTX_free(ctx);
        return EXIT_FAILURE;
    }

    // Setup server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        handle_error("Error binding socket");
        SSL_CTX_free(ctx);
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        handle_error("Error listening for connections");
        SSL_CTX_free(ctx);
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Register signal handler for graceful shutdown
    signal(SIGINT, handle_signal);
    signal(SIGPIPE, handle_signal);

    printf("Server listening on port %d...\n", PORT);

    while (server_running) {
        // Accept a connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            handle_error("Error accepting connection");
            continue;
        }

        // Create SSL connection
        SSL *ssl = SSL_new(ctx);
        if (!ssl) {
            handle_error("Error creating SSL structure");
            close(client_socket);
            continue;
        }

        SSL_set_fd(ssl, client_socket);
        if (SSL_accept(ssl) <= 0) {
            handle_error("Error during SSL_accept");
            close(client_socket);
            SSL_free(ssl);
            continue;
        }

        // Handle the client request
        handle_client(ssl);

        // Close the client socket
        close(client_socket);
    }

    // Clean up
    SSL_CTX_free(ctx);
    close(server_socket);

    return EXIT_SUCCESS;
}
