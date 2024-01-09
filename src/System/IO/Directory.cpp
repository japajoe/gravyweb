#include "Directory.hpp"

#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

bool Directory::Exists(const std::string &path)
{
    fs::path directorypath = path;
    return fs::is_directory(directorypath);
}