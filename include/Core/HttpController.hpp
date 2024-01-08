#ifndef HTTPCONTROLLER_HPP
#define HTTPCONTROLLER_HPP

#include "HttpContext.hpp"
#include "HttpResponse.hpp"

class HttpController
{
public:
    HttpController();
    virtual ~HttpController();
    virtual HttpResponse OnConnect(HttpContext *context);
    virtual HttpResponse OnDelete(HttpContext *context);
    virtual HttpResponse OnGet(HttpContext *context);
    virtual HttpResponse OnHead(HttpContext *context);
    virtual HttpResponse OnOptions(HttpContext *context);
    virtual HttpResponse OnPatch(HttpContext *context);
    virtual HttpResponse OnPost(HttpContext *context);
    virtual HttpResponse OnPut(HttpContext *context);
    virtual HttpResponse OnTrace(HttpContext *context);
    virtual HttpResponse OnUnknown(HttpContext *context);
protected:
    std::string ReadContentAsString(HttpContext *context);
};

#endif