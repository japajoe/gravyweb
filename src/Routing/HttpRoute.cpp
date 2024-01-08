#include "HttpRoute.hpp"
#include <iostream>

HttpRoute::HttpRoute()
{

}

HttpRoute::HttpRoute(const std::string &url, const std::function<std::unique_ptr<HttpController>()> &route, bool isInternal)
{
    this->url = url;
    this->route = route;
    this->isInternal = isInternal;
}

std::string HttpRoute::GetURL() const
{
    return url;
}

bool HttpRoute::IsInternal() const
{
    return isInternal;
}

HttpResponse HttpRoute::GetResponse(HttpContext *context)
{
    auto controller = route();

    HttpResponse response;

    switch(context->GetRequest()->GetMethod())
    {
        case HttpRequestMethod::Get:
            response = controller->OnGet(context);
            break;
        case HttpRequestMethod::Post:
            response = controller->OnPost(context);
            break;
        case HttpRequestMethod::Connect:
            response = controller->OnConnect(context);
            break;
        case HttpRequestMethod::Head:
            response = controller->OnHead(context);
            break;
        case HttpRequestMethod::Options:
            response = controller->OnOptions(context);
            break;
        case HttpRequestMethod::Patch:
            response = controller->OnPatch(context);
            break;
        case HttpRequestMethod::Delete:
            response = controller->OnDelete(context);
            break;
        case HttpRequestMethod::Put:
            response = controller->OnPut(context);
            break;
        case HttpRequestMethod::Trace:
            response = controller->OnTrace(context);
            break;
        case HttpRequestMethod::Unknown:
            response = HttpResponse(HttpStatusCode::NotImplemented);
            break;
    }

    return response;
}