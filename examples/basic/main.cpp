#include "HttpServer.hpp"

static HttpResponse OnHttpRequest(HttpContext *context);

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
        return HttpResponse(HttpStatusCode::OK, HttpContentType(HttpMediaType::TextHtml), "<h1>Hello world</h1>");
    else
        return HttpResponse(HttpStatusCode::NotFound);
}