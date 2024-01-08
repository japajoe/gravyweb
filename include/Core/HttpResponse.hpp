#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include "HttpStatusCode.hpp"
#include "HttpContentType.hpp"
#include "HttpResponseBuilder.hpp"
#include "HttpStream.hpp"
#include "Stream.hpp"

class HttpResponse
{
private:
    std::unordered_map<std::string,std::string> fields;
    HttpStatusCode status;
    HttpContentType contentType;
    std::shared_ptr<Stream> content;
    bool Send(HttpStream *stream, void *data, size_t dataSize);
    bool Send(HttpStream *stream, Stream *data);
public:
    HttpResponse(HttpStatusCode status, const HttpContentType &contentType, const std::string &content);
    HttpResponse(HttpStatusCode status, const HttpContentType &contentType, const std::shared_ptr<Stream> &content);
    HttpResponse(HttpStatusCode status, const HttpContentType &contentType);
    HttpResponse(HttpStatusCode status);
    HttpResponse();
    HttpStatusCode GetStatusCode() const;
    void AddHeader(const std::string &key, const std::string &value);
    void AddHeader(const std::string &key, size_t value);
    void AddHeader(const std::string &key, ssize_t value);
    void AddHeader(const std::string &key, float value);
    void AddHeader(const std::string &key, double value);
    void Send(HttpStream *stream);
};

#endif