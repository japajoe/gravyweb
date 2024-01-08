#include "StringUtility.hpp"
#include <sstream>
#include <cctype> // For std::isspace
#include <algorithm> // For std::transform

bool StringUtility::StartsWith(const std::string& str, const std::string& suffix)
{
    if (str.length() >= suffix.length()) 
        return (0 == str.compare(0, suffix.length(), suffix));
    return false;
}

bool StringUtility::EndsWith(const std::string& str, const std::string& suffix)
{
    if (str.length() >= suffix.length()) 
        return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
    return false;
}

std::vector<std::string> StringUtility::ToLines(const std::string& str)
{
    std::vector<std::string> lines;
    std::istringstream iss(str);

    std::string line;
    while (std::getline(iss, line)) 
    {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> StringUtility::Split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter)) 
    {
        result.push_back(token);
    }

    return result;
}

std::string StringUtility::Trim(const std::string& str)
{
    // Find the first non-whitespace character from the beginning
    size_t start = str.find_first_not_of(" \t\n\r\f\v");

    // Find the last non-whitespace character from the end
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    // Handle the case where the string is all whitespace
    if (start == std::string::npos)
        return "";

    // Extract the substring between start and end
    return str.substr(start, end - start + 1);
}

std::string StringUtility::TrimStart(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");

    if (start == std::string::npos)
        return "";

    // Extract the substring starting from the first non-whitespace character
    return str.substr(start);
}

std::string StringUtility::TrimEnd(const std::string& str)
{
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    if (end == std::string::npos)
        return "";

    // Extract the substring from the beginning to the last non-whitespace character
    return str.substr(0, end + 1);
}

std::string StringUtility::ToLower(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string StringUtility::ToUpper(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

uint64_t StringUtility::ToUInt64(const std::string& str)
{
    try 
    {
        uint64_t value = std::stoull(str);
        return value;
    } 
    catch (const std::invalid_argument& e) 
    {
        return 0;
    }
    catch (const std::out_of_range& e) 
    {
        return 0;
    }
}

int64_t StringUtility::ToInt64(const std::string& str)
{
    try 
    {
        int64_t value = std::stoll(str);
        return value;
    } 
    catch (const std::invalid_argument& e) 
    {
        return 0;
    }
    catch (const std::out_of_range& e) 
    {
        return 0;
    }
}

bool StringUtility::Contains(const std::string &haystack, const std::string needle)
{
    return haystack.find(needle) != std::string::npos;
}

void StringUtility::Replace(std::string &original, const std::string &target, const std::string &replacement)
{
    size_t startPos = 0;

    while ((startPos = original.find(target, startPos)) != std::string::npos)
    {
        original.replace(startPos, target.length(), replacement);
        startPos += replacement.length();
    }
}