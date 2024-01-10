#include "HttpSettings.hpp"

HttpConfig HttpSettings::config;

void HttpSettings::LoadFromConfig(const HttpConfig &config)
{
    HttpSettings::config = config;
}
std::string HttpSettings::GetHost()
{
    return config.host;
}

std::string HttpSettings::GetName()
{
    return config.name;
}

std::string HttpSettings::GetBindAddress()
{
    return config.bindAddress;
}

std::string HttpSettings::GetPublicHtml()
{
    return config.publicHtml;
}

std::string HttpSettings::GetPrivateHtml()
{
    return config.privateHtml;
}

std::string HttpSettings::GetCertificatePath()
{
    return config.certificatePath;
}

std::string HttpSettings::GetPrivateKeyPath()
{
    return config.privateKeyPath;
}

uint16_t HttpSettings::GetPort()
{
    return config.port;
}

uint16_t HttpSettings::GetSslPort()
{
    return config.sslPort;
}

bool HttpSettings::GetUseHttps()
{
    return config.useHttps;
}

bool HttpSettings::GetUseHttpsForwarding()
{
    return config.useHttpsForwarding;
}

uint32_t HttpSettings::GetMaxHeaderSize()
{
    return config.maxHeaderSize;
}

uint32_t HttpSettings::GetBufferSize()
{
    return config.bufferSize;
}
