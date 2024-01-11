#include "File.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <iostream>
#include <algorithm>

// Check if the C++17 filesystem is available
#if __has_include(<filesystem>) && __cpp_lib_filesystem >= 201703
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

const char DirectorySeparatorChar = '\\';
const char AltDirectorySeparatorChar = '/';
const char VolumeSeparatorChar = ':';

File::File()
{
}

File::File(const std::string &path)
{
    this->path = path;

    if (File::Exists(path))
    {
        name = File::GetName(path);
        extension = File::GetExtension(path);
        size = File::GetSize(path);
    }
}

std::string File::GetPath() const
{
    return path;
}

std::string File::GetName() const
{
    return name;
}

std::string File::GetExtension() const
{
    return extension;
}

size_t File::GetSize() const
{
    return size;
}

std::string File::ReadAllText(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string str;
    std::string file_contents;

    while (std::getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }

    if (file.is_open())
        file.close();
    return file_contents;
}

std::vector<std::string> File::ReadAllLines(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string str;
    std::vector<std::string> lines;

    while (std::getline(file, str))
    {
        lines.push_back(str);
    }

    if (file.is_open())
        file.close();
    return lines;
}

std::vector<unsigned char> File::ReadAllBytes(const std::string &filepath)
{
    std::vector<unsigned char> bytes;
    std::ifstream file(filepath, std::ios_base::in | std::ios_base::binary);
    unsigned char ch = file.get();

    while (file.good())
    {
        bytes.push_back(ch);
        ch = file.get();
    }

    file.close();
    return bytes;
}

void File::WriteAllText(const std::string &filepath, const std::string &text)
{
    // std::ofstream outfile;
    // std::string file(filepath);
    // outfile << text;
    // outfile.close();
    std::ofstream file(filepath, std::ios_base::out);
    if (file.is_open())
    {
        file << text; // Write text to file
        file.close();
    }
}

void File::WriteLine(const std::string &filepath, const std::string &text)
{
    std::ofstream file(filepath, std::ios_base::app); // Open file for appending
    if (file.is_open())
    {
        file << text << '\n'; // Write text to file
        file.close();
    }

    // std::ofstream outfile;
    // std::string file(filepath);
    // outfile.open(file, std::ios_base::openmode::_S_ios_openmode_end);
    // outfile << text;
    // outfile.close();
}

void File::WriteAllBytes(const std::string &filepath, unsigned char *bytes, size_t size)
{
    std::ofstream file(filepath, std::ios::binary);

    if (file)
    {
        file.write(reinterpret_cast<const char *>(bytes), size);
    }

    if (file.is_open())
        file.close();
}

size_t File::GetSize(const std::string &filepath)
{
    return fs::file_size(filepath);
}

bool File::Exists(const std::string &filepath)
{
    return fs::exists(filepath) && fs::is_regular_file(filepath);
}

bool File::IsWithinDirectory(const std::string &path, const std::string &directory)
{
    fs::path directoryPath = fs::absolute(directory);
    fs::path filePath = fs::absolute(path);

    auto const normRoot = fs::canonical(directoryPath);
    auto const normChild = fs::canonical(filePath);
    
    auto itr = std::search(normChild.begin(), normChild.end(), 
                           normRoot.begin(), normRoot.end());
    
    return itr == normChild.begin();
}

std::string File::GetName(const std::string &filepath)
{
    if (filepath.size() > 0)
    {
        size_t length = filepath.size();

        for (size_t i = length; --i > 0;)
        {
            char ch = filepath[i];

            if (ch == DirectorySeparatorChar || ch == AltDirectorySeparatorChar || ch == VolumeSeparatorChar)
            {
                return filepath.substr(i + 1, length - i - 1);
            }
        }
    }
    return filepath;
}

std::string File::GetExtension(const std::string &filepath)
{
    if (filepath.size() == 0)
        return "";

    size_t length = filepath.size();

    for (int i = length; --i > 0;)
    {
        char ch = filepath[i];

        if (ch == '.')
        {
            if (i != length - 1)
                return filepath.substr(i, length - i);
            else
                return "";
        }

        if (ch == DirectorySeparatorChar || ch == AltDirectorySeparatorChar || ch == VolumeSeparatorChar)
            break;
    }

    return "";
}