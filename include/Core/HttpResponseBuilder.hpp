#ifndef HTTPRESPONSEBUILDER_HPP
#define HTTPRESPONSEBUILDER_HPP

#include <string>
#include "HttpStatusCode.hpp"
#include "StringBuilder.hpp"

class HttpResponseBuilder
{
private:
    StringBuilder sb;
public:
    HttpResponseBuilder();
    void BeginHeader(HttpStatusCode status);
    void AddHeader(const std::string &key, const std::string &value);
    void AddHeader(const std::string &key, size_t value);
    void AddHeader(const std::string &key, ssize_t value);
    void AddHeader(const std::string &key, float value);
    void AddHeader(const std::string &key, double value);
    void AddString(const std::string &str);
    void EndHeader();
    void Clear();
    std::string ToString() const;
};

#endif