#ifndef INDEXHANDLER_HPP
#define INDEXHANDLER_HPP

#include "HttpContext.hpp"
#include "HttpResponse.hpp"
#include "HttpPageContent.hpp"
#include "HttpSettings.hpp"
#include "StringUtility.hpp"

class IndexHandler
{
private:
    HttpPageContent pageTemplate;
    HttpPageContent pageContent;
public:
    HttpResponse OnGet(HttpContext *context)
    {
        if(pageTemplate.GetContent().size() == 0)
            pageTemplate = HttpPageContent(HttpSettings::GetPrivateHtml() + "/template.html");

        if(pageContent.GetContent().size() == 0)
            pageContent = HttpPageContent(HttpSettings::GetPrivateHtml() + "/index.html");

        std::string html;

        if(pageTemplate.Load() && pageContent.Load())
        {
            html = pageTemplate.GetContent();
            StringUtility::Replace(html, "$(title)", "Home - Gravy Web");
            StringUtility::Replace(html, "$(header_text)", "The HTTP/1.1 Protocol");
            StringUtility::Replace(html, "$(head)", "");

            std::string content = pageContent.GetContent();
            StringUtility::Replace(html, "$(content)", content);
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
            "    <h1>Home</h1>\n"
            "</body>\n"
            "</html>";           
        }

        HttpResponse response(HttpStatusCode::OK, HttpContentType(HttpMediaType::TextHtml), html);
        response.AddHeader("Cache-Control", "max-age=3600");
        return response;
    }
};

#endif