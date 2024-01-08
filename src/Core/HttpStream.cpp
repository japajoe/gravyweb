#include "HttpStream.hpp"
#include <cstring>

HttpStream::HttpStream()
{
}

HttpStream::HttpStream(TcpClient client)
{
    this->client = client;
}

int32_t HttpStream::ReadByte()
{
    if(!client.IsConnected())
        return -1;
    unsigned char buffer[16];
    std::memset(buffer, 0, 16);
    ssize_t numBytes = client.Receive(buffer, 0, 1);
    if(numBytes > 0)
        return *reinterpret_cast<int32_t*>(&buffer[0]);
    return -1;
}

ssize_t HttpStream::Read(void *buffer, size_t offset, size_t count)
{
    if(!client.IsConnected())
        return 0;
    unsigned char *buf = reinterpret_cast<unsigned char *>(buffer);
    return client.Receive(buf, offset, count);
}

ssize_t HttpStream::Write(void *buffer, size_t offset, size_t count)
{
    if(!client.IsConnected())
        return 0;
    unsigned char *buf = reinterpret_cast<unsigned char *>(buffer);
    return client.Send(buf, offset, count);
}

void HttpStream::Close()
{
    if(!client.IsConnected())
        return;
    client.Close();
}

TcpClient *HttpStream::GetClient()
{
    return &client;
}