#include "Stream.hpp"

Stream::Stream()
{
    size = 0;
    readPosition = 0;
    writePosition = 0;
}

Stream::~Stream() 
{

}

std::string Stream::Read(size_t size)
{
    return "";
}

size_t Stream::Read(void *buffer, size_t offset, size_t size)
{
    return 0;
}

size_t Stream::Write(void *buffer, size_t offset, size_t size)
{
    return 0;
}

size_t Stream::GetReadPosition() const
{
    return readPosition;
}

size_t Stream::GetWritePosition() const
{
    return writePosition;
}

size_t Stream::GetSize() const
{
    return size;
}

void Stream::Dispose()
{

}