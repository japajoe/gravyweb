#include "HttpController.hpp"

HttpController::HttpController()
{

}

HttpController::~HttpController()
{

}

HttpResponse HttpController::OnConnect(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnDelete(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnGet(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::NotFound, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnHead(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnOptions(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnPatch(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnPost(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnPut(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnTrace(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
}

HttpResponse HttpController::OnUnknown(HttpContext *context)
{
    return HttpResponse(HttpStatusCode::MethodNotAllowed, HttpContentType(HttpMediaType::TextHtml));
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