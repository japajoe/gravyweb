#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "HttpRequestMethod.hpp"
#include "HttpContentType.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class HttpRequest
{
private:
    static std::unordered_map<std::string, HttpRequestMethod> requestMethodTable;
    HttpRequestMethod method;
    std::string URL;
    std::string rawURL;
    std::string host;
    std::string userAgent;
    std::string accept;
    std::string acceptLanguage;
    std::string acceptEncoding;
    bool DNT;
    std::string connection;
    std::string referer;
    std::string secFetchDest;
    std::string secFetchMode;
    std::string secFetchSite;
    std::string cacheControl;
    bool upgradeInsecureRequests;
    HttpContentType contentType;
    uint64_t contentLength;
    std::unordered_map<std::string,std::string> keyValuePairs;
    std::unordered_map<std::string,std::string> cookies;
    static std::string GetValue(std::unordered_map<std::string,std::string> &dictionary, const std::string &key);
    static HttpRequestMethod GetRequestMethod(const std::string &s);
    static std::unordered_map<std::string,std::string> GetKeyValuePairs(const std::string & URL);
    static std::unordered_map<std::string,std::string> GetCookies(const std::vector<std::string> &cookies);
    static HttpContentType GetContentType(const std::string &s);
    static bool GetBoolean(const std::string &s);
    static void CreateRequestMethodTable();
public:
    HttpRequest();
    HttpRequestMethod GetMethod() const;
    std::string GetMethodAsString() const;
    std::string GetURL() const;
    std::string GetRawURL() const;
    std::string GetHost() const;
    std::string GetUserAgent() const;
    std::string GetAccept() const;
    std::string GetAcceptLanguage() const;
    std::string GetAcceptEncoding() const;
    bool GetDNT() const;
    std::string GetConnection() const;
    std::string GetReferer() const;
    std::string GetSecFetchDest() const;
    std::string GetSecFetchMode() const;
    std::string GetSecFetchSite() const;
    std::string GetCacheControl() const;
    bool GetUpgradeInsecureRequests() const;
    HttpContentType GetContentType() const;
    uint64_t GetContentLength() const;
    std::unordered_map<std::string,std::string> GetKeyValuePairs() const;
    std::unordered_map<std::string,std::string> GetCookies() const;    
    static bool TryParse(const std::string &request, HttpRequest &httpRequest);
};

#endif