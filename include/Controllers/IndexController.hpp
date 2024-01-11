#ifndef INDEXCONTROLLER_HPP
#define INDEXCONTROLLER_HPP

#include "HttpController.hpp"
#include "HttpPageContent.hpp"

class IndexController : public HttpController
{
private:
    static HttpPageContent pageTemplate;
    static HttpPageContent pageContent;
public:
    IndexController();
    HttpResponse OnGet(HttpContext *context) override;
};

#endif