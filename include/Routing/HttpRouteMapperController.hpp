#ifndef HTTPROUTEMAPPERCONTROLLER_HPP
#define HTTPROUTEMAPPERCONTROLLER_HPP

#include "HttpRoute.hpp"
#include <functional>
#include <memory>
#include <string>
#include <regex>
#include <vector>

class HttpRouteMapperController
{
private:
    std::vector<std::pair<std::regex, HttpRoute>> routes;
public:
    HttpRoute *GetRoute(const std::string &url, bool allowInternal);

    template <typename ControllerType>
    void Add(const std::string &route, bool isInternal = false) 
    {
        auto task = []() { return std::make_unique<ControllerType>(); };
        routes.emplace_back(std::regex(route), HttpRoute(route, task, isInternal));
    }
};



#endif