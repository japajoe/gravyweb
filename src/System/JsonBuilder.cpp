#include "JsonBuilder.hpp"

void JsonBuilder::AddProperty(const std::string &key, const std::string &value)
{
    properties[key] = "\"" + EscapeString(value) + "\"";
}

void JsonBuilder::AddProperty(const std::string &key, const char *value)
{
    properties[key] = "\"" + EscapeString(value) + "\"";
}

void JsonBuilder::AddProperty(const std::string &key, int8_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, uint8_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, int16_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, uint16_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, int32_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, uint32_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, int64_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, uint64_t value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, float value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, double value)
{
    properties[key] = std::to_string(value);
}

void JsonBuilder::AddProperty(const std::string &key, bool value)
{
    properties[key] = value ? "true" : "false";
}

void JsonBuilder::AddObject(const std::string &key, const JsonBuilder &obj)
{
    properties[key] = obj.ToString();
}

void JsonBuilder::AddArray(const std::string &key, const std::vector<std::string> &array)
{
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < array.size(); ++i)
    {
        if (i > 0)
            ss << ",";
        ss << "\"" << EscapeString(array[i]) << "\"";
    }
    ss << "]";
    properties[key] = ss.str();
}

std::string JsonBuilder::ToString() const
{
    std::stringstream ss;
    ss << "{";
    bool first = true;
    for (const auto &pair : properties)
    {
        if (!first)
            ss << ",";
        ss << "\"" << pair.first << "\":" << pair.second;
        first = false;
    }
    ss << "}";
    return ss.str();
}

std::string JsonBuilder::EscapeString(const std::string &str) const
{
    std::string result;
    for (char c : str)
    {
        if (c == '\"' || c == '\\' || c == '/')
        {
            result += '\\';
        }
        result += c;
    }
    return result;
}