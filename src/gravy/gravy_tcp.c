#include "gravy_tcp.h"

#define GRAVY_SUCCESS 1
#define GRAVY_ERROR 0

static int gravy_tcp_library_initialized = 0;

int gravy_tcp_library_init(void) {
    if(gravy_tcp_library_initialized)
        return GRAVY_SUCCESS;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        return GRAVY_ERROR;
    }
#endif

    gravy_tcp_library_initialized = 1;
    return GRAVY_SUCCESS;
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
#ifdef _WIN32
    if(s.fd == INVALID_SOCKET)
        s.fd = -1;
#endif
    return s;
}

int gravy_tcp_socket_bind(gravy_tcp_socket_t *socket, const char *bindAddress, uint16_t port) {
    sockaddr_in_t address = {0};
    address.sin_family = AF_INET;

    struct in_addr addr;

    if (inet_pton(AF_INET, bindAddress, &addr) <= 0)
        return GRAVY_ERROR;

    address.sin_addr.s_addr = INADDR_ANY;
    memcpy(&address.sin_addr.s_addr, &addr, sizeof(addr));
    
    address.sin_port = htons(port);

    memcpy(&socket->address.ipv4, &address, sizeof(sockaddr_in_t));

#ifdef _WIN32
    return bind(socket->fd, (struct sockaddr*)&socket->address.ipv4, sizeof(sockaddr_in_t)) == SOCKET_ERROR ? GRAVY_ERROR : GRAVY_SUCCESS;
#else
    return bind(socket->fd, (struct sockaddr*)&socket->address.ipv4, sizeof(sockaddr_in_t)) == -1 ? GRAVY_ERROR : GRAVY_SUCCESS;
#endif
}

int gravy_tcp_socket_listen(gravy_tcp_socket_t *socket, int backlog) {
#ifdef _WIN32
    return listen(socket->fd, backlog) == SOCKET_ERROR ? GRAVY_ERROR : GRAVY_SUCCESS;
#else
    return listen(socket->fd, backlog) == -1 ? GRAVY_ERROR : GRAVY_SUCCESS;
#endif
}

int gravy_tcp_socket_accept(gravy_tcp_socket_t *serverSocket, gravy_tcp_socket_t *clientSocket) {
    sockaddr_in_t clientAddr;
    uint32_t addrLen = sizeof(clientAddr);

    int clientFD = -1;

#ifdef _WIN32
    clientFD = accept(serverSocket->fd, (struct sockaddr*)&clientAddr, (int32_t*)&addrLen);
    
    if(clientFD == INVALID_SOCKET)
        clientFD = -1;
#else
    clientFD = accept(serverSocket->fd, (struct sockaddr*)&clientAddr, &addrLen);
#endif

    if (clientFD == -1)
        return GRAVY_ERROR;

    clientSocket->fd = clientFD;
    memcpy(&clientSocket->address, &clientAddr, sizeof(sockaddr_in_t));

    return GRAVY_SUCCESS;
}

int gravy_tcp_socket_connect(gravy_tcp_socket_t *socket, const char *ip, uint16_t port) {
    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    int result = connect(socket->fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

#ifdef _WIN32
    return result == SOCKET_ERROR ? GRAVY_ERROR : GRAVY_SUCCESS;
#else
    return result == -1 ? GRAVY_ERROR : GRAVY_SUCCESS;
#endif
}

ssize_t gravy_tcp_socket_send(gravy_tcp_socket_t *socket, const void *data, size_t size) {
#ifdef _WIN32
    return send(socket->fd, (char*)data, size, 0);
#else
    return send(socket->fd, data, size, 0);
#endif
}

ssize_t gravy_tcp_socket_receive(gravy_tcp_socket_t *socket, void *buffer, size_t size) {
#ifdef _WIN32
    return recv(socket->fd, (char*)buffer, size, 0);
#else
    return recv(socket->fd, buffer, size, 0);
#endif
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
#ifdef _WIN32
    return setsockopt(socket->fd, level, option, (char*)value, valueSize) != 0 ? GRAVY_ERROR : GRAVY_SUCCESS;
#else
    return setsockopt(socket->fd, level, option, value, valueSize) != 0 ? GRAVY_ERROR : GRAVY_SUCCESS;
#endif
}