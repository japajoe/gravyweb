#include "HttpApplication.hpp"
#include "HttpSettings.hpp"
#include "APIController.hpp"
#include "ContactController.hpp"
#include "ExampleController.hpp"
#include "IndexController.hpp"
#include "NotFoundController.hpp"
#include "File.hpp"
#include "FileStream.hpp"
#include <experimental/filesystem>

#include "Console.hpp"

namespace fs = std::experimental::filesystem;

HttpApplication::HttpApplication(const HttpConfig &config)
{
    server = std::make_unique<HttpServer>(config);    
    
    auto requestHandler = [this] (HttpContext *context) {
        return OnRequest(context);
    };

    server->SetRequestHandler(requestHandler);

    routeMapper = std::make_unique<HttpRouteMapper>();
    routeMapper->Add<APIController>("/api/v1");
    routeMapper->Add<ContactController>("/contact");
    routeMapper->Add<ExampleController>("/example");
    routeMapper->Add<IndexController>("/");
    routeMapper->Add<IndexController>("/home");
    routeMapper->Add<IndexController>("/index");
    routeMapper->Add<NotFoundController>("/404", true);
}

void HttpApplication::Run()
{
    server->Run();
}

HttpResponse HttpApplication::OnRequest(HttpContext *context)
{
    HttpRoute *route = routeMapper->GetRoute(context->GetRequest()->GetURL(), false);

    if(route)
    {
        return route->GetResponse(context);
    }
    else
    {
        std::string filepath = HttpSettings::GetPublicHtml() + context->GetRequest()->GetURL();

        if(File::Exists(filepath) && IsPathWithinDirectory(filepath, HttpSettings::GetPublicHtml()))
        {
            HttpContentType contentType = HttpContentType::GetContentTypeFromFileExtension(filepath);
            std::shared_ptr<FileStream> fileStream = std::make_shared<FileStream>(filepath, FileMode::Open, FileAccess::Read);
            HttpResponse response(HttpStatusCode::OK, contentType, fileStream);
            response.AddHeader("Cache-Control", "max-age=3600");
            return response;
        }
        else
        {
            route = routeMapper->GetRoute("/404", true);

            if(route)
            {
                std::cout << "/404 found\n";
                return route->GetResponse(context);
            }
            else
            {
                std::cout << "/404 not found\n";
                return HttpResponse(HttpStatusCode::NotFound);
            }
        }
    }
}

bool HttpApplication::IsPathWithinDirectory(const std::string &path, const std::string &directory)
{
    fs::path directoryPath = fs::absolute(directory);
    fs::path filePath = fs::absolute(path);

    auto const normRoot = fs::canonical(directoryPath);
    auto const normChild = fs::canonical(filePath);
    
    auto itr = std::search(normChild.begin(), normChild.end(), 
                           normRoot.begin(), normRoot.end());
    
    return itr == normChild.begin();
}