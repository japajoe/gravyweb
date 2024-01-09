#include "HttpResponse.hpp"
#include "MemoryStream.hpp"
#include <cstring>

HttpResponse::HttpResponse(HttpStatusCode status, const HttpContentType &contentType, const std::string &content)
{
    this->status = status;
    this->contentType = contentType;
    char *data = const_cast<char*>(content.data());
    this->content = std::make_shared<MemoryStream>(data, content.size(), true);
}

HttpResponse::HttpResponse(HttpStatusCode status, const HttpContentType &contentType, const std::shared_ptr<Stream> &content)
{
    this->status = status;
    this->contentType = contentType;
    this->content = content;
}

HttpResponse::HttpResponse(HttpStatusCode status, const HttpContentType &contentType)
{
    this->status = status;
    this->contentType = contentType;
    this->content = nullptr;
}

HttpResponse::HttpResponse(HttpStatusCode status)
{
    this->status = status;
    this->contentType = HttpContentType(HttpMediaType::TextPlain);
    this->content = nullptr;
}

HttpResponse::HttpResponse()
{
    this->status = HttpStatusCode::OK;
    this->contentType = HttpContentType(HttpMediaType::TextPlain);
    this->content = nullptr;
}

HttpStatusCode HttpResponse::GetStatusCode() const
{
    return status;
}

void HttpResponse::AddHeader(const std::string &key, const std::string &value)
{
    fields[key] = value;
}

void HttpResponse::AddHeader(const std::string &key, size_t value)
{
    fields[key] = std::to_string(value);
}

void HttpResponse::AddHeader(const std::string &key, ssize_t value)
{
    fields[key] = std::to_string(value);
}

void HttpResponse::AddHeader(const std::string &key, float value)
{
    fields[key] = std::to_string(value);
}

void HttpResponse::AddHeader(const std::string &key, double value)
{
    fields[key] = std::to_string(value);
}

void HttpResponse::Send(HttpStream *stream)
{
    HttpResponseBuilder builder;
    builder.BeginHeader(status);

    for(auto &item : fields)
    {
        builder.AddHeader(item.first, item.second);
    }

    if(content != nullptr)
    {
        builder.AddHeader("Content-Type", contentType.ToString());
        builder.AddHeader("Content-Length", content->GetSize());
    }

    builder.EndHeader();

    std::string header = builder.ToString();

    if(Send(stream, const_cast<char*>(header.data()), header.size()))
    {
        if(content != nullptr)
            Send(stream, content.get());
    }
}

bool HttpResponse::Send(HttpStream *stream, void *data, size_t dataSize)
{
    const size_t chunkSize = 1024;
    unsigned char buffer[1024];
    std::memset(buffer, 0, 1024);

    unsigned char *pData = reinterpret_cast<unsigned char*>(data);

    for (size_t offset = 0; offset < dataSize; offset += chunkSize) 
    {
        size_t remaining = dataSize - offset;
        size_t currentChunkSize = (remaining > chunkSize) ? chunkSize : remaining;

        // Copy the current chunk of data into the buffer
        std::memcpy(buffer, pData + offset, currentChunkSize);

        if(stream->Write(buffer, 0, currentChunkSize) <= 0)
            return false;
    }

    return true;
}

bool HttpResponse::Send(HttpStream *stream, Stream *data)
{
    if(data == nullptr)
        return false;

    if(data->GetSize() == 0)
        return false;

    const size_t chunkSize = 1024;
    unsigned char buffer[1024];
    std::memset(buffer, 0, 1024);
    size_t dataSize = data->GetSize();

    for (size_t offset = 0; offset < dataSize; offset += chunkSize) 
    {
        size_t remaining = dataSize - offset;
        size_t currentChunkSize = (remaining > chunkSize) ? chunkSize : remaining;

        // Copy the current chunk of data into the buffer
        data->Read(buffer, 0, currentChunkSize);

        if(stream->Write(buffer, 0, currentChunkSize) <= 0)
            return false;
    }

    return true;
}