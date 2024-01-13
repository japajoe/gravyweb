#include "ExampleController.hpp"
#include "HttpSettings.hpp"
#include "StringUtility.hpp"
#include "StringBuilder.hpp"
#include <iostream>

HttpPageContent ExampleController::content;

ExampleController::ExampleController()
{
    if(content.GetContent().size() == 0)
        content = HttpPageContent(HttpSettings::GetPrivateHtml() + "/template.html");
}

std::string ExampleController::CreateContent() const
{
    std::string html;

    if(content.Load())
    {
        html = content.GetContent();
        StringUtility::Replace(html, "$(title)", "Example - Gravy Web");
        StringUtility::Replace(html, "$(header_text)", "Example");
        StringUtility::Replace(html, "$(head)", "<script src=\"/api.js\"></script>");

        StringBuilder sb;
        sb.AppendLine("<p>Click the button to send a POST request<p>");
        sb.AppendLine("<p><button class=\"btn-style\" type=\"button\" class=\"btn btn-success\" id=\"buttonSend\">Send</button></p>");
        sb.AppendLine("<p id=\"responseArea\"></p>");

        StringUtility::Replace(html, "$(content)", sb.ToString());
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
        "    <h1>Example</h1>\n"
        "</body>\n"
        "</html>";           
    }

    return html;
}

HttpResponse ExampleController::OnGet(HttpContext *context)
{
    std::string html = CreateContent();
    HttpResponse response(HttpStatusCode::OK, HttpContentType(HttpMediaType::TextHtml), html);
    response.AddHeader("Cache-Control", "max-age=3600");
    return response;
}