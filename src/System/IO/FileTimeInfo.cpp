#include "FileTimeInfo.hpp"

FileTimeInfo::FileTimeInfo()
{
    this->creationTime = DateTime::Now();
    this->lastWriteTime = DateTime::Now();
}

FileTimeInfo::FileTimeInfo(const FileInfo &info)
{
    this->creationTime = info.GetCreationTime();
    this->lastWriteTime = info.GetLastWriteTime();
}