#ifndef FILEINFO_HPP
#define FILEINFO_HPP

#include <string>
#include "DateTime.hpp"

class FileInfo
{
private:
    DateTime creationTime;
    DateTime lastWriteTime;
    size_t size;
    std::string path;
public:
    FileInfo(const std::string &filePath);
    DateTime GetCreationTime() const;
    DateTime GetLastWriteTime() const;
    size_t GetSize() const;
    std::string GetPath() const;
};

#endif