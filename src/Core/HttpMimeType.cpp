#include "HttpMimeType.hpp"
#include "StringUtility.hpp"
#include "File.hpp"

std::unordered_map<std::string,std::string> HttpMimeType::mimeTypeMap;
std::string HttpMimeType::Dot = ".";
std::string HttpMimeType::QuestionMark = "?";
std::string HttpMimeType::DefaultMimeType = "application/octet-stream";

void HttpMimeType::Initialize()
{
    if(mimeTypeMap.size() > 0)
        return;

    mimeTypeMap[".323"] = "text/h323";
    mimeTypeMap[".3g2"] = "video/3gpp2";
    mimeTypeMap[".3gp"] = "video/3gpp";
    mimeTypeMap[".3gp2"] = "video/3gpp2";
    mimeTypeMap[".3gpp"] = "video/3gpp";
    mimeTypeMap[".7z"] = "application/x-7z-compressed";
    mimeTypeMap[".aa"] = "audio/audible";
    mimeTypeMap[".AAC"] = "audio/aac";
    mimeTypeMap[".aaf"] = "application/octet-stream";
    mimeTypeMap[".aax"] = "audio/vnd.audible.aax";
    mimeTypeMap[".ac3"] = "audio/ac3";
    mimeTypeMap[".aca"] = "application/octet-stream";
    mimeTypeMap[".accda"] = "application/msaccess.addin";
    mimeTypeMap[".accdb"] = "application/msaccess";
    mimeTypeMap[".accdc"] = "application/msaccess.cab";
    mimeTypeMap[".accde"] = "application/msaccess";
    mimeTypeMap[".accdr"] = "application/msaccess.runtime";
    mimeTypeMap[".accdt"] = "application/msaccess";
    mimeTypeMap[".accdw"] = "application/msaccess.webapplication";
    mimeTypeMap[".accft"] = "application/msaccess.ftemplate";
    mimeTypeMap[".acx"] = "application/internet-property-stream";
    mimeTypeMap[".AddIn"] = "text/xml";
    mimeTypeMap[".ade"] = "application/msaccess";
    mimeTypeMap[".adobebridge"] = "application/x-bridge-url";
    mimeTypeMap[".adp"] = "application/msaccess";
    mimeTypeMap[".ADT"] = "audio/vnd.dlna.adts";
    mimeTypeMap[".ADTS"] = "audio/aac";
    mimeTypeMap[".afm"] = "application/octet-stream";
    mimeTypeMap[".ai"] = "application/postscript";
    mimeTypeMap[".aif"] = "audio/aiff";
    mimeTypeMap[".aifc"] = "audio/aiff";
    mimeTypeMap[".aiff"] = "audio/aiff";
    mimeTypeMap[".air"] = "application/vnd.adobe.air-application-installer-package+zip";
    mimeTypeMap[".amc"] = "application/mpeg";
    mimeTypeMap[".anx"] = "application/annodex";
    mimeTypeMap[".apk"] = "application/vnd.android.package-archive";
    mimeTypeMap[".apng"] = "image/apng";
    mimeTypeMap[".application"] = "application/x-ms-application";
    mimeTypeMap[".art"] = "image/x-jg";
    mimeTypeMap[".asa"] = "application/xml";
    mimeTypeMap[".asax"] = "application/xml";
    mimeTypeMap[".ascx"] = "application/xml";
    mimeTypeMap[".asd"] = "application/octet-stream";
    mimeTypeMap[".asf"] = "video/x-ms-asf";
    mimeTypeMap[".ashx"] = "application/xml";
    mimeTypeMap[".asi"] = "application/octet-stream";
    mimeTypeMap[".asm"] = "text/plain";
    mimeTypeMap[".asmx"] = "application/xml";
    mimeTypeMap[".aspx"] = "application/xml";
    mimeTypeMap[".asr"] = "video/x-ms-asf";
    mimeTypeMap[".asx"] = "video/x-ms-asf";
    mimeTypeMap[".atom"] = "application/atom+xml";
    mimeTypeMap[".au"] = "audio/basic";
    mimeTypeMap[".avci"] = "image/avci";
    mimeTypeMap[".avcs"] = "image/avcs";
    mimeTypeMap[".avi"] = "video/x-msvideo";
    mimeTypeMap[".avif"] = "image/avif";
    mimeTypeMap[".avifs"] = "image/avif-sequence";
    mimeTypeMap[".axa"] = "audio/annodex";
    mimeTypeMap[".axs"] = "application/olescript";
    mimeTypeMap[".axv"] = "video/annodex";
    mimeTypeMap[".bas"] = "text/plain";
    mimeTypeMap[".bcpio"] = "application/x-bcpio";
    mimeTypeMap[".bin"] = "application/octet-stream";
    mimeTypeMap[".bmp"] = "image/bmp";
    mimeTypeMap[".c"] = "text/plain";
    mimeTypeMap[".cab"] = "application/octet-stream";
    mimeTypeMap[".caf"] = "audio/x-caf";
    mimeTypeMap[".calx"] = "application/vnd.ms-office.calx";
    mimeTypeMap[".cat"] = "application/vnd.ms-pki.seccat";
    mimeTypeMap[".cc"] = "text/plain";
    mimeTypeMap[".cd"] = "text/plain";
    mimeTypeMap[".cdda"] = "audio/aiff";
    mimeTypeMap[".cdf"] = "application/x-cdf";
    mimeTypeMap[".cer"] = "application/x-x509-ca-cert";
    mimeTypeMap[".cfg"] = "text/plain";
    mimeTypeMap[".chm"] = "application/octet-stream";
    mimeTypeMap[".class"] = "application/x-java-applet";
    mimeTypeMap[".clp"] = "application/x-msclip";
    mimeTypeMap[".cmd"] = "text/plain";
    mimeTypeMap[".cmx"] = "image/x-cmx";
    mimeTypeMap[".cnf"] = "text/plain";
    mimeTypeMap[".cod"] = "image/cis-cod";
    mimeTypeMap[".config"] = "application/xml";
    mimeTypeMap[".contact"] = "text/x-ms-contact";
    mimeTypeMap[".coverage"] = "application/xml";
    mimeTypeMap[".cpio"] = "application/x-cpio";
    mimeTypeMap[".cpp"] = "text/plain";
    mimeTypeMap[".crd"] = "application/x-mscardfile";
    mimeTypeMap[".crl"] = "application/pkix-crl";
    mimeTypeMap[".crt"] = "application/x-x509-ca-cert";
    mimeTypeMap[".cs"] = "text/plain";
    mimeTypeMap[".csdproj"] = "text/plain";
    mimeTypeMap[".csh"] = "application/x-csh";
    mimeTypeMap[".csproj"] = "text/plain";
    mimeTypeMap[".css"] = "text/css";
    mimeTypeMap[".csv"] = "text/csv";
    mimeTypeMap[".cur"] = "application/octet-stream";
    mimeTypeMap[".czx"] = "application/x-czx";
    mimeTypeMap[".cxx"] = "text/plain";
    mimeTypeMap[".dat"] = "application/octet-stream";
    mimeTypeMap[".datasource"] = "application/xml";
    mimeTypeMap[".dbproj"] = "text/plain";
    mimeTypeMap[".dcr"] = "application/x-director";
    mimeTypeMap[".def"] = "text/plain";
    mimeTypeMap[".deploy"] = "application/octet-stream";
    mimeTypeMap[".der"] = "application/x-x509-ca-cert";
    mimeTypeMap[".dgml"] = "application/xml";
    mimeTypeMap[".dib"] = "image/bmp";
    mimeTypeMap[".dif"] = "video/x-dv";
    mimeTypeMap[".dir"] = "application/x-director";
    mimeTypeMap[".disco"] = "text/xml";
    mimeTypeMap[".divx"] = "video/divx";
    mimeTypeMap[".dll"] = "application/x-msdownload";
    mimeTypeMap[".dll.config"] = "text/xml";
    mimeTypeMap[".dlm"] = "text/dlm";
    mimeTypeMap[".doc"] = "application/msword";
    mimeTypeMap[".docm"] = "application/vnd.ms-word.document.macroEnabled.12";
    mimeTypeMap[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypeMap[".dot"] = "application/msword";
    mimeTypeMap[".dotm"] = "application/vnd.ms-word.template.macroEnabled.12";
    mimeTypeMap[".dotx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
    mimeTypeMap[".dsp"] = "application/octet-stream";
    mimeTypeMap[".dsw"] = "text/plain";
    mimeTypeMap[".dtd"] = "text/xml";
    mimeTypeMap[".dtsConfig"] = "text/xml";
    mimeTypeMap[".dv"] = "video/x-dv";
    mimeTypeMap[".dvi"] = "application/x-dvi";
    mimeTypeMap[".dwf"] = "drawing/x-dwf";
    mimeTypeMap[".dwg"] = "application/acad";
    mimeTypeMap[".dwp"] = "application/octet-stream";
    mimeTypeMap[".dxf"] = "application/x-dxf";
    mimeTypeMap[".dxr"] = "application/x-director";
    mimeTypeMap[".eml"] = "message/rfc822";
    mimeTypeMap[".emf"] = "image/emf";
    mimeTypeMap[".emz"] = "application/octet-stream";
    mimeTypeMap[".eot"] = "application/vnd.ms-fontobject";
    mimeTypeMap[".eps"] = "application/postscript";
    mimeTypeMap[".es"] = "application/ecmascript";
    mimeTypeMap[".etl"] = "application/etl";
    mimeTypeMap[".etx"] = "text/x-setext";
    mimeTypeMap[".evy"] = "application/envoy";
    mimeTypeMap[".exe"] = "application/vnd.microsoft.portable-executable";
    mimeTypeMap[".exe.config"] = "text/xml";
    mimeTypeMap[".f4v"] = "video/mp4";
    mimeTypeMap[".fdf"] = "application/vnd.fdf";
    mimeTypeMap[".fif"] = "application/fractals";
    mimeTypeMap[".filters"] = "application/xml";
    mimeTypeMap[".fla"] = "application/octet-stream";
    mimeTypeMap[".flac"] = "audio/flac";
    mimeTypeMap[".flr"] = "x-world/x-vrml";
    mimeTypeMap[".flv"] = "video/x-flv";
    mimeTypeMap[".fsscript"] = "application/fsharp-script";
    mimeTypeMap[".fsx"] = "application/fsharp-script";
    mimeTypeMap[".generictest"] = "application/xml";
    mimeTypeMap[".geojson"] = "application/geo+json";
    mimeTypeMap[".gif"] = "image/gif";
    mimeTypeMap[".gpx"] = "application/gpx+xml";
    mimeTypeMap[".group"] = "text/x-ms-group";
    mimeTypeMap[".gsm"] = "audio/x-gsm";
    mimeTypeMap[".gtar"] = "application/x-gtar";
    mimeTypeMap[".gz"] = "application/x-gzip";
    mimeTypeMap[".h"] = "text/plain";
    mimeTypeMap[".hdf"] = "application/x-hdf";
    mimeTypeMap[".hdml"] = "text/x-hdml";
    mimeTypeMap[".heic"] = "image/heic";
    mimeTypeMap[".heics"] = "image/heic-sequence";
    mimeTypeMap[".heif"] = "image/heif";
    mimeTypeMap[".heifs"] = "image/heif-sequence";
    mimeTypeMap[".hhc"] = "application/x-oleobject";
    mimeTypeMap[".hhk"] = "application/octet-stream";
    mimeTypeMap[".hhp"] = "application/octet-stream";
    mimeTypeMap[".hlp"] = "application/winhlp";
    mimeTypeMap[".hpp"] = "text/plain";
    mimeTypeMap[".hqx"] = "application/mac-binhex40";
    mimeTypeMap[".hta"] = "application/hta";
    mimeTypeMap[".htc"] = "text/x-component";
    mimeTypeMap[".htm"] = "text/html";
    mimeTypeMap[".html"] = "text/html";
    mimeTypeMap[".htt"] = "text/webviewhtml";
    mimeTypeMap[".hxa"] = "application/xml";
    mimeTypeMap[".hxc"] = "application/xml";
    mimeTypeMap[".hxd"] = "application/octet-stream";
    mimeTypeMap[".hxe"] = "application/xml";
    mimeTypeMap[".hxf"] = "application/xml";
    mimeTypeMap[".hxh"] = "application/octet-stream";
    mimeTypeMap[".hxi"] = "application/octet-stream";
    mimeTypeMap[".hxk"] = "application/xml";
    mimeTypeMap[".hxq"] = "application/octet-stream";
    mimeTypeMap[".hxr"] = "application/octet-stream";
    mimeTypeMap[".hxs"] = "application/octet-stream";
    mimeTypeMap[".hxt"] = "text/html";
    mimeTypeMap[".hxv"] = "application/xml";
    mimeTypeMap[".hxw"] = "application/octet-stream";
    mimeTypeMap[".hxx"] = "text/plain";
    mimeTypeMap[".i"] = "text/plain";
    mimeTypeMap[".ical"] = "text/calendar";
    mimeTypeMap[".icalendar"] = "text/calendar";
    mimeTypeMap[".ico"] = "image/x-icon";
    mimeTypeMap[".ics"] = "text/calendar";
    mimeTypeMap[".idl"] = "text/plain";
    mimeTypeMap[".ief"] = "image/ief";
    mimeTypeMap[".ifb"] = "text/calendar";
    mimeTypeMap[".iii"] = "application/x-iphone";
    mimeTypeMap[".inc"] = "text/plain";
    mimeTypeMap[".inf"] = "application/octet-stream";
    mimeTypeMap[".ini"] = "text/plain";
    mimeTypeMap[".inl"] = "text/plain";
    mimeTypeMap[".ins"] = "application/x-internet-signup";
    mimeTypeMap[".ipa"] = "application/x-itunes-ipa";
    mimeTypeMap[".ipg"] = "application/x-itunes-ipg";
    mimeTypeMap[".ipproj"] = "text/plain";
    mimeTypeMap[".ipsw"] = "application/x-itunes-ipsw";
    mimeTypeMap[".iqy"] = "text/x-ms-iqy";
    mimeTypeMap[".isp"] = "application/x-internet-signup";
    mimeTypeMap[".isma"] = "application/octet-stream";
    mimeTypeMap[".ismv"] = "application/octet-stream";
    mimeTypeMap[".ite"] = "application/x-itunes-ite";
    mimeTypeMap[".itlp"] = "application/x-itunes-itlp";
    mimeTypeMap[".itms"] = "application/x-itunes-itms";
    mimeTypeMap[".itpc"] = "application/x-itunes-itpc";
    mimeTypeMap[".IVF"] = "video/x-ivf";
    mimeTypeMap[".jar"] = "application/java-archive";
    mimeTypeMap[".java"] = "application/octet-stream";
    mimeTypeMap[".jck"] = "application/liquidmotion";
    mimeTypeMap[".jcz"] = "application/liquidmotion";
    mimeTypeMap[".jfif"] = "image/pjpeg";
    mimeTypeMap[".jnlp"] = "application/x-java-jnlp-file";
    mimeTypeMap[".jpb"] = "application/octet-stream";
    mimeTypeMap[".jpe"] = "image/jpeg";
    mimeTypeMap[".jpeg"] = "image/jpeg";
    mimeTypeMap[".jpg"] = "image/jpeg";
    mimeTypeMap[".js"] = "application/javascript";
    mimeTypeMap[".json"] = "application/json";
    mimeTypeMap[".jsx"] = "text/jscript";
    mimeTypeMap[".jsxbin"] = "text/plain";
    mimeTypeMap[".key"] = "application/vnd.apple.keynote";
    mimeTypeMap[".latex"] = "application/x-latex";
    mimeTypeMap[".library-ms"] = "application/windows-library+xml";
    mimeTypeMap[".lit"] = "application/x-ms-reader";
    mimeTypeMap[".loadtest"] = "application/xml";
    mimeTypeMap[".lpk"] = "application/octet-stream";
    mimeTypeMap[".lsf"] = "video/x-la-asf";
    mimeTypeMap[".lst"] = "text/plain";
    mimeTypeMap[".lsx"] = "video/x-la-asf";
    mimeTypeMap[".lzh"] = "application/octet-stream";
    mimeTypeMap[".m13"] = "application/x-msmediaview";
    mimeTypeMap[".m14"] = "application/x-msmediaview";
    mimeTypeMap[".m1v"] = "video/mpeg";
    mimeTypeMap[".m2t"] = "video/vnd.dlna.mpeg-tts";
    mimeTypeMap[".m2ts"] = "video/vnd.dlna.mpeg-tts";
    mimeTypeMap[".m2v"] = "video/mpeg";
    mimeTypeMap[".m3u"] = "audio/x-mpegurl";
    mimeTypeMap[".m3u8"] = "audio/x-mpegurl";
    mimeTypeMap[".m4a"] = "audio/m4a";
    mimeTypeMap[".m4b"] = "audio/m4b";
    mimeTypeMap[".m4p"] = "audio/m4p";
    mimeTypeMap[".m4r"] = "audio/x-m4r";
    mimeTypeMap[".m4v"] = "video/x-m4v";
    mimeTypeMap[".mac"] = "image/x-macpaint";
    mimeTypeMap[".mak"] = "text/plain";
    mimeTypeMap[".man"] = "application/x-troff-man";
    mimeTypeMap[".manifest"] = "application/x-ms-manifest";
    mimeTypeMap[".map"] = "text/plain";
    mimeTypeMap[".master"] = "application/xml";
    mimeTypeMap[".mbox"] = "application/mbox";
    mimeTypeMap[".mda"] = "application/msaccess";
    mimeTypeMap[".mdb"] = "application/x-msaccess";
    mimeTypeMap[".mde"] = "application/msaccess";
    mimeTypeMap[".mdp"] = "application/octet-stream";
    mimeTypeMap[".me"] = "application/x-troff-me";
    mimeTypeMap[".mfp"] = "application/x-shockwave-flash";
    mimeTypeMap[".mht"] = "message/rfc822";
    mimeTypeMap[".mhtml"] = "message/rfc822";
    mimeTypeMap[".mid"] = "audio/mid";
    mimeTypeMap[".midi"] = "audio/mid";
    mimeTypeMap[".mix"] = "application/octet-stream";
    mimeTypeMap[".mk"] = "text/plain";
    mimeTypeMap[".mk3d"] = "video/x-matroska-3d";
    mimeTypeMap[".mka"] = "audio/x-matroska";
    mimeTypeMap[".mkv"] = "video/x-matroska";
    mimeTypeMap[".mmf"] = "application/x-smaf";
    mimeTypeMap[".mno"] = "text/xml";
    mimeTypeMap[".mny"] = "application/x-msmoney";
    mimeTypeMap[".mod"] = "video/mpeg";
    mimeTypeMap[".mov"] = "video/quicktime";
    mimeTypeMap[".movie"] = "video/x-sgi-movie";
    mimeTypeMap[".mp2"] = "video/mpeg";
    mimeTypeMap[".mp2v"] = "video/mpeg";
    mimeTypeMap[".mp3"] = "audio/mpeg";
    mimeTypeMap[".mp4"] = "video/mp4";
    mimeTypeMap[".mp4v"] = "video/mp4";
    mimeTypeMap[".mpa"] = "video/mpeg";
    mimeTypeMap[".mpe"] = "video/mpeg";
    mimeTypeMap[".mpeg"] = "video/mpeg";
    mimeTypeMap[".mpf"] = "application/vnd.ms-mediapackage";
    mimeTypeMap[".mpg"] = "video/mpeg";
    mimeTypeMap[".mpp"] = "application/vnd.ms-project";
    mimeTypeMap[".mpv2"] = "video/mpeg";
    mimeTypeMap[".mqv"] = "video/quicktime";
    mimeTypeMap[".ms"] = "application/x-troff-ms";
    mimeTypeMap[".msg"] = "application/vnd.ms-outlook";
    mimeTypeMap[".msi"] = "application/octet-stream";
    mimeTypeMap[".mso"] = "application/octet-stream";
    mimeTypeMap[".mts"] = "video/vnd.dlna.mpeg-tts";
    mimeTypeMap[".mtx"] = "application/xml";
    mimeTypeMap[".mvb"] = "application/x-msmediaview";
    mimeTypeMap[".mvc"] = "application/x-miva-compiled";
    mimeTypeMap[".mxf"] = "application/mxf";
    mimeTypeMap[".mxp"] = "application/x-mmxp";
    mimeTypeMap[".nc"] = "application/x-netcdf";
    mimeTypeMap[".nsc"] = "video/x-ms-asf";
    mimeTypeMap[".numbers"] = "application/vnd.apple.numbers";
    mimeTypeMap[".nws"] = "message/rfc822";
    mimeTypeMap[".ocx"] = "application/octet-stream";
    mimeTypeMap[".oda"] = "application/oda";
    mimeTypeMap[".odb"] = "application/vnd.oasis.opendocument.database";
    mimeTypeMap[".odc"] = "application/vnd.oasis.opendocument.chart";
    mimeTypeMap[".odf"] = "application/vnd.oasis.opendocument.formula";
    mimeTypeMap[".odg"] = "application/vnd.oasis.opendocument.graphics";
    mimeTypeMap[".odh"] = "text/plain";
    mimeTypeMap[".odi"] = "application/vnd.oasis.opendocument.image";
    mimeTypeMap[".odl"] = "text/plain";
    mimeTypeMap[".odm"] = "application/vnd.oasis.opendocument.text-master";
    mimeTypeMap[".odp"] = "application/vnd.oasis.opendocument.presentation";
    mimeTypeMap[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    mimeTypeMap[".odt"] = "application/vnd.oasis.opendocument.text";
    mimeTypeMap[".oga"] = "audio/ogg";
    mimeTypeMap[".ogg"] = "audio/ogg";
    mimeTypeMap[".ogv"] = "video/ogg";
    mimeTypeMap[".ogx"] = "application/ogg";
    mimeTypeMap[".one"] = "application/onenote";
    mimeTypeMap[".onea"] = "application/onenote";
    mimeTypeMap[".onepkg"] = "application/onenote";
    mimeTypeMap[".onetmp"] = "application/onenote";
    mimeTypeMap[".onetoc"] = "application/onenote";
    mimeTypeMap[".onetoc2"] = "application/onenote";
    mimeTypeMap[".opus"] = "audio/ogg";
    mimeTypeMap[".orderedtest"] = "application/xml";
    mimeTypeMap[".osdx"] = "application/opensearchdescription+xml";
    mimeTypeMap[".otf"] = "application/font-sfnt";
    mimeTypeMap[".otg"] = "application/vnd.oasis.opendocument.graphics-template";
    mimeTypeMap[".oth"] = "application/vnd.oasis.opendocument.text-web";
    mimeTypeMap[".otp"] = "application/vnd.oasis.opendocument.presentation-template";
    mimeTypeMap[".ots"] = "application/vnd.oasis.opendocument.spreadsheet-template";
    mimeTypeMap[".ott"] = "application/vnd.oasis.opendocument.text-template";
    mimeTypeMap[".oxps"] = "application/oxps";
    mimeTypeMap[".oxt"] = "application/vnd.openofficeorg.extension";
    mimeTypeMap[".p10"] = "application/pkcs10";
    mimeTypeMap[".p12"] = "application/x-pkcs12";
    mimeTypeMap[".p7b"] = "application/x-pkcs7-certificates";
    mimeTypeMap[".p7c"] = "application/pkcs7-mime";
    mimeTypeMap[".p7m"] = "application/pkcs7-mime";
    mimeTypeMap[".p7r"] = "application/x-pkcs7-certreqresp";
    mimeTypeMap[".p7s"] = "application/pkcs7-signature";
    mimeTypeMap[".pages"] = "application/vnd.apple.pages";
    mimeTypeMap[".pbm"] = "image/x-portable-bitmap";
    mimeTypeMap[".pcast"] = "application/x-podcast";
    mimeTypeMap[".pct"] = "image/pict";
    mimeTypeMap[".pcx"] = "application/octet-stream";
    mimeTypeMap[".pcz"] = "application/octet-stream";
    mimeTypeMap[".pdf"] = "application/pdf";
    mimeTypeMap[".pfb"] = "application/octet-stream";
    mimeTypeMap[".pfm"] = "application/octet-stream";
    mimeTypeMap[".pfx"] = "application/x-pkcs12";
    mimeTypeMap[".pgm"] = "image/x-portable-graymap";
    mimeTypeMap[".pic"] = "image/pict";
    mimeTypeMap[".pict"] = "image/pict";
    mimeTypeMap[".pkgdef"] = "text/plain";
    mimeTypeMap[".pkgundef"] = "text/plain";
    mimeTypeMap[".pko"] = "application/vnd.ms-pki.pko";
    mimeTypeMap[".pls"] = "audio/scpls";
    mimeTypeMap[".pma"] = "application/x-perfmon";
    mimeTypeMap[".pmc"] = "application/x-perfmon";
    mimeTypeMap[".pml"] = "application/x-perfmon";
    mimeTypeMap[".pmr"] = "application/x-perfmon";
    mimeTypeMap[".pmw"] = "application/x-perfmon";
    mimeTypeMap[".png"] = "image/png";
    mimeTypeMap[".pnm"] = "image/x-portable-anymap";
    mimeTypeMap[".pnt"] = "image/x-macpaint";
    mimeTypeMap[".pntg"] = "image/x-macpaint";
    mimeTypeMap[".pnz"] = "image/png";
    mimeTypeMap[".pot"] = "application/vnd.ms-powerpoint";
    mimeTypeMap[".potm"] = "application/vnd.ms-powerpoint.template.macroEnabled.12";
    mimeTypeMap[".potx"] = "application/vnd.openxmlformats-officedocument.presentationml.template";
    mimeTypeMap[".ppa"] = "application/vnd.ms-powerpoint";
    mimeTypeMap[".ppam"] = "application/vnd.ms-powerpoint.addin.macroEnabled.12";
    mimeTypeMap[".ppm"] = "image/x-portable-pixmap";
    mimeTypeMap[".pps"] = "application/vnd.ms-powerpoint";
    mimeTypeMap[".ppsm"] = "application/vnd.ms-powerpoint.slideshow.macroEnabled.12";
    mimeTypeMap[".ppsx"] = "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
    mimeTypeMap[".ppt"] = "application/vnd.ms-powerpoint";
    mimeTypeMap[".pptm"] = "application/vnd.ms-powerpoint.presentation.macroEnabled.12";
    mimeTypeMap[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mimeTypeMap[".prf"] = "application/pics-rules";
    mimeTypeMap[".prm"] = "application/octet-stream";
    mimeTypeMap[".prx"] = "application/octet-stream";
    mimeTypeMap[".ps"] = "application/postscript";
    mimeTypeMap[".psc1"] = "application/PowerShell";
    mimeTypeMap[".psd"] = "application/octet-stream";
    mimeTypeMap[".psess"] = "application/xml";
    mimeTypeMap[".psm"] = "application/octet-stream";
    mimeTypeMap[".psp"] = "application/octet-stream";
    mimeTypeMap[".pst"] = "application/vnd.ms-outlook";
    mimeTypeMap[".pub"] = "application/x-mspublisher";
    mimeTypeMap[".pwz"] = "application/vnd.ms-powerpoint";
    mimeTypeMap[".qht"] = "text/x-html-insertion";
    mimeTypeMap[".qhtm"] = "text/x-html-insertion";
    mimeTypeMap[".qt"] = "video/quicktime";
    mimeTypeMap[".qti"] = "image/x-quicktime";
    mimeTypeMap[".qtif"] = "image/x-quicktime";
    mimeTypeMap[".qtl"] = "application/x-quicktimeplayer";
    mimeTypeMap[".qxd"] = "application/octet-stream";
    mimeTypeMap[".ra"] = "audio/x-pn-realaudio";
    mimeTypeMap[".ram"] = "audio/x-pn-realaudio";
    mimeTypeMap[".rar"] = "application/x-rar-compressed";
    mimeTypeMap[".ras"] = "image/x-cmu-raster";
    mimeTypeMap[".rat"] = "application/rat-file";
    mimeTypeMap[".rc"] = "text/plain";
    mimeTypeMap[".rc2"] = "text/plain";
    mimeTypeMap[".rct"] = "text/plain";
    mimeTypeMap[".rdlc"] = "application/xml";
    mimeTypeMap[".reg"] = "text/plain";
    mimeTypeMap[".resx"] = "application/xml";
    mimeTypeMap[".rf"] = "image/vnd.rn-realflash";
    mimeTypeMap[".rgb"] = "image/x-rgb";
    mimeTypeMap[".rgs"] = "text/plain";
    mimeTypeMap[".rm"] = "application/vnd.rn-realmedia";
    mimeTypeMap[".rmi"] = "audio/mid";
    mimeTypeMap[".rmp"] = "application/vnd.rn-rn_music_package";
    mimeTypeMap[".rmvb"] = "application/vnd.rn-realmedia-vbr";
    mimeTypeMap[".roff"] = "application/x-troff";
    mimeTypeMap[".rpm"] = "audio/x-pn-realaudio-plugin";
    mimeTypeMap[".rqy"] = "text/x-ms-rqy";
    mimeTypeMap[".rtf"] = "application/rtf";
    mimeTypeMap[".rtx"] = "text/richtext";
    mimeTypeMap[".rvt"] = "application/octet-stream";
    mimeTypeMap[".ruleset"] = "application/xml";
    mimeTypeMap[".s"] = "text/plain";
    mimeTypeMap[".safariextz"] = "application/x-safari-safariextz";
    mimeTypeMap[".scd"] = "application/x-msschedule";
    mimeTypeMap[".scr"] = "text/plain";
    mimeTypeMap[".sct"] = "text/scriptlet";
    mimeTypeMap[".sd2"] = "audio/x-sd2";
    mimeTypeMap[".sdp"] = "application/sdp";
    mimeTypeMap[".sea"] = "application/octet-stream";
    mimeTypeMap[".searchConnector-ms"] = "application/windows-search-connector+xml";
    mimeTypeMap[".setpay"] = "application/set-payment-initiation";
    mimeTypeMap[".setreg"] = "application/set-registration-initiation";
    mimeTypeMap[".settings"] = "application/xml";
    mimeTypeMap[".sgimb"] = "application/x-sgimb";
    mimeTypeMap[".sgml"] = "text/sgml";
    mimeTypeMap[".sh"] = "application/x-sh";
    mimeTypeMap[".shar"] = "application/x-shar";
    mimeTypeMap[".shtml"] = "text/html";
    mimeTypeMap[".sit"] = "application/x-stuffit";
    mimeTypeMap[".sitemap"] = "application/xml";
    mimeTypeMap[".skin"] = "application/xml";
    mimeTypeMap[".skp"] = "application/x-koan";
    mimeTypeMap[".sldm"] = "application/vnd.ms-powerpoint.slide.macroEnabled.12";
    mimeTypeMap[".sldx"] = "application/vnd.openxmlformats-officedocument.presentationml.slide";
    mimeTypeMap[".slk"] = "application/vnd.ms-excel";
    mimeTypeMap[".sln"] = "text/plain";
    mimeTypeMap[".slupkg-ms"] = "application/x-ms-license";
    mimeTypeMap[".smd"] = "audio/x-smd";
    mimeTypeMap[".smi"] = "application/octet-stream";
    mimeTypeMap[".smx"] = "audio/x-smd";
    mimeTypeMap[".smz"] = "audio/x-smd";
    mimeTypeMap[".snd"] = "audio/basic";
    mimeTypeMap[".snippet"] = "application/xml";
    mimeTypeMap[".snp"] = "application/octet-stream";
    mimeTypeMap[".sql"] = "application/sql";
    mimeTypeMap[".sol"] = "text/plain";
    mimeTypeMap[".sor"] = "text/plain";
    mimeTypeMap[".spc"] = "application/x-pkcs7-certificates";
    mimeTypeMap[".spl"] = "application/futuresplash";
    mimeTypeMap[".spx"] = "audio/ogg";
    mimeTypeMap[".src"] = "application/x-wais-source";
    mimeTypeMap[".srf"] = "text/plain";
    mimeTypeMap[".SSISDeploymentManifest"] = "text/xml";
    mimeTypeMap[".ssm"] = "application/streamingmedia";
    mimeTypeMap[".sst"] = "application/vnd.ms-pki.certstore";
    mimeTypeMap[".stl"] = "application/vnd.ms-pki.stl";
    mimeTypeMap[".sv4cpio"] = "application/x-sv4cpio";
    mimeTypeMap[".sv4crc"] = "application/x-sv4crc";
    mimeTypeMap[".svc"] = "application/xml";
    mimeTypeMap[".svg"] = "image/svg+xml";
    mimeTypeMap[".swf"] = "application/x-shockwave-flash";
    mimeTypeMap[".step"] = "application/step";
    mimeTypeMap[".stp"] = "application/step";
    mimeTypeMap[".t"] = "application/x-troff";
    mimeTypeMap[".tar"] = "application/x-tar";
    mimeTypeMap[".tcl"] = "application/x-tcl";
    mimeTypeMap[".testrunconfig"] = "application/xml";
    mimeTypeMap[".testsettings"] = "application/xml";
    mimeTypeMap[".tex"] = "application/x-tex";
    mimeTypeMap[".texi"] = "application/x-texinfo";
    mimeTypeMap[".texinfo"] = "application/x-texinfo";
    mimeTypeMap[".tgz"] = "application/x-compressed";
    mimeTypeMap[".thmx"] = "application/vnd.ms-officetheme";
    mimeTypeMap[".thn"] = "application/octet-stream";
    mimeTypeMap[".tif"] = "image/tiff";
    mimeTypeMap[".tiff"] = "image/tiff";
    mimeTypeMap[".tlh"] = "text/plain";
    mimeTypeMap[".tli"] = "text/plain";
    mimeTypeMap[".toc"] = "application/octet-stream";
    mimeTypeMap[".tr"] = "application/x-troff";
    mimeTypeMap[".trm"] = "application/x-msterminal";
    mimeTypeMap[".trx"] = "application/xml";
    mimeTypeMap[".ts"] = "video/vnd.dlna.mpeg-tts";
    mimeTypeMap[".tsv"] = "text/tab-separated-values";
    mimeTypeMap[".ttf"] = "application/font-sfnt";
    mimeTypeMap[".tts"] = "video/vnd.dlna.mpeg-tts";
    mimeTypeMap[".txt"] = "text/plain";
    mimeTypeMap[".u32"] = "application/octet-stream";
    mimeTypeMap[".uls"] = "text/iuls";
    mimeTypeMap[".user"] = "text/plain";
    mimeTypeMap[".ustar"] = "application/x-ustar";
    mimeTypeMap[".vb"] = "text/plain";
    mimeTypeMap[".vbdproj"] = "text/plain";
    mimeTypeMap[".vbk"] = "video/mpeg";
    mimeTypeMap[".vbproj"] = "text/plain";
    mimeTypeMap[".vbs"] = "text/vbscript";
    mimeTypeMap[".vcf"] = "text/x-vcard";
    mimeTypeMap[".vcproj"] = "application/xml";
    mimeTypeMap[".vcs"] = "text/plain";
    mimeTypeMap[".vcxproj"] = "application/xml";
    mimeTypeMap[".vddproj"] = "text/plain";
    mimeTypeMap[".vdp"] = "text/plain";
    mimeTypeMap[".vdproj"] = "text/plain";
    mimeTypeMap[".vdx"] = "application/vnd.ms-visio.viewer";
    mimeTypeMap[".vml"] = "text/xml";
    mimeTypeMap[".vscontent"] = "application/xml";
    mimeTypeMap[".vsct"] = "text/xml";
    mimeTypeMap[".vsd"] = "application/vnd.visio";
    mimeTypeMap[".vsi"] = "application/ms-vsi";
    mimeTypeMap[".vsix"] = "application/vsix";
    mimeTypeMap[".vsixlangpack"] = "text/xml";
    mimeTypeMap[".vsixmanifest"] = "text/xml";
    mimeTypeMap[".vsmdi"] = "application/xml";
    mimeTypeMap[".vspscc"] = "text/plain";
    mimeTypeMap[".vss"] = "application/vnd.visio";
    mimeTypeMap[".vsscc"] = "text/plain";
    mimeTypeMap[".vssettings"] = "text/xml";
    mimeTypeMap[".vssscc"] = "text/plain";
    mimeTypeMap[".vst"] = "application/vnd.visio";
    mimeTypeMap[".vstemplate"] = "text/xml";
    mimeTypeMap[".vsto"] = "application/x-ms-vsto";
    mimeTypeMap[".vsw"] = "application/vnd.visio";
    mimeTypeMap[".vsx"] = "application/vnd.visio";
    mimeTypeMap[".vtt"] = "text/vtt";
    mimeTypeMap[".vtx"] = "application/vnd.visio";
    mimeTypeMap[".wasm"] = "application/wasm";
    mimeTypeMap[".wav"] = "audio/wav";
    mimeTypeMap[".wave"] = "audio/wav";
    mimeTypeMap[".wax"] = "audio/x-ms-wax";
    mimeTypeMap[".wbk"] = "application/msword";
    mimeTypeMap[".wbmp"] = "image/vnd.wap.wbmp";
    mimeTypeMap[".wcm"] = "application/vnd.ms-works";
    mimeTypeMap[".wdb"] = "application/vnd.ms-works";
    mimeTypeMap[".wdp"] = "image/vnd.ms-photo";
    mimeTypeMap[".webarchive"] = "application/x-safari-webarchive";
    mimeTypeMap[".webm"] = "video/webm";
    mimeTypeMap[".webp"] = "image/webp";
    mimeTypeMap[".webtest"] = "application/xml";
    mimeTypeMap[".wiq"] = "application/xml";
    mimeTypeMap[".wiz"] = "application/msword";
    mimeTypeMap[".wks"] = "application/vnd.ms-works";
    mimeTypeMap[".WLMP"] = "application/wlmoviemaker";
    mimeTypeMap[".wlpginstall"] = "application/x-wlpg-detect";
    mimeTypeMap[".wlpginstall3"] = "application/x-wlpg3-detect";
    mimeTypeMap[".wm"] = "video/x-ms-wm";
    mimeTypeMap[".wma"] = "audio/x-ms-wma";
    mimeTypeMap[".wmd"] = "application/x-ms-wmd";
    mimeTypeMap[".wmf"] = "application/x-msmetafile";
    mimeTypeMap[".wml"] = "text/vnd.wap.wml";
    mimeTypeMap[".wmlc"] = "application/vnd.wap.wmlc";
    mimeTypeMap[".wmls"] = "text/vnd.wap.wmlscript";
    mimeTypeMap[".wmlsc"] = "application/vnd.wap.wmlscriptc";
    mimeTypeMap[".wmp"] = "video/x-ms-wmp";
    mimeTypeMap[".wmv"] = "video/x-ms-wmv";
    mimeTypeMap[".wmx"] = "video/x-ms-wmx";
    mimeTypeMap[".wmz"] = "application/x-ms-wmz";
    mimeTypeMap[".woff"] = "application/font-woff";
    mimeTypeMap[".woff2"] = "application/font-woff2";
    mimeTypeMap[".wpl"] = "application/vnd.ms-wpl";
    mimeTypeMap[".wps"] = "application/vnd.ms-works";
    mimeTypeMap[".wri"] = "application/x-mswrite";
    mimeTypeMap[".wrl"] = "x-world/x-vrml";
    mimeTypeMap[".wrz"] = "x-world/x-vrml";
    mimeTypeMap[".wsc"] = "text/scriptlet";
    mimeTypeMap[".wsdl"] = "text/xml";
    mimeTypeMap[".wvx"] = "video/x-ms-wvx";
    mimeTypeMap[".x"] = "application/directx";
    mimeTypeMap[".xaf"] = "x-world/x-vrml";
    mimeTypeMap[".xaml"] = "application/xaml+xml";
    mimeTypeMap[".xap"] = "application/x-silverlight-app";
    mimeTypeMap[".xbap"] = "application/x-ms-xbap";
    mimeTypeMap[".xbm"] = "image/x-xbitmap";
    mimeTypeMap[".xdr"] = "text/plain";
    mimeTypeMap[".xht"] = "application/xhtml+xml";
    mimeTypeMap[".xhtml"] = "application/xhtml+xml";
    mimeTypeMap[".xla"] = "application/vnd.ms-excel";
    mimeTypeMap[".xlam"] = "application/vnd.ms-excel.addin.macroEnabled.12";
    mimeTypeMap[".xlc"] = "application/vnd.ms-excel";
    mimeTypeMap[".xld"] = "application/vnd.ms-excel";
    mimeTypeMap[".xlk"] = "application/vnd.ms-excel";
    mimeTypeMap[".xll"] = "application/vnd.ms-excel";
    mimeTypeMap[".xlm"] = "application/vnd.ms-excel";
    mimeTypeMap[".xls"] = "application/vnd.ms-excel";
    mimeTypeMap[".xlsb"] = "application/vnd.ms-excel.sheet.binary.macroEnabled.12";
    mimeTypeMap[".xlsm"] = "application/vnd.ms-excel.sheet.macroEnabled.12";
    mimeTypeMap[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mimeTypeMap[".xlt"] = "application/vnd.ms-excel";
    mimeTypeMap[".xltm"] = "application/vnd.ms-excel.template.macroEnabled.12";
    mimeTypeMap[".xltx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
    mimeTypeMap[".xlw"] = "application/vnd.ms-excel";
    mimeTypeMap[".xml"] = "text/xml";
    mimeTypeMap[".xmp"] = "application/octet-stream";
    mimeTypeMap[".xmta"] = "application/xml";
    mimeTypeMap[".xof"] = "x-world/x-vrml";
    mimeTypeMap[".XOML"] = "text/plain";
    mimeTypeMap[".xpm"] = "image/x-xpixmap";
    mimeTypeMap[".xps"] = "application/vnd.ms-xpsdocument";
    mimeTypeMap[".xrm-ms"] = "text/xml";
    mimeTypeMap[".xsc"] = "application/xml";
    mimeTypeMap[".xsd"] = "text/xml";
    mimeTypeMap[".xsf"] = "text/xml";
    mimeTypeMap[".xsl"] = "text/xml";
    mimeTypeMap[".xslt"] = "text/xml";
    mimeTypeMap[".xsn"] = "application/octet-stream";
    mimeTypeMap[".xss"] = "application/xml";
    mimeTypeMap[".xspf"] = "application/xspf+xml";
    mimeTypeMap[".xtp"] = "application/octet-stream";
    mimeTypeMap[".xwd"] = "image/x-xwindowdump";
    mimeTypeMap[".z"] = "application/x-compress";
    mimeTypeMap[".zip"] = "application/zip";

    mimeTypeMap["application/fsharp-script"] = ".fsx";
    mimeTypeMap["application/msaccess"] = ".adp";
    mimeTypeMap["application/msword"] = ".doc";
    mimeTypeMap["application/octet-stream"] = ".bin";
    mimeTypeMap["application/onenote"] = ".one";
    mimeTypeMap["application/postscript"] = ".eps";
    mimeTypeMap["application/step"] = ".step";
    mimeTypeMap["application/vnd.apple.keynote"] = ".key";
    mimeTypeMap["application/vnd.apple.numbers"] = ".numbers";
    mimeTypeMap["application/vnd.apple.pages"] = ".pages";
    mimeTypeMap["application/vnd.ms-excel"] = ".xls";
    mimeTypeMap["application/vnd.ms-powerpoint"] = ".ppt";
    mimeTypeMap["application/vnd.ms-works"] = ".wks";
    mimeTypeMap["application/vnd.visio"] = ".vsd";
    mimeTypeMap["application/x-director"] = ".dir";
    mimeTypeMap["application/x-msdos-program"] = ".exe";
    mimeTypeMap["application/x-shockwave-flash"] = ".swf";
    mimeTypeMap["application/x-x509-ca-cert"] = ".cer";
    mimeTypeMap["application/x-zip-compressed"] = ".zip";
    mimeTypeMap["application/xhtml+xml"] = ".xhtml";
    mimeTypeMap["application/x-iwork-keynote-sffkey"] = ".key";
    mimeTypeMap["application/x-iwork-numbers-sffnumbers"] = ".numbers";
    mimeTypeMap["application/x-iwork-pages-sffpages"] = ".pages";
    mimeTypeMap["application/xml"] = ".xml";
    mimeTypeMap["audio/aac"] = ".AAC";
    mimeTypeMap["audio/aiff"] = ".aiff";
    mimeTypeMap["audio/basic"] = ".snd";
    mimeTypeMap["audio/mid"] = ".midi";
    mimeTypeMap["audio/mp4"] = ".m4a";
    mimeTypeMap["audio/ogg"] = ".ogg";
    mimeTypeMap["audio/ogg; codecs=opus"] = ".opus";
    mimeTypeMap["audio/wav"] = ".wav";
    mimeTypeMap["audio/x-m4a"] = ".m4a";
    mimeTypeMap["audio/x-mpegurl"] = ".m3u";
    mimeTypeMap["audio/x-pn-realaudio"] = ".ra";
    mimeTypeMap["audio/x-smd"] = ".smd";
    mimeTypeMap["image/bmp"] = ".bmp";
    mimeTypeMap["image/heic"] = ".heic";
    mimeTypeMap["image/heif"] = ".heif";
    mimeTypeMap["image/jpeg"] = ".jpg";
    mimeTypeMap["image/pict"] = ".pic";
    mimeTypeMap["image/png"] = ".png";
    mimeTypeMap["image/x-png"] = ".png";
    mimeTypeMap["image/tiff"] = ".tiff";
    mimeTypeMap["image/x-macpaint"] = ".mac";
    mimeTypeMap["image/x-quicktime"] = ".qti";
    mimeTypeMap["message/rfc822"] = ".eml";
    mimeTypeMap["text/calendar"] = ".ics";
    mimeTypeMap["text/html"] = ".html";
    mimeTypeMap["text/plain"] = ".txt";
    mimeTypeMap["text/scriptlet"] = ".wsc";
    mimeTypeMap["text/xml"] = ".xml";
    mimeTypeMap["video/3gpp"] = ".3gp";
    mimeTypeMap["video/3gpp2"] = ".3gp2";
    mimeTypeMap["video/mp4"] = ".mp4";
    mimeTypeMap["video/mpeg"] = ".mpg";
    mimeTypeMap["video/quicktime"] = ".mov";
    mimeTypeMap["video/vnd.dlna.mpeg-tts"] = ".m2t";
    mimeTypeMap["video/x-dv"] = ".dv";
    mimeTypeMap["video/x-la-asf"] = ".lsf";
    mimeTypeMap["video/x-ms-asf"] = ".asf";
    mimeTypeMap["x-world/x-vrml"] = ".xof";
}

bool HttpMimeType::TryGetMimeType(const std::string &fileNameOrExtension, std::string &mimeType)
{
    Initialize();

    if(fileNameOrExtension.size() < 3)
        return false;


    std::string extension = File::GetExtension(fileNameOrExtension);

    if(extension.size() >= 3)
    {
        extension = StringUtility::ToLower(extension);
        if(mimeTypeMap.count(extension) > 0)
        {
            mimeType = mimeTypeMap[extension];
            return true;
        }
    }

    return false;
}