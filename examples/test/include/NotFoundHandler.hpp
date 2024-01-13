#ifndef NOTFOUNDHANDLER_HPP
#define NOTFOUNDHANDLER_HPP

#include "HttpContext.hpp"
#include "HttpResponse.hpp"
#include "HttpPageContent.hpp"
#include "HttpSettings.hpp"
#include "StringUtility.hpp"

class NotFoundHandler
{
private:
    HttpPageContent pageTemplate;
public:
    HttpResponse OnGet(HttpContext *context)
    {
        if(pageTemplate.GetContent().size() == 0)
            pageTemplate = HttpPageContent(HttpSettings::GetPrivateHtml() + "/template.html");

        bool result = pageTemplate.Load();

        std::string html = "Hello world";

        if(result)
        {
            html = pageTemplate.GetContent();
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
};

#endif