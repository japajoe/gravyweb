#ifndef HTTPSTREAM_HPP
#define HTTPSTREAM_HPP

#include "TcpClient.hpp"

class HttpStream
{
private:
    TcpClient client;
public:
    HttpStream();
    HttpStream(TcpClient client);
    int32_t ReadByte();
    ssize_t Read(void *buffer, size_t offset, size_t count);
    ssize_t Write(void *buffer, size_t offset, size_t count);
    void Close();
    TcpClient *GetClient();
};

#endif