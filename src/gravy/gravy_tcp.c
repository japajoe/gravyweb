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

int gravy_tcp_socket_bind(gravy_tcp_socket_t *socket, const char *bindAddress, uint16_t port) {
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;

    struct in_addr addr;

    if (inet_pton(AF_INET, bindAddress, &addr) <= 0) {
        return 0;
    }

    address.sin_addr.s_addr = INADDR_ANY;
    memcpy(&address.sin_addr.s_addr, &addr, sizeof(addr));
    
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

void get_ip_and_port(const char *url, const char *service) {
    struct addrinfo hints, *result, *rp;
    int status;

    // Set hints for getaddrinfo
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Use TCP stream sockets

    // Resolve the URL
    status = getaddrinfo(url, service, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "Error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    // Iterate over the list of addresses and print IP and port
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];

        if (rp->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
            printf("IPv4 Address: %s\n", inet_ntop(AF_INET, addr, ipstr, sizeof(ipstr)));
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
            printf("IPv6 Address: %s\n", inet_ntop(AF_INET6, addr, ipstr, sizeof(ipstr)));
        }

        printf("Port: %d\n", ntohs(rp->ai_addr->sa_family == AF_INET ?
                                        ((struct sockaddr_in *)rp->ai_addr)->sin_port :
                                        ((struct sockaddr_in6 *)rp->ai_addr)->sin6_port));
    }

    freeaddrinfo(result);
}

int gravy_tcp_get_ip_address(const char *hostname, char *ip_buffer, size_t buffer_size) {
    struct hostent *host_info = gethostbyname(hostname);

    if (host_info == NULL) {
        perror("Error: Unable to get IP address");
        return -1; // Indicate failure
    }

    struct in_addr **addr_list = (struct in_addr **)host_info->h_addr_list;

    // Assuming there's at least one address in the list
    if (inet_ntop(AF_INET, addr_list[0], ip_buffer, buffer_size) == NULL) {
        perror("Error: Unable to convert IP address to string");
        return -1; // Indicate failure
    }

    return 1; // Success
}