#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>

class Directory
{
public:
    static bool Exists(const std::string &path);
};

#endif