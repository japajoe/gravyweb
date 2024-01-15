#include "MemoryStream.hpp"

MemoryStream::MemoryStream(void *data, size_t size, bool copyMemory) : Stream()
{
    this->ownsMemory = copyMemory;

    if(this->ownsMemory)
    {
        unsigned char *memory = new unsigned char[size];
        std::memcpy(memory, data, size);
        this->data = memory;
    }
    else
    {
        this->data = data;
    }
    this->size = size;
}

MemoryStream::~MemoryStream()
{
    Dispose();
}

std::string MemoryStream::Read(size_t numBytes)
{
    if (readPosition >= size)
        return ""; // Read position is out of range

    if (readPosition + numBytes > size)
        numBytes = size - readPosition; // Adjust the number of bytes to read to avoid going out of range

    std::string s(static_cast<char*>(data) + readPosition, numBytes);

    readPosition += numBytes;

    return s;
}

size_t MemoryStream::Read(void *buffer, size_t offset, size_t numBytes)
{
    if (readPosition >= size)
        return 0; // Read position is out of range

    if (readPosition + numBytes > size)
        numBytes = size - readPosition; // Adjust the number of bytes to read to avoid going out of range

    char *pBuffer = static_cast<char*>(buffer);

    std::memcpy(pBuffer + offset, static_cast<char*>(data) + readPosition, numBytes);
    readPosition += numBytes;

    return numBytes;
}

size_t MemoryStream::Write(void *buffer, size_t offset, size_t numBytes)
{
    if (writePosition >= size)
        return 0; // Write position is out of range

    if (writePosition + numBytes > size)
        numBytes = size - writePosition; // Adjust the number of bytes to write to avoid going out of range

    char *pBuffer = static_cast<char*>(buffer);

    std::memcpy(static_cast<char*>(data) + writePosition, pBuffer + offset, numBytes);
    writePosition += numBytes;

    return numBytes;
}

ssize_t MemoryStream::Seek(ssize_t offset, SeekOrigin origin)
{
    if(!data)
        return -1;

    switch (origin)
    {
    case SeekOrigin::Begin:
        readPosition = std::max(static_cast<size_t>(0), std::min(static_cast<size_t>(offset), size));
        break;
    case SeekOrigin::Current:
        readPosition = std::max(static_cast<size_t>(0), std::min(readPosition + offset, size));
        break;
    case SeekOrigin::End:
        readPosition = std::max(static_cast<size_t>(0), std::min(size + offset, size));
        break;
    default:
        // Invalid seek origin
        return -1;
    }

    writePosition = readPosition; // Update write position as well

    return readPosition;
}


void MemoryStream::Dispose()
{
    if(ownsMemory && data)
    {
        unsigned char *ptr = static_cast<unsigned char*>(data);
        delete[] ptr;
        data = nullptr;
    }
}