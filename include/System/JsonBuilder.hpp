#ifndef JSONBUILDER_HPP
#define JSONBUILDER_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

class JsonBuilder
{
private:
    std::unordered_map<std::string, std::string> properties;
    std::string EscapeString(const std::string &str) const;
public:
    void AddProperty(const std::string &key, const std::string &value);
    void AddProperty(const std::string &key, const char *value); //Needed to resolve ambiguity between the std::string and bool overload when you pass a string literal
    void AddProperty(const std::string &key, int8_t value);
    void AddProperty(const std::string &key, uint8_t value);
    void AddProperty(const std::string &key, int16_t value);
    void AddProperty(const std::string &key, uint16_t value);
    void AddProperty(const std::string &key, int32_t value);
    void AddProperty(const std::string &key, uint32_t value);
    void AddProperty(const std::string &key, int64_t value);
    void AddProperty(const std::string &key, uint64_t value);
    void AddProperty(const std::string &key, float value);
    void AddProperty(const std::string &key, double value);
    void AddProperty(const std::string& key, bool value);
    void AddObject(const std::string &key, const JsonBuilder &obj);
    void AddArray(const std::string &key, const std::vector<std::string> &array);
    std::string ToString() const;
};

#endif