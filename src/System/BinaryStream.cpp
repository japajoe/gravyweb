#include "BinaryStream.hpp"
#include "BitConverter.hpp"
#include <cstring>

BinaryStream::BinaryStream(unsigned char *buffer, size_t bufferSize, size_t length)
{
    SetBuffer(buffer, bufferSize, length);
}

unsigned char *BinaryStream::GetBuffer() const
{
    return buffer;
}

size_t BinaryStream::GetReadOffset() const
{
    return readOffset;
}

size_t BinaryStream::GetWriteOffset() const
{
    return writeOffset;
}

size_t BinaryStream::GetLength() const
{
    return length;
}

size_t BinaryStream::GetBufferSize() const
{
    return bufferSize;
}

void BinaryStream::SetBuffer(unsigned char *buffer, size_t bufferSize, size_t length)
{
    this->buffer = buffer;
    this->readOffset = 0;
    this->writeOffset = 0;
    this->length = length;
}

void BinaryStream::Reset()
{
    this->readOffset = 0;
    this->writeOffset = 0;
    this->length = 0;
}

void BinaryStream::SetReadOffset(size_t offset)
{
    this->readOffset = offset;
}

void BinaryStream::SetWriteOffset(size_t offset)
{
    this->writeOffset = offset;
}

void BinaryStream::AdvanceReadOffset(size_t size)
{
    this->readOffset += size;
}

void BinaryStream::AdvanceWriteOffset(size_t size)
{
    // only increase length if current length is equal to the current position
    if ((this->writeOffset + size) == (this->length + size))
        this->length += size;

    this->writeOffset += size;
}

void BinaryStream::Write(int64_t value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(int64_t));
}

void BinaryStream::Write(uint64_t value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(uint64_t));
}

void BinaryStream::Write(int32_t value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(int32_t));
}

void BinaryStream::Write(uint32_t value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(uint32_t));
}

void BinaryStream::Write(int16_t value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(int16_t));
}

void BinaryStream::Write(uint16_t value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(uint16_t));
}

void BinaryStream::Write(int8_t value)
{
    buffer[writeOffset] = value;
    AdvanceWriteOffset(sizeof(int8_t));
}

void BinaryStream::Write(uint8_t value)
{
    buffer[writeOffset] = value;
    AdvanceWriteOffset(sizeof(uint8_t));
}

void BinaryStream::Write(bool value)
{
    buffer[writeOffset] = value == false ? (uint8_t)0 : (uint8_t)1;
    AdvanceWriteOffset(sizeof(uint8_t));
}

void BinaryStream::Write(double value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(double));
}

void BinaryStream::Write(float value)
{
    BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(sizeof(float));
}

void BinaryStream::Write(const std::string &value)
{
    int numBytes = BitConverter::GetBytes(value, buffer, writeOffset);
    AdvanceWriteOffset(numBytes);
}

void BinaryStream::Write(const void *buffer, size_t length)
{
    memcpy(&this->buffer[writeOffset], buffer, length);
    AdvanceReadOffset(length);
}

int64_t BinaryStream::ReadInt64()
{
    int64_t value = BitConverter::ToInt64(buffer, readOffset);
    AdvanceReadOffset(sizeof(int64_t));
    return value;
}

uint64_t BinaryStream::ReadUInt64()
{
    uint64_t value = BitConverter::ToUInt64(buffer, readOffset);
    AdvanceReadOffset(sizeof(uint64_t));
    return value;
}

int32_t BinaryStream::ReadInt32()
{
    int32_t value = BitConverter::ToInt32(buffer, readOffset);
    AdvanceReadOffset(sizeof(int32_t));
    return value;
}

uint32_t BinaryStream::ReadUInt32()
{
    uint32_t value = BitConverter::ToUInt32(buffer, readOffset);
    AdvanceReadOffset(sizeof(uint32_t));
    return value;
}

int16_t BinaryStream::ReadInt16()
{
    int16_t value = BitConverter::ToInt16(buffer, readOffset);
    AdvanceReadOffset(sizeof(int16_t));
    return value;
}

uint16_t BinaryStream::ReadUInt16()
{
    uint16_t value = BitConverter::ToUInt16(buffer, readOffset);
    AdvanceReadOffset(sizeof(uint16_t));
    return value;
}

int8_t BinaryStream::ReadInt8()
{
    int8_t value = buffer[readOffset];
    AdvanceReadOffset(sizeof(int8_t));
    return value;
}

uint8_t BinaryStream::ReadUInt8()
{
    uint8_t value = buffer[readOffset];
    AdvanceReadOffset(sizeof(uint8_t));
    return value;
}

bool BinaryStream::ReadBool()
{
    bool value = buffer[readOffset] == 0 ? false : true;
    AdvanceReadOffset(sizeof(unsigned char));
    return value;
}

double BinaryStream::ReadDouble()
{
    double value = BitConverter::ToDouble(buffer, readOffset);
    AdvanceReadOffset(sizeof(double));
    return value;
}

float BinaryStream::ReadFloat()
{
    float value = BitConverter::ToSingle(buffer, readOffset);
    AdvanceReadOffset(sizeof(float));
    return value;
}

void BinaryStream::Read(void *buffer, size_t length)
{
    memcpy(buffer, &this->buffer[readOffset], length);
    AdvanceReadOffset(length);
}

std::string BinaryStream::ReadString(size_t length)
{
    std::string value = BitConverter::ToString(buffer, readOffset, length);
    AdvanceReadOffset(length);
    return value;
}