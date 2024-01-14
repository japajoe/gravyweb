#ifndef GRAVY_TCP_H_
#define GRAVY_TCP_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <openssl/ssl.h>

#ifdef _WIN32
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0600
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <poll.h>
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr_in6 sockaddr_in6_t;

typedef union {
    sockaddr_in_t ipv4;
    sockaddr_in6_t ipv6;
} gravy_socket_address;

typedef struct gravy_tcp_socket {
    int32_t fd;
    gravy_socket_address address;
} gravy_tcp_socket_t;

#define GRAVY_API extern

#ifdef __cplusplus
extern "C" {
#endif
    GRAVY_API int gravy_tcp_library_init(void);
    GRAVY_API void gravy_tcp_library_uninit(void);
    GRAVY_API gravy_tcp_socket_t gravy_tcp_socket_create(void);
    GRAVY_API int gravy_tcp_socket_bind(gravy_tcp_socket_t *socket, const char *bindAddress, uint16_t port);
    GRAVY_API int gravy_tcp_socket_listen(gravy_tcp_socket_t *socket, int backlog);
    GRAVY_API int gravy_tcp_socket_accept(gravy_tcp_socket_t *serverSocket, gravy_tcp_socket_t *clientSocket);
    GRAVY_API int gravy_tcp_socket_connect(gravy_tcp_socket_t *socket, const char *server, uint16_t port);
    GRAVY_API ssize_t gravy_tcp_socket_send(gravy_tcp_socket_t *socket, const void *data, size_t size);
    GRAVY_API ssize_t gravy_tcp_socket_receive(gravy_tcp_socket_t *socket, void *buffer, size_t size);
    GRAVY_API void gravy_tcp_socket_close(gravy_tcp_socket_t *socket);
    GRAVY_API int gravy_tcp_socket_set_option(gravy_tcp_socket_t *socket, int level, int option, const void *value, uint32_t valueSize);
#ifdef __cplusplus
}
#endif

#endif //GRAVY_TCP_H_