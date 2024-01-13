#include "HttpRouteMapper.hpp"
#include "HttpSettings.hpp"

HttpRequestHandlerInfo::HttpRequestHandlerInfo(const HttpRequestHandler &handler, HttpMediaType mediaTypePolicy, uint64_t maxRequestBodySize, bool isInternal)
{
    this->handler = handler;
    if(maxRequestBodySize == 0)
        this->maxRequestBodySize = HttpSettings::GetMaxRequestBodySize();
    else
        this->maxRequestBodySize = maxRequestBodySize;
    this->mediaTypePolicy = mediaTypePolicy;
    this->isInternal = isInternal;
}

HttpResponse HttpRequestHandlerInfo::GetResponse(HttpContext *context)
{
    if(context->GetRequest()->GetMethod() != method)
        return HttpResponse(HttpStatusCode::MethodNotAllowed);

    uint64_t contentSize = context->GetRequest()->GetContentLength();

    if(maxRequestBodySize > 0 && maxRequestBodySize != HttpSettings::GetMaxRequestBodySize())
    {
        if(contentSize > maxRequestBodySize)
            return HttpResponse(HttpStatusCode::PayloadTooLarge);
    }
    else
    {
        if(contentSize > HttpSettings::GetMaxRequestBodySize())
            return HttpResponse(HttpStatusCode::PayloadTooLarge);
    }

    HttpMediaType mediaType = context->GetRequest()->GetContentType().GetMediaType();

    if(contentSize > 0)
    {
        if(mediaTypePolicy != HttpMediaType::Unknown && mediaType != mediaTypePolicy)
            return HttpResponse(HttpStatusCode::BadRequest);
    }

    if(handler)
        return handler(context);
    
    return HttpResponse(HttpStatusCode::NotImplemented);
}

#include <iostream>

HttpRequestHandlerInfo *HttpRouteMapper::GetRoute(const std::string &url, bool allowInternal)
{
    for (auto& route : routes) 
    {
        std::smatch match;
        if (std::regex_match(url, match, route.first))
        {
            // Not sure yet about this...
            // std::unordered_map<std::string, std::string> params;
            // for (size_t i = 1; i < match.size(); ++i) 
            // {
            //     params["$" + std::to_string(i)] = match[i].str();
            // }

            if(route.second.isInternal)
            {
                if(allowInternal)
                    return &route.second;
                return nullptr;
            }

            return &route.second;
        }
    }

    return nullptr;
}

void HttpRouteMapper::AddConnectHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Connect;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddDeleteHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Delete;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddGetHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Get;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddHeadHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Head;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddOptionsHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Options;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddPatchHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Patch;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddPostHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Post;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddPutHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Put;
    routes.emplace_back(std::regex(route), handlerInfo);
}

void HttpRouteMapper::AddTraceHandler(const std::string &route, const HttpRequestHandlerInfo &handlerInfo)
{
    const_cast<HttpRequestHandlerInfo*>(&handlerInfo)->method = HttpRequestMethod::Trace;
    routes.emplace_back(std::regex(route), handlerInfo);
}
