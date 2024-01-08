#ifndef HTTPRESPONSEBUILDER_HPP
#define HTTPRESPONSEBUILDER_HPP

#include <string>
#include "HttpStatusCode.hpp"

class HttpResponseBuilder
{
private:
    std::string response;
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
    const std::string &Build() const;
};

#endif