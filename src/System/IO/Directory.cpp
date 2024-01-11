#include "Directory.hpp"
#include <iostream>

// Check if the C++17 filesystem is available
#if __has_include(<filesystem>) && __cpp_lib_filesystem >= 201703
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

bool Directory::Exists(const std::string &path)
{
    fs::path directorypath = path;
    return fs::is_directory(directorypath);
}