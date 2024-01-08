#ifndef HTTPROUTEMAPPER_HPP
#define HTTPROUTEMAPPER_HPP

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include "HttpRoute.hpp"

class HttpRouteMapper
{
private:
    std::unordered_map<std::string, HttpRoute> routes;
public:
    HttpRouteMapper();
    HttpRoute *GetRoute(const std::string &url, bool allowInternal);

    template <typename ControllerType>
    void Add(const std::string &route, bool isInternal = false) 
    {
        if(routes.count(route) == 0)
        {
            auto task = []() { return std::make_unique<ControllerType>(); };
            routes[route] = HttpRoute(route, task, isInternal);
        }
    }
};

#endif