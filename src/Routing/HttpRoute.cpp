#include "HttpRoute.hpp"
#include "HttpSettings.hpp"

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

    size_t maxRequestBodySize = controller->GetMaxRequestBodySize();

    if(maxRequestBodySize > 0 && maxRequestBodySize != HttpSettings::GetMaxRequestBodySize())
    {
        if(context->GetRequest()->GetContentLength() > maxRequestBodySize)
            return HttpResponse(HttpStatusCode::PayloadTooLarge);
    }
    else
    {
        if(context->GetRequest()->GetContentLength() > HttpSettings::GetMaxRequestBodySize())
            return HttpResponse(HttpStatusCode::PayloadTooLarge);
    }

    switch(context->GetRequest()->GetMethod())
    {
        case HttpRequestMethod::Get:
            return controller->OnGet(context);
        case HttpRequestMethod::Post:
            return controller->OnPost(context);
        case HttpRequestMethod::Connect:
            return controller->OnConnect(context);
        case HttpRequestMethod::Head:
            return controller->OnHead(context);
        case HttpRequestMethod::Options:
            return controller->OnOptions(context);
        case HttpRequestMethod::Patch:
            return controller->OnPatch(context);
        case HttpRequestMethod::Delete:
            return controller->OnDelete(context);
        case HttpRequestMethod::Put:
            return controller->OnPut(context);
        case HttpRequestMethod::Trace:
            return controller->OnTrace(context);
        default:
            return HttpResponse(HttpStatusCode::NotImplemented);
    }
}