#include "BitConverter.hpp"
#include <cstring>

bool BitConverter::IsLittleEndian()
{
    uint32_t i = 1;
    unsigned char* c = reinterpret_cast<unsigned char*>(&i);
    return *c > 0;
}

void BitConverter::GetBytes(int64_t value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(int64_t));
}

void BitConverter::GetBytes(uint64_t value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(uint64_t));
}

void BitConverter::GetBytes(int32_t value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(int32_t));
}        

void BitConverter::GetBytes(uint32_t value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(uint32_t));
}

void BitConverter::GetBytes(int16_t value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(int16_t));
}

void BitConverter::GetBytes(uint16_t value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(uint16_t));
}

void BitConverter::GetBytes(double value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(double));
}

void BitConverter::GetBytes(float value, unsigned char * buffer, int offset)
{
    memcpy(&buffer[offset], &value, sizeof(float));
}

int BitConverter::GetBytes(const std::string &value, unsigned char * buffer, int offset)
{
    char *chars = const_cast<char*>(value.c_str());
    memcpy(&buffer[offset], chars, value.length());
    return value.length();
}

int64_t BitConverter::ToInt64(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<int64_t*>(&bytes[offset]);
}

uint64_t BitConverter::ToUInt64(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<uint64_t*>(&bytes[offset]);
}

int32_t BitConverter::ToInt32(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<int32_t*>(&bytes[offset]);
}

uint32_t BitConverter::ToUInt32(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<uint32_t*>(&bytes[offset]);
}

int16_t BitConverter::ToInt16(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<int16_t*>(&bytes[offset]);
}

uint16_t BitConverter::ToUInt16(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<uint16_t*>(&bytes[offset]);
}

float BitConverter::ToSingle(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<float*>(&bytes[offset]);
}

double BitConverter::ToDouble(unsigned char *bytes, int offset)
{
    return *reinterpret_cast<double*>(&bytes[offset]);
}

std::string BitConverter::ToString(unsigned char *bytes, int offset, int length)
{
    char *characters = reinterpret_cast<char*>(&bytes[offset]);
    std::string result(characters, length);
    return result;
}

void BitConverter::FlipBytes(unsigned char *bytes, int offset, int length)
{
    FlipBytes(&bytes[offset], length);
}

void BitConverter::FlipBytes(unsigned char* bytes, int length)
{
    for (int i = 0; i < length / 2; ++i) 
    {
        unsigned char t = bytes[i];
        bytes[i] = bytes[length - i - 1];
        bytes[length - i - 1] = t;
    }
}

int BitConverter::GetByteCount(const std::string &value)
{
    return value.length();
}