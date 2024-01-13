#ifndef CONTACTCONTROLLER_HPP
#define CONTACTCONTROLLER_HPP

#include "HttpController.hpp"
#include "HttpPageContent.hpp"

class ContactController : public HttpController
{
private:
    static HttpPageContent content;
    std::string CreateContent() const;
public:
    ContactController();
    HttpResponse OnGet(HttpContext *context) override;
};

#endif