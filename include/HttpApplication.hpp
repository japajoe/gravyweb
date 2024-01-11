#ifndef HTTPAPPLICATION_HPP
#define HTTPAPPLICATION_HPP

#include "HttpServer.hpp"
#include "HttpRouteMapper.hpp"
#include <memory>

class HttpApplication
{
private:
    std::unique_ptr<HttpServer> server;
    std::unique_ptr<HttpRouteMapper> routeMapper;
    HttpResponse OnRequest(HttpContext *context);
public:
    HttpApplication(const HttpConfig &config);
    void Run();
};

#endif