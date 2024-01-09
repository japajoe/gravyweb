#include "HttpRouteMapper.hpp"

HttpRoute *HttpRouteMapper::GetRoute(const std::string &url, bool allowInternal)
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

            if(route.second.IsInternal())
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