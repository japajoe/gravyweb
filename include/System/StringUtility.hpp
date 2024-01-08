#ifndef STRINGUTILITY_HPP
#define STRINGUTILITY_HPP

#include <string>
#include <vector>

class StringUtility
{
public:
    static bool StartsWith(const std::string& str, const std::string& suffix);
    static bool EndsWith(const std::string& str, const std::string& suffix);
    static std::vector<std::string> ToLines(const std::string& str);
    static std::vector<std::string> Split(const std::string& str, char delimiter);
    static std::string Trim(const std::string& str);
    static std::string TrimStart(const std::string& str);
    static std::string TrimEnd(const std::string& str);
    static std::string ToLower(const std::string& str);
    static std::string ToUpper(const std::string& str);
    static uint64_t ToUInt64(const std::string& str);
    static int64_t ToInt64(const std::string& str);
    static bool Contains(const std::string &haystack, const std::string needle);
    static void Replace(std::string &original, const std::string &target, const std::string &replacement);
};

#endif