#include "IndexController.hpp"
#include "HttpSettings.hpp"
#include "StringUtility.hpp"
#include <iostream>

HttpPageContent IndexController::content;

IndexController::IndexController()
{
    if(content.GetContent().size() == 0)
        content = HttpPageContent(HttpSettings::GetPrivateHtml() + "/template.html");
}

HttpResponse IndexController::OnGet(HttpContext *context)
{
    bool result = content.Load();

    std::string html = "Hello world";

    if(result)
    {
        html = content.GetContent();
        StringUtility::Replace(html, "$(title)", "Home - Swerva Web");
        StringUtility::Replace(html, "$(header_text)", "Home");
        StringUtility::Replace(html, "$(head)", "");
        StringUtility::Replace(html, "$(content)", "<p>Welcome to the home page</p>");
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