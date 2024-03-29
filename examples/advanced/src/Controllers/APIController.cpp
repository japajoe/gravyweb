#include "APIController.hpp"
#include "HttpSettings.hpp"
#include "Console.hpp"
#include "StringUtility.hpp"
#include "JsonBuilder.hpp"

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
        JsonBuilder builder;
        builder.AddProperty("Message", message);
        builder.AddProperty("NumberOfRequests", numberOfRequests);
        return builder.ToString();
    }
};

int APIController::numRequests = 0;

APIController::APIController()
{
    //This overrides HttpSettings::GetMaxRequestBodySize()
    //This will only affect this controller
    SetMaxRequestBodySize(128);
}

HttpResponse APIController::OnPost(HttpContext *context)
{
    numRequests++;

    HttpRequest *request = context->GetRequest();
    HttpMediaType mediaType = request->GetContentType().GetMediaType();

    if(mediaType == HttpMediaType::ApplicationJson)
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