#ifndef HTTPREQUESTMETHOD_HPP
#define HTTPREQUESTMETHOD_HPP

enum class HttpRequestMethod : int
{
    Connect,
    Delete,
    Get,
    Head,
    Options,
    Patch,
    Post,
    Put,
    Trace,
    Unknown
};

#endif