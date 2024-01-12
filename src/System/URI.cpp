#include "URI.hpp"
#include <regex>

URI::URI(const std::string &uriString)
{
    this->uri = uriString;
}

bool URI::GetScheme(std::string &value)
{
    std::regex schemeRegex(R"(([^:/?#]+):\/\/)");
    std::smatch match;
    if (std::regex_search(uri, match, schemeRegex)) 
    {
        value = match[1];
        return true;
    }
    return false;
}

bool URI::GetHost(std::string &value)
{
    std::regex hostRegex(R"(:\/\/([^/?#]+))");
    std::smatch match;
    if (std::regex_search(uri, match, hostRegex)) 
    {
        value = match[1];
        return true;
    }
    return false;
}

bool URI::GetPath(std::string &value)
{
    std::regex pathRegex(R"(:\/\/[^/?#]+([^?#]*))");
    std::smatch match;
    if (std::regex_search(uri, match, pathRegex)) 
    {
        value = match[1];
        return true;
    }
    return false;
}

bool URI::GetQuery(std::string &value)
{
    std::regex queryRegex(R"(\?([^#]*))");
    std::smatch match;
    if (std::regex_search(uri, match, queryRegex)) 
    {
        value = match[1];
        return true;
    }
    return false;
}

bool URI::GetFragment(std::string &value)
{
    std::regex fragmentRegex(R"(#(.*))");
    std::smatch match;
    if (std::regex_search(uri, match, fragmentRegex)) 
    {
        value = match[1];
        return true;
    }
    return false;
}