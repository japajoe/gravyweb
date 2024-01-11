#include "HashCode.hpp"

//Reference material: http://www.cse.yorku.ca/~oz/hash.html

uint64_t HashCode::Get(const void *data, size_t size, HashAlgorithm algorithm)
{
    switch(algorithm)
    {
        case HashAlgorithm::DJB2:
            return GetDJB2(data, size);
        case HashAlgorithm::SDBM:
            return GetSDBM(data, size);
        default:
            return GetSDBM(data, size);
    }
}

uint64_t HashCode::GetDJB2(const void *data, size_t size)
{
    uint8_t *d = reinterpret_cast<uint8_t*>(const_cast<void*>(data));
    uint64_t hash = 5381;
    int32_t c;

    for(size_t i = 0; i < size; i++)
    {
        c = d[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

uint64_t HashCode::GetSDBM(const void *data, size_t size)
{
    uint8_t *d = reinterpret_cast<uint8_t*>(const_cast<void*>(data));
    uint64_t hash = 0;
    int32_t c;

    for(size_t i = 0; i < size; i++)
    {
        c = d[i];
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}