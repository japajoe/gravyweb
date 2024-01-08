#include "APIController.hpp"
#include "HttpSettings.hpp"
#include "Console.hpp"
#include "StringUtility.hpp"
#include "StringBuilder.hpp"


class APIResponse
{
public:
    int numberOfRequests;
    std::string message;

    APIResponse(int numberOfRequests, const std::string &message)
    {
        this->numberOfRequests = numberOfRequests;
        this->message = message;
    }

    std::string Serialize() const
    {
        const std::string DQ = "\"";
        StringBuilder sb;
        sb.Append("{" + DQ + "NumberOfRequests" + DQ + ":" + std::to_string(numberOfRequests) + ",");
        sb.Append(DQ + "Message" + DQ + ":" + DQ + message + DQ + "}");
        return sb.ToString();
    }
};

int APIController::numRequests = 0;

APIController::APIController()
{

}

HttpResponse APIController::OnPost(HttpContext *context)
{
    numRequests++;

    HttpRequest *request = context->GetRequest();
    uint64_t contentSize = request->GetContentLength();
    HttpMediaType mediaType = request->GetContentType().GetMediaType();

    if(contentSize > 0 && mediaType == HttpMediaType::ApplicationJson)
    {
        std::string json = ReadContentAsString(context);    
        Console::WriteLog("Received JSON: " + json);    
        APIResponse response(numRequests, "Thank you!");
        return HttpResponse(HttpStatusCode::OK, HttpContentType(HttpMediaType::ApplicationJson), response.Serialize());
    }
    else
    {
        return HttpResponse(HttpStatusCode::BadRequest);
    }
}