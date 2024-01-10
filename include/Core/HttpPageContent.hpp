#ifndef HTTPPAGECONTENT_HPP
#define HTTPPAGECONTENT_HPP

#include <string>
#include "FileTimeInfo.hpp"
#include <unordered_map>

class HttpPageContent
{
private:
    std::string path;
    std::string content;
    FileTimeInfo fileInfo;
public:
    HttpPageContent();
    HttpPageContent(const std::string &path);
    bool Load();
    std::string GetPath() const;
    std::string GetContent() const;
    FileTimeInfo GetFileInfo() const;
};

#endif