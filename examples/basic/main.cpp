#include "HttpServer.hpp"
#include "Console.hpp"

HttpResponse OnHttpRequest(HttpContext *context);

int main(int argc, char **argv)
{
    HttpConfig config;
    
    if(!config.LoadFromFile("config.ini"))
    {
        return 1;
    }

    HttpServer server(config);
    server.SetRequestHandler(OnHttpRequest);
    server.Run();
    return 0;
}

HttpResponse OnHttpRequest(HttpContext *context)
{
    if(context->GetRequest()->GetURL() == "/")
        return HttpResponse(HttpStatusCode::OK, HttpContentType(HttpMediaType::TextPlain), "Hello world");
    else
        return HttpResponse(HttpStatusCode::NotFound);
}