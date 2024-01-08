#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include "TcpListener.hpp"
#include "HttpConfig.hpp"
#include "HttpContext.hpp"
#include "HttpStream.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpStream.hpp"
#include <atomic>
#include <functional>

using HttpRequestCallback = std::function<HttpResponse(HttpContext*)>;

class HttpServer
{
private:
    std::atomic<bool> isRunning;
    HttpRequestCallback requestCallback;
    void HandleHttp();
    void HandleHttps();
    void HandleRequest(HttpStream stream);
    int32_t ReadHeader(HttpStream *stream, std::string &header);
public:
    HttpServer(const HttpConfig &config);
    void Run();
    void SetRequestHandler(HttpRequestCallback callback);
};

#endif