#include "ContactController.hpp"
#include "HttpSettings.hpp"
#include "StringUtility.hpp"
#include <iostream>

HttpPageContent ContactController::content;

ContactController::ContactController()
{
    if(content.GetContent().size() == 0)
        content = HttpPageContent(HttpSettings::GetPrivateHtml() + "/template.html");    
}

std::string ContactController::CreateContent() const
{
    std::string html;

    if(content.Load())
    {
        html = content.GetContent();
        StringUtility::Replace(html, "$(title)", "Contact - Gravy Web");
        StringUtility::Replace(html, "$(header_text)", "Contact");
        StringUtility::Replace(html, "$(head)", "");
        StringUtility::Replace(html, "$(content)", "<p>Contact me on <a href=\"https://github.com/japajoe\" target=\"blank\">GitHub</a></p>");
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
        "    <h1>Contact</h1>\n"
        "</body>\n"
        "</html>";           
    }

    return html;
}

HttpResponse ContactController::OnGet(HttpContext *context)
{
    std::string html = CreateContent();
    HttpResponse response(HttpStatusCode::OK, HttpContentType(HttpMediaType::TextHtml), html);
    response.AddHeader("Cache-Control", "max-age=3600");
    return response;
}