#include "HttpRouteMapper.hpp"

HttpRouteMapper::HttpRouteMapper()
{
    
}

HttpRoute *HttpRouteMapper::GetRoute(const std::string &url, bool allowInternal)
{
    auto it = routes.find(url);

    if(it != routes.end())
    {
        if(it->second.IsInternal())
        {
            if(allowInternal)
            {
                return &it->second;
            }
            return nullptr;
        }
        return &it->second;
    }

    return nullptr;
}
