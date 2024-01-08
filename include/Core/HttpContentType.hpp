#ifndef HTTPCONTENTTYPE_HPP
#define HTTPCONTENTTYPE_HPP

#include <string>
#include <unordered_map>

enum class HttpMediaType : int
{
    ApplicationEDIX12,
    ApplicationEDIFACT,
    ApplicationJavaScript,
    ApplicationOctetStream,
    ApplicationOgg,
    ApplicationPdf,
    ApplicationXhtmlXml,
    ApplicationXShockWaveFlash,
    ApplicationJson,
    ApplicationLdJson,
    ApplicationXml,
    ApplicationZip,
    ApplicationXWWWFormUrlEncoded,
    AudioMpeg,
    AudioXMSWma,
    AudioVndRnRealAudio,
    AudioXWav,
    ImageGif,
    ImageJpeg,
    ImagePng,
    ImageTiff,
    ImageVndMicrosoftIcon,
    ImageXIcon,
    ImageVndDjvu,
    ImageSvgXml,
    MultiPartMixed,
    MultiPartAlternative,
    MultiPartRelated,
    MultiPartFormData,
    TextCss,
    TextCsv,
    TextHtml,
    TextJavaScript,
    TextPlain,
    TextXml,
    VideoMpeg,
    VideoMp4,
    VideoQuickTime,
    VideoXMSWmv,
    VideoXMSVideo,
    VideoXFlv,
    VideoWebM,
    ApplicationVndOasisOpenDocumentText,
    ApplicationVndOasisOpenDocumentSpreadSheet,
    ApplicationVndOasisOpenDocumentPresentation,
    ApplicationVndOasisOpenDocumentGraphics,
    ApplicationVndMSExcel,
    ApplicationVndOpenXmlFormatsOfficeDocumentSpreadSheetMLSheet,
    ApplicationVndMSPowerpoint,
    ApplicationVndOpenXmlFormatsOfficeDocumentPresentationMLPresentation,
    ApplicationMSWord,
    ApplicationVndOpenXmlFormatsOfficeDocumentWordProcessingMLDocument,
    ApplicationVndMozillaXulXml,
    Unknown
};

enum HttpCharSet : int
{
    ISO88591,
    ISO88598,
    UTF8,
    UTF16,
    Unknown
};

class HttpContentType
{
private:
    HttpMediaType mediaType;
    HttpCharSet charSet;
    static std::unordered_map<HttpMediaType, std::string> mediaTypeToStringTable;
    static std::unordered_map<std::string, HttpMediaType> stringToMediaTypeTable;
    static std::unordered_map<HttpCharSet, std::string> charSetToStringTable;
    static std::unordered_map<std::string, HttpCharSet> stringToCharSetTable;
    static void CreateTables();
public:
    HttpContentType();
    HttpContentType(HttpMediaType mediaType, HttpCharSet charSet = HttpCharSet::UTF8);
    HttpMediaType GetMediaType() const;
    HttpCharSet GetCharSet() const;
    std::string ToString() const;
    static HttpMediaType GetMediaTypeFromString(const std::string &contentType);
    static HttpCharSet GetCharSetFromString(const std::string &charSet);
    static HttpMediaType GetMediaTypeFromFileExtension(const std::string &filepath);
    static HttpContentType GetContentTypeFromFileExtension(const std::string &filepath);
};

#endif