#include "HttpController.hpp"

HttpController::HttpController()
{

}

HttpController::~HttpController()
{

}

HttpResponse HttpController::OnConnect(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

HttpResponse HttpController::OnDelete(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

HttpResponse HttpController::OnGet(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::NotFound);
}

HttpResponse HttpController::OnHead(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::NotFound);
}

HttpResponse HttpController::OnOptions(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

HttpResponse HttpController::OnPatch(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

HttpResponse HttpController::OnPost(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

HttpResponse HttpController::OnPut(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

HttpResponse HttpController::OnTrace(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

HttpResponse HttpController::OnUnknown(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed);
}

void HttpController::SetMaxRequestBodySize(uint64_t size)
{
    maxRequestBodySize = size;
}

uint64_t HttpController::GetMaxRequestBodySize() const
{
    return maxRequestBodySize;
}

std::string HttpController::ReadContentAsString(HttpContext *context)
{
    unsigned char buffer[1024];
    std::string payload;

    if(context->GetRequest()->GetContentLength() > 0)
    {
        uint64_t bytesRead = 0;
        
        while(bytesRead < context->GetRequest()->GetContentLength())
        {
            int numBytes = context->GetStream()->Read(buffer, 0, 1024);
            if(numBytes > 0)
            {
                char *buf = reinterpret_cast<char*>(buffer);
                payload += std::string(buf, numBytes);
            }
            bytesRead += numBytes;
        }

        return payload;
    }

    return payload;
}