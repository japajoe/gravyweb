#ifndef HASHCODE_HPP
#define HASHCODE_HPP

#include <cstdint>
#include <cstdlib>

enum class HashAlgorithm
{
    DJB2,
    SDBM
};

class HashCode
{
private:
    static uint64_t GetDJB2(const void *data, size_t size);
    static uint64_t GetSDBM(const void *data, size_t size);
public:
    static uint64_t Get(const void *data, size_t size, HashAlgorithm algorithm = HashAlgorithm::SDBM);
};

#endif