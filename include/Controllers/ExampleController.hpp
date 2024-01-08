#ifndef EXAMPLECONTROLLER_HPP
#define EXAMPLECONTROLLER_HPP

#include "HttpController.hpp"
#include "HttpPageContent.hpp"

class ExampleController : public HttpController
{
private:
    static HttpPageContent content;
public:
    ExampleController();
    HttpResponse OnGet(HttpContext *context) override;
};

#endif