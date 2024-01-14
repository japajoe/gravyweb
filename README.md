# gravyweb
An HTTP web server implementation with support for HTTPS.

# Disclaimer
I am not an authority in the field of web servers. This project is just for fun and educational purposes, so use at your own discretion.

# Features
- HTTP request parsing
- HTTP to HTTPS forwarding
- Create routes and controllers for different request methods (support for regular expressions too)
- Easy to use HTTP response creation
- [Example website](https://github.com/japajoe/gravyweb/tree/main/www) included

# Dependencies
You're required to install OpenSSL development libraries. I have created this project on Linux and have only done limited testing with MinGW to test for Windows compatibility. In theory you need to link with OpenSSL and ws2_32 (Winsock2) if you want to try this. To be more specific, you need to link against `libssl`, `libcrypto`, `libbcrypt` and `ws2_32`. If you want to have support for HTTPS, you need to provide a certicate. To generate a self signed certificate use following command `openssl req -newkey rsa:4096 -x509 -sha256 -days 3650 -nodes -out cert.pem -keyout key.pem`. After creating a certificate, be sure to update the settings in config.txt.

# Example
The library uses a callback to intercept http requests. The important thing is to always return an `HttpResponse` from the callback. You can handle the request any way you like, and implement your own routing mechanism depending on your needs. The example below shows the most simple way of how to handle an incoming http request. For more examples look [here](https://github.com/japajoe/gravyweb/tree/main/examples).
```cpp
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
```