#include "HttpContext.hpp"

HttpContext::HttpContext(const HttpStream &stream, const HttpRequest &request)
{
    this->stream = stream;
    this->request = request;
}

HttpStream *HttpContext::GetStream()
{
    return &stream;
}

HttpRequest *HttpContext::GetRequest()
{
    return &request;
}