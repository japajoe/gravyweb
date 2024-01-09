#include "StringBuilder.hpp"

void StringBuilder::Clear()
{
    ss.clear();
}

std::string StringBuilder::ToString() const
{
    return ss.str();
}

void StringBuilder::Append(const std::string &value)
{
    ss << value;
}

void StringBuilder::Append(int64_t value)
{
    ss << std::to_string(value);
}

void StringBuilder::Append(uint64_t value)
{
    ss << std::to_string(value);
}

void StringBuilder::Append(double value)
{
    ss << std::to_string(value);
}

void StringBuilder::AppendLine(const std::string &value)
{
    ss << value << '\n';
}

void StringBuilder::AppendLine(int64_t value)
{
    ss << std::to_string(value) << '\n';
}

void StringBuilder::AppendLine(uint64_t value)
{
    ss << std::to_string(value) << '\n';
}

void StringBuilder::AppendLine(double value)
{
    ss << std::to_string(value) << '\n';
}