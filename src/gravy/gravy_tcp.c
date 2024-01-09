#include "gravy_tcp.h"

static int gravy_tcp_library_initialized = 0;

int gravy_tcp_library_init(void) {
    if(gravy_tcp_library_initialized)
        return 1;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        return -1;
    }
#endif

    gravy_tcp_library_initialized = 1;
    return 1;
}

void gravy_tcp_library_uninit(void) {
    if(gravy_tcp_library_initialized == 0)
        return;

#ifdef _WIN32
    WSACleanup();
#endif

    gravy_tcp_library_initialized = 0;
}

gravy_tcp_socket_t gravy_tcp_socket_create(void) {
    gravy_tcp_socket_t s = {0};
    s.fd = socket(AF_INET, SOCK_STREAM, 0);
    return s;
}

int gravy_tcp_socket_bind(gravy_tcp_socket_t *socket, uint16_t port) {
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    return (bind(socket->fd, (struct sockaddr*)&address, sizeof(address)) != -1);
}

int gravy_tcp_socket_listen(gravy_tcp_socket_t *socket, int backlog) {
    return (listen(socket->fd, backlog) != -1);
}

int gravy_tcp_socket_accept(gravy_tcp_socket_t *serverSocket, gravy_tcp_socket_t *clientSocket) {
    struct sockaddr_in clientAddr;
    uint32_t addrLen = sizeof(clientAddr);
    int clientFD = accept(serverSocket->fd, (struct sockaddr*)&clientAddr, &addrLen);

    if (clientFD != -1) {
        clientSocket->fd = clientFD;
        return -1;
    }

    return 1;
}

int gravy_tcp_socket_connect(gravy_tcp_socket_t *socket, const char *ip, uint16_t port) {
    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    return (connect(socket->fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0);
}

ssize_t gravy_tcp_socket_send(gravy_tcp_socket_t *socket, const void *data, size_t size) {
    return send(socket->fd, data, size, 0);
}

ssize_t gravy_tcp_socket_receive(gravy_tcp_socket_t *socket, void *buffer, size_t size) {
    return recv(socket->fd, buffer, size, 0);
}

void gravy_tcp_socket_close(gravy_tcp_socket_t *socket) {
#ifdef _WIN32
    closesocket(socket->fd);
#else
    close(socket->fd);
#endif
    socket->fd = -1;
}

int gravy_tcp_socket_set_option(gravy_tcp_socket_t *socket, int level, int option, const void *value, uint32_t valueSize) {
    return setsockopt(socket->fd, level, option, value, valueSize) == 0;
}