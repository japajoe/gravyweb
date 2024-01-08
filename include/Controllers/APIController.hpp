#ifndef APICONTROLLER_HPP
#define APICONTROLLER_HPP

#include "HttpController.hpp"
#include "HttpPageContent.hpp"

class APIController : public HttpController
{
private:
    static int numRequests;
public:
    APIController();
    HttpResponse OnPost(HttpContext *context) override;
};

#endif