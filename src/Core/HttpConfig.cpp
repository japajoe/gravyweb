#include "HttpConfig.hpp"


#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

HttpConfig::HttpConfig()
{

}

bool HttpConfig::LoadFromFile(const std::string &path)
{
    FILE *fp;
    char *line = nullptr;
    size_t len = 0;
    ssize_t read;

    //Opens the file if it exists
    fp = fopen(path.c_str(), "r");
    if (fp == nullptr)
        return false;


    //Add all lines of the file into a vector
    std::vector<std::string> lines;
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        lines.push_back(std::string(line));
    }

    //Close the file
    fclose(fp);

    std::unordered_map<std::string,std::string> expectedKeyValuePairs;
    expectedKeyValuePairs["host"] = "localhost";
    expectedKeyValuePairs["name"] = "ServerName";
    expectedKeyValuePairs["public_html"] = "www/public_html";
    expectedKeyValuePairs["private_html"] = "www/private_html";
    expectedKeyValuePairs["certificate_path"] = "cert.pem";
    expectedKeyValuePairs["private_key_path"] = "key.pem";
    expectedKeyValuePairs["port"] = "8080";
    expectedKeyValuePairs["ssl_port"] = "8081";
    expectedKeyValuePairs["use_https"] = "true";
    expectedKeyValuePairs["use_https_forwarding"] = "true";
    expectedKeyValuePairs["max_header_size"] = "8192";
    expectedKeyValuePairs["buffer_size"] = "4096";

    std::string separator = " ";
    std::unordered_map<std::string,std::string> keyValuePairs;

    for(size_t i = 0; i < lines.size(); i++)
    {
        //Remove new line characters
        lines[i].erase(std::remove_if(lines[i].begin(), lines[i].end(), 
                [&](char ch) 
                { return std::iscntrl(static_cast<unsigned char>(ch));}), 
                lines[i].end());


        //Split the string at first space
        std::string key, value;
        size_t pos = lines[i].find(separator);
        key = lines[i].substr(0, pos);
        value = lines[i].substr(pos +1, std::string::npos);

        //Make the key lower case
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        //Check if given key is valid
        if(expectedKeyValuePairs.count(key) == 0)
        {
            std::cout << "Unexpected key in config: " << key << '\n';
            return false;
        }

        keyValuePairs[key] = value;
    }

    if(keyValuePairs.size() != expectedKeyValuePairs.size())
    {
        std::cout << "Config file is incomplete\n";
        return false;
    }

    std::string host = keyValuePairs["host"];
    std::string name = keyValuePairs["name"];
    std::string publicHtml = keyValuePairs["public_html"];
    std::string privateHtml = keyValuePairs["private_html"];
    std::string certificatePath = keyValuePairs["certificate_path"];
    std::string privateKeyPath = keyValuePairs["private_key_path"];
    uint16_t port = 8080;
    uint16_t sslPort = 8081;
    bool useHttps = false;
    bool useHttpsForwarding = false;
    uint32_t maxHeaderSize = 8192;
    uint32_t bufferSize = 4096;
    
    if(!ParseNumber(keyValuePairs["port"], port))
    {
        std::cout << "Failed to parse port\n";
        return false;
    }
    
    if(!ParseNumber(keyValuePairs["ssl_port"], sslPort))
    {
        std::cout << "Failed to parse ssl_port\n";
        return false;
    }

    if(!ParseBool(keyValuePairs["use_https"], useHttps))
    {
        std::cout << "Failed to parse use_https\n";
        return false;
    }

    if(!ParseBool(keyValuePairs["use_https_forwarding"], useHttpsForwarding))
    {
        std::cout << "Failed to parse use_https_forwarding use_https\n";
        return false;
    }
    
    if(!ParseNumber(keyValuePairs["max_header_size"], maxHeaderSize))
    {
        std::cout << "Failed to parse max_header_size\n";
        return false;
    }
    
    if(!ParseNumber(keyValuePairs["buffer_size"], bufferSize))
    {
        std::cout << "Failed to parse buffer_size\n";
        return false;
    }

    this->host = host;
    this->name = name;
    this->publicHtml = publicHtml;
    this->privateHtml = privateHtml;
    this->certificatePath = certificatePath;
    this->privateKeyPath = privateKeyPath;
    this->port = port;
    this->sslPort = sslPort;
    this->useHttps = useHttps;
    this->useHttpsForwarding = useHttpsForwarding;
    this->maxHeaderSize = maxHeaderSize;
    this->bufferSize = bufferSize;

    return true;
}
