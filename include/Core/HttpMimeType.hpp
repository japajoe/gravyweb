#ifndef HTTPMIMETYPE
#define HTTPMIMETYPE

#include <unordered_map>
#include <string>

class HttpMimeType
{
private:
    static std::unordered_map<std::string,std::string> mimeTypeMap;
    static std::string Dot;
    static std::string QuestionMark;
    static std::string DefaultMimeType;
    static void Initialize();
public:
    static bool TryGetMimeType(const std::string &fileNameOrExtension, std::string &mimeType);
};

#endif