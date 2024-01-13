#ifndef HTTPROUTEMAPPER_HPP
#define HTTPROUTEMAPPER_HPP

#include "HttpContext.hpp"
#include "HttpResponse.hpp"
#include <functional>
#include <regex>
#include <cstdint>
#include <vector>
#include <string>

using HttpRequestHandler = std::function<HttpResponse(HttpContext *context)>;

class HttpRequestHandlerInfo
{
public:
    HttpRequestMethod method;
    HttpRequestHandler handler;
    HttpMediaType mediaTypePolicy;
    uint64_t maxRequestBodySize;
    bool isInternal;
    HttpRequestHandlerInfo(const HttpRequestHandler &handler, HttpMediaType mediaTypePolicy = HttpMediaType::Unknown, uint64_t maxRequestBodySize = 0, bool isInternal = false);
    HttpResponse GetResponse(HttpContext *context);
};

class HttpRouteMapper
{
private:
    std::vector<std::pair<std::regex, HttpRequestHandlerInfo>> routes;
public:
    HttpRequestHandlerInfo *GetRoute(const std::string &url, bool allowInternal);
    void AddConnectHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddDeleteHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddGetHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddHeadHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddOptionsHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddPatchHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddPostHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddPutHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
    void AddTraceHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo);
};

#endif