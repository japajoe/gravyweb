#include "TcpConnectionInfo.hpp"
#include "StringUtility.hpp"
#include "gravy_tcp.h"

TcpConnectionInfo::TcpConnectionInfo()
{

}

TcpConnectionInfo::TcpConnectionInfo(const std::string &hostName, const std::string &ip, uint16_t port, bool secure)
{
    this->hostName = hostName;
    this->ip = ip;
    this->port = port;
    this->secure = secure;
}

bool TcpConnectionInfo::CreateFromURL(const std::string &url, TcpConnectionInfo &connectionInfo)
{
    std::string uri = StringUtility::TrimStart(url);

    bool secure = false;

    if(StringUtility::StartsWith(uri, "http://"))
    {
        StringUtility::Replace(uri, "http://", "");
        secure = false;
    }
    else if(StringUtility::StartsWith(uri, "https://"))
    {
        StringUtility::Replace(uri, "https://", "");
        secure = true;
    }

    std::string ip;
    uint16_t port;

    if(!GetIPAndPort(uri, ip, port, secure))
        return false;

    connectionInfo.hostName = uri;
    connectionInfo.ip = ip;
    connectionInfo.port = port;
    connectionInfo.secure = secure;

    return true;
}

bool TcpConnectionInfo::GetIPAndPort(const std::string &url, std::string &ip, uint16_t &port, bool https)
{
    std::string service = https ? "https" : "http";

    struct addrinfo hints, *result, *rp;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Use TCP stream sockets

    // Resolve the URL
    status = getaddrinfo(url.c_str(), service.c_str(), &hints, &result);
    if (status != 0)
    {
        //std::cerr << "Error: " << gai_strerror(status) << std::endl;
        return false;
    }

    // Iterate over the list of addresses and use the first one
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        char ipstr[INET6_ADDRSTRLEN];

        if (rp->ai_family == AF_INET)
        { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
            ip = ipstr;
            port = ((struct sockaddr_in *)rp->ai_addr)->sin_port;
            port = ntohs(port);
            freeaddrinfo(result);
            return true;
        }
        else
        { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            inet_ntop(AF_INET6, &(ipv6->sin6_addr), ipstr, sizeof(ipstr));
            ip = ipstr;
            port = ((struct sockaddr_in6 *)rp->ai_addr)->sin6_port;
            port = ntohs(port);
            freeaddrinfo(result);
            return true;
            break; // Use the first IPv6 address
        }
    }

    freeaddrinfo(result);

    return false;
}