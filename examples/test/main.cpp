#include "HttpServer.hpp"
#include "HttpRouteMapper.hpp"
#include "HttpSettings.hpp"
#include "File.hpp"
#include "FileStream.hpp"
#include <memory>

static HttpResponse OnHttpRequest(HttpContext *context);
static HttpRouteMapper routeMapper;

int main(int argc, char **argv)
{
    HttpConfig config;
    
    if(!config.LoadFromFile("config.ini"))
    {
        return 1;
    }

    HttpRequestHandler indexHandler = [] (HttpContext *context) {
        return HttpResponse(HttpStatusCode::OK);
    };

    HttpRequestHandler notFoundHandler = [] (HttpContext *context) {
        return HttpResponse(HttpStatusCode::NotFound);
    };
    
    routeMapper.AddGetHandler("/", HttpRequestHandlerInfo(indexHandler));
    routeMapper.AddGetHandler("/home", HttpRequestHandlerInfo(indexHandler));
    routeMapper.AddGetHandler("/index", HttpRequestHandlerInfo(indexHandler));
    routeMapper.AddGetHandler("/404", HttpRequestHandlerInfo(notFoundHandler, HttpMediaType::Unknown, 0, true));

    HttpServer server(config);
    server.SetRequestHandler(OnHttpRequest);
    server.Run();

    return 0;
}

HttpResponse OnHttpRequest(HttpContext *context)
{
    auto route = routeMapper.GetRoute(context->GetRequest()->GetURL(), false);

    if(route)
        return route->GetResponse(context);

    std::string filepath = HttpSettings::GetPublicHtml() + context->GetRequest()->GetURL();

    if(File::Exists(filepath) && File::IsWithinDirectory(filepath, HttpSettings::GetPublicHtml()))
    {
        HttpContentType contentType = HttpContentType::GetContentTypeFromFileExtension(filepath);
        std::shared_ptr<FileStream> fileStream = std::make_shared<FileStream>(filepath, FileMode::Open, FileAccess::Read);
        HttpResponse response(HttpStatusCode::OK, contentType, fileStream);
        response.AddHeader("Cache-Control", "max-age=3600");
        return response;
    }
    else
    {
        route = routeMapper.GetRoute("/404", true);

        if(route)
            return route->GetResponse(context);
        else
            return HttpResponse(HttpStatusCode::NotFound);
    }
}
    
