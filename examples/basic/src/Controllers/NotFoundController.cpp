#include "NotFoundController.hpp"
#include "HttpSettings.hpp"
#include "StringUtility.hpp"
#include <iostream>

HttpPageContent NotFoundController::content;

NotFoundController::NotFoundController()
{
    if(content.GetContent().size() == 0)
        content = HttpPageContent(HttpSettings::GetPrivateHtml() + "/template.html");
}

HttpResponse NotFoundController::OnGet(HttpContext *context)
{
    bool result = content.Load();

    std::string html = "Hello world";

    if(result)
    {
        html = content.GetContent();
        StringUtility::Replace(html, "$(title)", "Not Found - Gravy Web");
        StringUtility::Replace(html, "$(header_text)", "Error 404");
        StringUtility::Replace(html, "$(head)", "");
        StringUtility::Replace(html, "$(content)", "<p>The requested document was not found</p>");
    }
    else
    {
        html =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Gravy Web</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Whoops 404 Not Found</h1>\n"
        "</body>\n"
        "</html>";        
    }

    HttpResponse response(HttpStatusCode::NotFound, HttpContentType(HttpMediaType::TextHtml), html);
    response.AddHeader("Cache-Control", "max-age=3600");
    return response;
}