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

HttpResponse ContactController::OnGet(HttpContext *context)
{
    bool result = content.Load();

    std::string html = "Hello world";

    if(result)
    {
        html = content.GetContent();
        StringUtility::Replace(html, "$(title)", "Contact - Swerva Web");
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
        "    <title>Swerva Web</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Home</h1>\n"
        "</body>\n"
        "</html>";           
    }

    HttpResponse response(HttpStatusCode::OK, HttpContentType(HttpMediaType::TextHtml), html);
    response.AddHeader("Cache-Control", "max-age=60");
    return response;
}