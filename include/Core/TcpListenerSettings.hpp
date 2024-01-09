#ifndef TCPLISTENERSETTINGS_HPP
#define TCPLISTENERSETTINGS_HPP

#include <cstdint>
#include <string>

constexpr int TCP_LISTENER_MAX_CONNECTIONS = 2147483647;

class TcpListenerSettings
{
private:
    bool useSSL;
public:
    uint16_t port;
    int32_t backlog;
    std::string certificatePath;
    std::string privateKeyPath;

    TcpListenerSettings()
    {

    }

    TcpListenerSettings(uint16_t port)
    {
        this->port = port;
        this->backlog = TCP_LISTENER_MAX_CONNECTIONS;
        this->useSSL = false;
    }

    TcpListenerSettings(uint16_t port, int32_t backlog)
    {
        this->port = port;
        this->useSSL = false;
    }

    TcpListenerSettings(uint16_t port, const std::string &certificatePath, const std::string privateKeyPath)
    {
        this->port = port;
        this->backlog = TCP_LISTENER_MAX_CONNECTIONS;
        this->certificatePath = certificatePath;
        this->privateKeyPath = privateKeyPath;
        this->useSSL = true;
    }

    TcpListenerSettings(uint16_t port, int32_t backlog, const std::string &certificatePath, const std::string privateKeyPath)
    {
        this->port = port;
        this->backlog = backlog;
        this->certificatePath = certificatePath;
        this->privateKeyPath = privateKeyPath;
        this->useSSL = true;
    }

    bool UseSSL() const
    {
        return useSSL;
    }
};

#endif