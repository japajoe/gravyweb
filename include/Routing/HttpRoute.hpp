#ifndef HTTPROUTE_HPP
#define HTTPROUTE_HPP

#include <functional>
#include <memory>
#include <string>
#include "HttpController.hpp"

class HttpRoute
{
private:
    std::string url;
    std::function<std::unique_ptr<HttpController>()> route;
    bool isInternal;
public:
    HttpRoute();
    HttpRoute(const std::string &url, const std::function<std::unique_ptr<HttpController>()> &route, bool isInternal);
    std::string GetURL() const;
    bool IsInternal() const;
    HttpResponse GetResponse(HttpContext *context);
};

#endif