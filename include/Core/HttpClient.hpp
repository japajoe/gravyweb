#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include "TcpClient.hpp"
#include <string>

class HttpClient
{
private:
    TcpClient client;
public:
    void Get(const std::string &url);
};

#endif