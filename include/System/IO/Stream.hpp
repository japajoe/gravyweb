#ifndef STREAM_HPP
#define STREAM_HPP

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>

enum class SeekOrigin
{
    Begin,
    Current,
    End
};

class Stream
{
protected:
    size_t size;
    size_t readPosition;
    size_t writePosition;
public:
    Stream();
    virtual ~Stream();
    virtual std::string Read(size_t size);
    virtual size_t Read(void *buffer, size_t offset, size_t size);
    virtual size_t Write(void *buffer, size_t offset, size_t size);
    virtual ssize_t Seek(ssize_t offset, SeekOrigin origin);
    size_t GetReadPosition() const;
    size_t GetWritePosition() const;
    size_t GetSize() const;
    virtual void Dispose();
};

#endif