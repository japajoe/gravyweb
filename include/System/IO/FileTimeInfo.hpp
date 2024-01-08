#ifndef FILETIMEINFO_HPP
#define FILETIMEINFO_HPP

#include "FileInfo.hpp"

class FileTimeInfo
{
public:
    DateTime creationTime;
    DateTime lastWriteTime;
    FileTimeInfo();
    FileTimeInfo(const FileInfo &info);
    DateTime GetCreationTime() const;
    DateTime GetLastWriteTime() const;
};

#endif