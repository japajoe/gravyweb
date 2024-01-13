#include "HttpRequest.hpp"
#include "StringUtility.hpp"
#include <iostream>

std::unordered_map<std::string, HttpRequestMethod> HttpRequest::requestMethodTable;

HttpRequest::HttpRequest()
{
    CreateRequestMethodTable();

    contentLength = 0;
}

HttpRequestMethod HttpRequest::GetMethod() const
{
    return method;
}

std::string HttpRequest::GetMethodAsString() const
{
    switch(method)
    {
        case HttpRequestMethod::Connect:
            return "CONNECT";
        case HttpRequestMethod::Delete:
            return "DELETE";
        case HttpRequestMethod::Get:
            return "GET";
        case HttpRequestMethod::Head:
            return "HEAD";
        case HttpRequestMethod::Options:
            return "OPTIONS";
        case HttpRequestMethod::Patch:
            return "OPTIONS";
        case HttpRequestMethod::Post:
            return "POST";
        case HttpRequestMethod::Put:
            return "PUT";
        case HttpRequestMethod::Trace:
            return "TRACE";
        case HttpRequestMethod::Unknown:
            return "UNKNOWN";
        default:
            return "UNKNOWN";
    }
}

std::string HttpRequest::GetURL() const
{
    return URL;
}

std::string HttpRequest::GetRawURL() const
{
    return rawURL;
}

std::string HttpRequest::GetHost() const
{
    return host;
}

std::string HttpRequest::GetUserAgent() const
{
    return userAgent;
}

std::string HttpRequest::GetAccept() const
{
    return accept;
}

std::string HttpRequest::GetAcceptLanguage() const
{
    return acceptLanguage;
}

std::string HttpRequest::GetAcceptEncoding() const
{
    return acceptEncoding;
}

std::string HttpRequest::GetDNT() const
{
    return DNT;
}

std::string HttpRequest::GetConnection() const
{
    return connection;
}

std::string HttpRequest::GetReferer() const
{
    return referer;
}

std::string HttpRequest::GetSecFetchDest() const
{
    return secFetchDest;
}

std::string HttpRequest::GetSecFetchMode() const
{
    return secFetchMode;
}

std::string HttpRequest::GetSecFetchSite() const
{
    return secFetchSite;
}

std::string HttpRequest::GetCacheControl() const
{
    return cacheControl;
}

std::string HttpRequest::GetUpgradeInsecureRequests() const
{
    return upgradeInsecureRequests;
}

HttpContentType HttpRequest::GetContentType() const
{
    return contentType;
}

uint64_t HttpRequest::GetContentLength() const
{
    return contentLength;
}

std::unordered_map<std::string,std::string> HttpRequest::GetKeyValuePairs() const
{
    return keyValuePairs;
}

std::unordered_map<std::string,std::string> HttpRequest::GetCookies() const
{
    return cookies;
}

bool HttpRequest::TryParse(const std::string &request, HttpRequest &httpRequest)
{
    std::vector<std::string> lines = StringUtility::ToLines(request);

    if(lines.size() < 1)
        return false;

    std::vector<std::string> methodComponents = StringUtility::Split(lines[0], ' ');

    if(methodComponents.size() < 3)
        return false;

    std::unordered_map<std::string, std::string> dictionary;
    std::vector<std::string> cookies;

    std::string method = StringUtility::Trim(methodComponents[0]);
    methodComponents[1] = StringUtility::Trim(methodComponents[1]);

    std::string url = methodComponents[1];
    std::string protocol = methodComponents[2];

    dictionary["Method"] = method;
    dictionary["URL"] = url;

    for (size_t i = 1; i < lines.size(); i++)
    {
        std::vector<std::string> lineComponents = StringUtility::Split(lines[i], ':');

        if(lineComponents.size() < 2)
            continue;

        std::string key = StringUtility::Trim(lineComponents[0]);
        std::string value;

        lineComponents = StringUtility::Split(lines[i], ' ');

        lineComponents[1] = StringUtility::TrimStart(lineComponents[1]);

        for (size_t j = 1; j < lineComponents.size(); j++)
        {
            if(j < lineComponents.size() -1)
                value += lineComponents[j] + " ";
            else
                value += lineComponents[j];
        }

        if(dictionary.count(key) == 0)
        {
            value.pop_back(); //Might still have carriage return
            dictionary[key] = value;
        }

        if(StringUtility::ToLower(key) == "cookie")
            cookies.push_back(value);
    }

    httpRequest.method = GetRequestMethod(GetValue(dictionary, "Method"));
    httpRequest.URL = GetValue(dictionary, "URL");
    httpRequest.rawURL = GetValue(dictionary, "URL");
    httpRequest.host = GetValue(dictionary, "Host");
    httpRequest.userAgent = GetValue(dictionary, "User-Agent");
    httpRequest.accept = GetValue(dictionary, "Accept");
    httpRequest.acceptLanguage = GetValue(dictionary, "Accept-Language");
    httpRequest.acceptEncoding = GetValue(dictionary, "Accept-Encoding");
    httpRequest.DNT = GetValue(dictionary, "DNT");
    httpRequest.connection = GetValue(dictionary, "Connection");
    httpRequest.referer = GetValue(dictionary, "Referer");
    httpRequest.secFetchDest = GetValue(dictionary, "Sec-Fetch-Dest");
    httpRequest.secFetchMode = GetValue(dictionary, "Sec-Fetch-Mode");
    httpRequest.secFetchSite = GetValue(dictionary, "Sec-Fetch-Site");
    httpRequest.cacheControl = GetValue(dictionary, "Cache-Control");
    httpRequest.upgradeInsecureRequests = GetValue(dictionary, "Upgrade-Insecure-Requests");
    httpRequest.contentType = GetContentType(GetValue(dictionary, "Content-Type"));
    httpRequest.contentLength = StringUtility::ToUInt64(GetValue(dictionary, "Content-Length"));

    httpRequest.keyValuePairs = GetKeyValuePairs(httpRequest.URL);

    httpRequest.cookies = GetCookies(cookies);

    if(StringUtility::Contains(httpRequest.URL, "?"))
    {
        auto components = StringUtility::Split(httpRequest.URL, '?');
        httpRequest.URL = components[0];
    }

    return true;
}

std::string HttpRequest::GetValue(std::unordered_map<std::string,std::string> &dictionary, const std::string &key)
{
    if(dictionary.count(key) > 0)
        return dictionary[key];

    return "";
}

HttpRequestMethod HttpRequest::GetRequestMethod(const std::string &s)
{
    std::string sss = StringUtility::ToLower(s);

    if(requestMethodTable.count(sss) > 0)
    {
        return requestMethodTable[sss];
    }

    return HttpRequestMethod::Unknown;
}

std::unordered_map<std::string,std::string> HttpRequest::GetKeyValuePairs(const std::string & URL)
{
    std::unordered_map<std::string,std::string> keyValuePairs;

    if(StringUtility::Contains(URL, "?"))
    {
        std::vector<std::string> components = StringUtility::Split(URL, '?');

        if(components.size() < 2)
            return keyValuePairs;

        if(StringUtility::Contains(components[1], "&"))
        {
            if(StringUtility::Contains(components[1], "="))
            {                     
                components = StringUtility::Split(components[1], '&');

                if(components.size() < 2)
                    return keyValuePairs;

                for (size_t i = 0; i < components.size(); i++)
                {
                    std::vector<std::string> keyValue = StringUtility::Split(components[i], '=');

                    if(keyValue.size() < 2)
                        continue;

                    std::string &key = keyValue[0];
                    std::string &value = keyValue[1];

                    if(key.size() == 0 || value.size() == 0)
                        continue;

                    keyValuePairs[key] = value;
                }
            }
        }
        else
        {
            if(StringUtility::Contains(components[1], "="))
            {
                components = StringUtility::Split(components[1], '=');

                if(components.size() < 2)
                    return keyValuePairs;

                if(components.size() % 2 != 0)
                    return keyValuePairs;

                for (size_t i = 0; i < components.size(); i+=2)
                { 
                    std::string &key = components[i];
                    std::string &value = components[+1];

                    if(key.size() == 0 || value.size() == 0)
                        continue;
                    
                    keyValuePairs[key] = value;
                }
            }
        }
    }
    
    return keyValuePairs;
}

std::unordered_map<std::string,std::string> HttpRequest::GetCookies(const std::vector<std::string> &cookies)
{
    std::unordered_map<std::string,std::string> dictionary;

    if(cookies.size() == 0)
        return dictionary;

    for (size_t i = 0; i < cookies.size(); i++)
    {
        //Multiple cookie key/value pairs
        if(StringUtility::Contains(cookies[i], ";"))
        {
            std::vector<std::string> keyValuePairs = StringUtility::Split(cookies[i], ';');

            for (size_t j = 0; j < keyValuePairs.size(); j++)
            {
                std::vector<std::string> components = StringUtility::Split(keyValuePairs[j], '=');

                if(components.size() == 2)
                {
                    std::string key = StringUtility::Trim(components[0]);
                    std::string value = StringUtility::Trim(components[1]);
                    
                    if(dictionary.count(key) == 0)
                        dictionary[key] = value;
                }
            }
        }
        else
        {
            std::vector<std::string> components = StringUtility::Split(cookies[i], '=');

            if(components.size() == 2)
            {
                std::string key = StringUtility::Trim(components[0]);
                std::string value = StringUtility::Trim(components[1]);
                
                if(dictionary.count(key) == 0)
                    dictionary[key] = value;
            }
        }
    }

    return dictionary;
}

HttpContentType HttpRequest::GetContentType(const std::string &s)
{
    HttpMediaType mediaType = HttpMediaType::Unknown;

    if(StringUtility::Contains(s, ";"))
    {
        auto components = StringUtility::Split(s, ';');

        if (components.size() > 1)
        {
            mediaType = HttpContentType::GetMediaTypeFromString(StringUtility::Trim(components[0]));
            HttpCharSet charSet = HttpContentType::GetCharSetFromString(StringUtility::Trim(components[1]));
            return HttpContentType(mediaType, charSet);
        }
    }

    mediaType = HttpContentType::GetMediaTypeFromString(StringUtility::Trim(s));
    return HttpContentType(mediaType);            
}

void HttpRequest::CreateRequestMethodTable()
{
    if(requestMethodTable.size() == 0)
    {
        requestMethodTable["connect"] = HttpRequestMethod::Connect;
        requestMethodTable["delete"] = HttpRequestMethod::Delete;
        requestMethodTable["get"] = HttpRequestMethod::Get;
        requestMethodTable["head"] = HttpRequestMethod::Head;
        requestMethodTable["options"] = HttpRequestMethod::Options;
        requestMethodTable["patch"] = HttpRequestMethod::Patch;
        requestMethodTable["post"] = HttpRequestMethod::Post;
        requestMethodTable["put"] = HttpRequestMethod::Put;
        requestMethodTable["trace"] = HttpRequestMethod::Trace;
    }
}