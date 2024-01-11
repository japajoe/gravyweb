#ifndef BINARYSTREAM_HPP
#define BINARYSTREAM_HPP

#include <cstdint>
#include <string>

class BinaryStream
{
private:
    unsigned char *buffer;
    size_t readOffset;
    size_t writeOffset;
    size_t length;
    size_t bufferSize;
    void AdvanceReadOffset(size_t size);
    void AdvanceWriteOffset(size_t size);
public:
    BinaryStream(unsigned char *buffer, size_t bufferSize, size_t length = 0);
    unsigned char *GetBuffer() const;
    size_t GetReadOffset() const;
    size_t GetWriteOffset() const;
    size_t GetLength() const;
    size_t GetBufferSize() const;
    void SetBuffer(unsigned char *buffer, size_t bufferSize, size_t length = 0);
    void Reset();
    void SetReadOffset(size_t offset);
    void SetWriteOffset(size_t offset);
    void Write(int64_t value);
    void Write(uint64_t value);
    void Write(int32_t value);
    void Write(uint32_t value);
    void Write(int16_t value);
    void Write(uint16_t value);
    void Write(int8_t value);
    void Write(uint8_t value);
    void Write(bool value);
    void Write(double value);
    void Write(float value);
    void Write(const std::string &value);
    void Write(const void *buffer, size_t length);
    int64_t ReadInt64();
    uint64_t ReadUInt64();
    int32_t ReadInt32();
    uint32_t ReadUInt32();
    int16_t ReadInt16();
    uint16_t ReadUInt16();
    int8_t ReadInt8();
    uint8_t ReadUInt8();
    bool ReadBool();
    double ReadDouble();
    float ReadFloat();
    void Read(void *buffer, size_t length);
    std::string ReadString(size_t length);
};

#endif