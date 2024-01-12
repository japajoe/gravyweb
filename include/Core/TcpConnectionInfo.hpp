#ifndef TCPCONNECTIONINFO_HPP
#define TCPCONNECTIONINFO_HPP

#include <string>
#include <cstdint>

class TcpConnectionInfo
{
public:
    std::string hostName;
    std::string ip;
    uint16_t port;
    bool secure;
    TcpConnectionInfo();
    TcpConnectionInfo(const std::string &hostName, const std::string &ip, uint16_t port, bool secure);
    static bool CreateFromURL(const std::string &url, TcpConnectionInfo &connectionInfo);
    static bool GetIPAndPort(const std::string &url, std::string &ip, uint16_t &port, bool https);
};

#endif