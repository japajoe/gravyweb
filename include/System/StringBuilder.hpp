#ifndef STRINGBUILDER_HPP
#define STRINGBUILDER_HPP

#include <string>
#include <sstream>

class StringBuilder
{
private:
    std::stringstream ss;
public:
    void Clear();
    std::string ToString() const;
    void Append(const std::string &value);
    void Append(int64_t value);
    void Append(uint64_t value);
    void Append(double value);
    void AppendLine(const std::string &value);
    void AppendLine(int64_t value);
    void AppendLine(uint64_t value);
    void AppendLine(double value);
};

#endif