#include "HttpContentType.hpp"
#include "HttpMimeType.hpp"

std::unordered_map<HttpMediaType, std::string> HttpContentType::mediaTypeToStringTable;
std::unordered_map<std::string, HttpMediaType> HttpContentType::stringToMediaTypeTable;
std::unordered_map<HttpCharSet, std::string> HttpContentType::charSetToStringTable;
std::unordered_map<std::string, HttpCharSet> HttpContentType::stringToCharSetTable;

HttpContentType::HttpContentType()
{
    this->mediaType = HttpMediaType::TextPlain;
    this->charSet = HttpCharSet::UTF8;
    CreateTables();
}

HttpContentType::HttpContentType(HttpMediaType mediaType, HttpCharSet charSet)
{
    this->mediaType = mediaType;
    this->charSet = charSet;
    CreateTables();
}

void HttpContentType::CreateTables()
{
    if(mediaTypeToStringTable.size() == 0)
    {
        mediaTypeToStringTable[HttpMediaType::ApplicationEDIX12] = "application/EDI-X12";
        mediaTypeToStringTable[HttpMediaType::ApplicationEDIFACT] = "application/EDIFACT";
        mediaTypeToStringTable[HttpMediaType::ApplicationJavaScript] = "application/javascript";
        mediaTypeToStringTable[HttpMediaType::ApplicationOctetStream] = "application/octet-stream";
        mediaTypeToStringTable[HttpMediaType::ApplicationOgg] = "application/ogg";
        mediaTypeToStringTable[HttpMediaType::ApplicationPdf] = "application/pdf";
        mediaTypeToStringTable[HttpMediaType::ApplicationXhtmlXml] = "application/xhtml+xml";
        mediaTypeToStringTable[HttpMediaType::ApplicationXShockWaveFlash] = "application/x-shockwave-flash";
        mediaTypeToStringTable[HttpMediaType::ApplicationJson] = "application/json";
        mediaTypeToStringTable[HttpMediaType::ApplicationLdJson] = "application/ld+json";
        mediaTypeToStringTable[HttpMediaType::ApplicationXml] = "application/xml";
        mediaTypeToStringTable[HttpMediaType::ApplicationZip] = "application/zip";
        mediaTypeToStringTable[HttpMediaType::ApplicationXWWWFormUrlEncoded] = "application/x-www-form-urlencoded";
        mediaTypeToStringTable[HttpMediaType::AudioMpeg] = "audio/mpeg";
        mediaTypeToStringTable[HttpMediaType::AudioXMSWma] = "audio/x-ms-wma";
        mediaTypeToStringTable[HttpMediaType::AudioVndRnRealAudio] = "audio/vnd.rn-realaudio";
        mediaTypeToStringTable[HttpMediaType::AudioXWav] = "audio/x-wav";
        mediaTypeToStringTable[HttpMediaType::ImageGif] = "image/gif";
        mediaTypeToStringTable[HttpMediaType::ImageJpeg] = "image/jpeg";
        mediaTypeToStringTable[HttpMediaType::ImagePng] = "image/png";
        mediaTypeToStringTable[HttpMediaType::ImageTiff] = "image/tiff";
        mediaTypeToStringTable[HttpMediaType::ImageVndMicrosoftIcon] = "image/vnd.microsoft.icon";
        mediaTypeToStringTable[HttpMediaType::ImageXIcon] = "image/x-icon";
        mediaTypeToStringTable[HttpMediaType::ImageVndDjvu] = "image/vnd.djvu";
        mediaTypeToStringTable[HttpMediaType::ImageSvgXml] = "image/svg+xml";
        mediaTypeToStringTable[HttpMediaType::MultiPartMixed] = "multipart/mixed";
        mediaTypeToStringTable[HttpMediaType::MultiPartAlternative] = "multipart/alternative";
        mediaTypeToStringTable[HttpMediaType::MultiPartRelated] = "multipart/related";
        mediaTypeToStringTable[HttpMediaType::MultiPartFormData] = "multipart/form-data";
        mediaTypeToStringTable[HttpMediaType::TextCss] = "text/css";
        mediaTypeToStringTable[HttpMediaType::TextCsv] = "text/csv";
        mediaTypeToStringTable[HttpMediaType::TextHtml] = "text/html";
        mediaTypeToStringTable[HttpMediaType::TextJavaScript] = "text/javascript";
        mediaTypeToStringTable[HttpMediaType::TextPlain] = "text/plain";
        mediaTypeToStringTable[HttpMediaType::TextXml] = "text/xml";
        mediaTypeToStringTable[HttpMediaType::VideoMpeg] = "video/mpeg";
        mediaTypeToStringTable[HttpMediaType::VideoMp4] = "video/mp4";
        mediaTypeToStringTable[HttpMediaType::VideoQuickTime] = "video/quicktime";
        mediaTypeToStringTable[HttpMediaType::VideoXMSWmv] = "video/x-ms-wmv";
        mediaTypeToStringTable[HttpMediaType::VideoXMSVideo] = "video/x-msvideo";
        mediaTypeToStringTable[HttpMediaType::VideoXFlv] = "video/x-flv";
        mediaTypeToStringTable[HttpMediaType::VideoWebM] = "video/webm";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndOasisOpenDocumentText] = "application/vnd.oasis.opendocument.text";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndOasisOpenDocumentSpreadSheet] = "application/vnd.oasis.opendocument.spreadsheet";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndOasisOpenDocumentPresentation] = "application/vnd.oasis.opendocument.presentation";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndOasisOpenDocumentGraphics] = "application/vnd.oasis.opendocument.graphics";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndMSExcel] = "application/vnd.ms-excel";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndOpenXmlFormatsOfficeDocumentSpreadSheetMLSheet] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndMSPowerpoint] = "application/vnd.ms-powerpoint";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndOpenXmlFormatsOfficeDocumentPresentationMLPresentation] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
        mediaTypeToStringTable[HttpMediaType::ApplicationMSWord] = "application/msword";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndOpenXmlFormatsOfficeDocumentWordProcessingMLDocument] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
        mediaTypeToStringTable[HttpMediaType::ApplicationVndMozillaXulXml] = "application/vnd.mozilla.xul+xml";
        mediaTypeToStringTable[HttpMediaType::Unknown] = "unknown";

        for(auto &item : mediaTypeToStringTable)
        {
            stringToMediaTypeTable[item.second] = item.first;
        }

        charSetToStringTable[HttpCharSet::ISO88591] = "charset=ISO-8859-1";
        charSetToStringTable[HttpCharSet::ISO88598] = "charset=ISO-8859-8";
        charSetToStringTable[HttpCharSet::UTF8] = "charset=utf-8";
        charSetToStringTable[HttpCharSet::UTF16] = "charset=utf-16";
        charSetToStringTable[HttpCharSet::Unknown] = "charset=unknown";

        for(auto &item : charSetToStringTable)
        {
            stringToCharSetTable[item.second] = item.first;
        }
    }
}

HttpMediaType HttpContentType::GetMediaType() const
{
    return mediaType;
}

HttpCharSet HttpContentType::GetCharSet() const
{
    return charSet;
}

std::string HttpContentType::ToString() const
{
    std::string ss = mediaTypeToStringTable[mediaType] + "; " + charSetToStringTable[charSet];
    return ss;
}

HttpMediaType HttpContentType::GetMediaTypeFromString(const std::string &contentType)
{
    CreateTables();

    if(stringToMediaTypeTable.count(contentType))
    {
        return stringToMediaTypeTable[contentType];
    }

    return HttpMediaType::Unknown;
}

HttpCharSet HttpContentType::GetCharSetFromString(const std::string &charSet)
{
    CreateTables();

    if(stringToCharSetTable.count(charSet))
    {
        return stringToCharSetTable[charSet];
    }

    return HttpCharSet::Unknown;
}

HttpMediaType HttpContentType::GetMediaTypeFromFileExtension(const std::string &filepath)
{
    HttpMediaType mediaType = HttpMediaType::ApplicationOctetStream;

    std::string mimeType;
    
    if(HttpMimeType::TryGetMimeType(filepath, mimeType))
    {
        mediaType = HttpContentType::GetMediaTypeFromString(mimeType);
    }

    return mediaType;
}

HttpContentType HttpContentType::GetContentTypeFromFileExtension(const std::string &filepath)
{
    return HttpContentType(GetMediaTypeFromFileExtension(filepath));
}