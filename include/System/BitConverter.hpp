#ifndef BITCONVERTER_HPP
#define BITCONVERTER_HPP

#include <cstdint>
#include <string>

typedef unsigned char byte;

class BitConverter
{
public:
    static bool IsLittleEndian();
    static void GetBytes(int64_t value, unsigned char * buffer, int offset);
    static void GetBytes(uint64_t value, unsigned char * buffer, int offset);
    static void GetBytes(int32_t value, unsigned char * buffer, int offset);
    static void GetBytes(uint32_t value, unsigned char * buffer, int offset);
    static void GetBytes(int16_t value, unsigned char * buffer, int offset);
    static void GetBytes(uint16_t value, unsigned char * buffer, int offset);
    static void GetBytes(double value, unsigned char * buffer, int offset);
    static void GetBytes(float value, unsigned char * buffer, int offset);
    static int GetBytes(const std::string &value, unsigned char * buffer, int offset);
    static int64_t ToInt64(unsigned char *bytes, int offset);
    static uint64_t ToUInt64(unsigned char *bytes, int offset);
    static int32_t ToInt32(unsigned char *bytes, int offset);
    static uint32_t ToUInt32(unsigned char *bytes, int offset);
    static int16_t ToInt16(unsigned char *bytes, int offset);
    static uint16_t ToUInt16(unsigned char *bytes, int offset);
    static float ToSingle(unsigned char *bytes, int offset);
    static double ToDouble(unsigned char *bytes, int offset);
    static std::string ToString(unsigned char *bytes, int offset, int length);
    static void FlipBytes(unsigned char *bytes, int offset, int length);
    static void FlipBytes(unsigned char* bytes, int length);
    static int GetByteCount(const std::string &value);
};

#endif