#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include "TcpClient.hpp"
#include <string>

class HttpClient
{
private:
    TcpClient client;
    bool GetIPAndPort(const std::string &url, std::string &ip, uint16_t &port, bool https);
public:
    //This is broken, do not use
    void Get(const std::string &url);
};

#endif