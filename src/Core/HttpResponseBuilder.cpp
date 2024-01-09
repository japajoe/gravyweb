#include "HttpResponseBuilder.hpp"

HttpResponseBuilder::HttpResponseBuilder()
{
    
}

void HttpResponseBuilder::BeginHeader(HttpStatusCode status)
{
    sb.AppendLine("HTTP/1.1 " + std::to_string(static_cast<int>(status)));
}

void HttpResponseBuilder::AddHeader(const std::string &key, const std::string &value)
{
    sb.AppendLine(key + ": " + value);
}

void HttpResponseBuilder::AddHeader(const std::string &key, size_t value)
{
    sb.AppendLine(key + ": " + std::to_string(value));
}

void HttpResponseBuilder::AddHeader(const std::string &key, ssize_t value)
{
    sb.AppendLine(key + ": " + std::to_string(value));
}

void HttpResponseBuilder::AddHeader(const std::string &key, float value)
{
    sb.AppendLine(key + ": " + std::to_string(value));
}

void HttpResponseBuilder::AddHeader(const std::string &key, double value)
{
    sb.AppendLine(key + ": " + std::to_string(value));
}

void HttpResponseBuilder::AddString(const std::string &str)
{
    sb.Append(str);
}

void HttpResponseBuilder::EndHeader()
{
    sb.Append("\r\n");
}

void HttpResponseBuilder::Clear()
{
    sb.Clear();
}

std::string HttpResponseBuilder::ToString() const
{
    return sb.ToString();
}