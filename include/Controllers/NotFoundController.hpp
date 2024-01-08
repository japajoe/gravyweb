#ifndef NOTFOUNDCONTROLLER_HPP
#define NOTFOUNDCONTROLLER_HPP

#include "HttpController.hpp"
#include "HttpPageContent.hpp"

class NotFoundController : public HttpController
{
private:
    static HttpPageContent content;
public:
    NotFoundController();
    HttpResponse OnGet(HttpContext *context) override;
};

#endif