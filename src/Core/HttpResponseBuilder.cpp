#include "HttpResponseBuilder.hpp"

HttpResponseBuilder::HttpResponseBuilder()
{
    
}

void HttpResponseBuilder::BeginHeader(HttpStatusCode status)
{
    response = "HTTP/1.1 " + std::to_string(static_cast<int>(status)) + "\n";
}

void HttpResponseBuilder::AddHeader(const std::string &key, const std::string &value)
{
    response += key + ": " + value + "\n";
}

void HttpResponseBuilder::AddHeader(const std::string &key, size_t value)
{
    response += key + ": " + std::to_string(value) + "\n";
}

void HttpResponseBuilder::AddHeader(const std::string &key, ssize_t value)
{
    response += key + ": " + std::to_string(value) + "\n";
}

void HttpResponseBuilder::AddHeader(const std::string &key, float value)
{
    response += key + ": " + std::to_string(value) + "\n";
}

void HttpResponseBuilder::AddHeader(const std::string &key, double value)
{
    response += key + ": " + std::to_string(value) + "\n";
}

void HttpResponseBuilder::AddString(const std::string &str)
{
    response += str;
}

void HttpResponseBuilder::EndHeader()
{
    response += "\r\n";
}

void HttpResponseBuilder::Clear()
{
    response.clear();
}

const std::string &HttpResponseBuilder::Build() const
{
    return response;
}