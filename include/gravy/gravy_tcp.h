#ifndef GRAVY_TCP_H_
#define GRAVY_TCP_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#include <winsock2.h>
#include "openssl/ssl.h"
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <openssl/ssl.h>
#endif

typedef struct gravy_tcp_socket {
    int32_t fd;
} gravy_tcp_socket_t;

#define GRAVY_API extern

#ifdef __cplusplus
extern "C" {
#endif
    GRAVY_API int gravy_tcp_library_init(void);
    GRAVY_API void gravy_tcp_library_uninit(void);
    GRAVY_API gravy_tcp_socket_t gravy_tcp_socket_create(void);
    GRAVY_API int gravy_tcp_socket_bind(gravy_tcp_socket_t *socket, uint16_t port);
    GRAVY_API int gravy_tcp_socket_listen(gravy_tcp_socket_t *socket, int backlog);
    GRAVY_API int gravy_tcp_socket_accept(gravy_tcp_socket_t *serverSocket, gravy_tcp_socket_t *clientSocket);
    GRAVY_API int gravy_tcp_socket_connect(gravy_tcp_socket_t *socket, const char *server, uint16_t port);
    GRAVY_API ssize_t gravy_tcp_socket_send(gravy_tcp_socket_t *socket, const void *data, size_t size);
    GRAVY_API ssize_t gravy_tcp_socket_receive(gravy_tcp_socket_t *socket, void *buffer, size_t size);
    GRAVY_API void gravy_tcp_socket_close(gravy_tcp_socket_t *socket);
    GRAVY_API int gravy_tcp_socket_set_option(gravy_tcp_socket_t *socket, int level, int option, const void *value, uint32_t valueSize);
    GRAVY_API int gravy_tcp_get_ip_from_domain(const char *domainName, char *result, size_t result_size);
#ifdef __cplusplus
}
#endif

#endif //GRAVY_TCP_H_