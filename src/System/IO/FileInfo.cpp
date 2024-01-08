#include "FileInfo.hpp"
#include "File.hpp"
#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

static DateTime FromFileTime(const fs::file_time_type& fileTime)
{
    auto time = std::chrono::system_clock::to_time_t(fileTime);
    return DateTime(std::chrono::system_clock::from_time_t(time));
}

FileInfo::FileInfo(const std::string &filePath)
{
    try
    {
        // Check if the file exists
        if (!File::Exists(filePath))
        {
            std::cout << "File not found: " << filePath << std::endl;
            return;
        }

        // Print file information
        this->path = filePath;
        this->size = fs::file_size(filePath);

        // Convert file time points to local time
        auto creationTime = fs::last_write_time(filePath);
        auto writeTime = fs::last_write_time(filePath);
        
        this->creationTime = FromFileTime(creationTime);
        this->lastWriteTime = FromFileTime(writeTime);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

DateTime FileInfo::GetCreationTime() const
{
    return creationTime;
}

DateTime FileInfo::GetLastWriteTime() const
{
    return lastWriteTime;
}

size_t FileInfo::GetSize() const
{
    return size;
}

std::string FileInfo::GetPath() const
{
    return path;
}