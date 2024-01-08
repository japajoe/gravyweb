#ifndef HTTPCONTEXT_HPP
#define HTTPCONTEXT_HPP

#include "HttpStream.hpp"
#include "HttpRequest.hpp"

class HttpContext
{
private:
    HttpStream stream;
    HttpRequest request;
public:
    HttpContext(const HttpStream &stream, const HttpRequest &request);
    HttpStream *GetStream();
    HttpRequest *GetRequest();
};

#endif