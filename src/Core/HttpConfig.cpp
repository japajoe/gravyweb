#include "HttpConfig.hpp"
#include "Console.hpp"
#include "StringUtility.hpp"
#include <cstdint>
#include <string>
#include <regex>
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
    std::vector<std::string> inputLines;
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        inputLines.push_back(std::string(line));
    }

    //Close the file
    fclose(fp);

    std::vector<std::string> lines;

    //Strip comments
    for (const auto& line : inputLines) {
        // Use regex to remove comments (lines starting with # or ; and anything after # or ;)
        std::string processedLine = std::regex_replace(line, std::regex("[#;].*"), "");
        
        // Remove leading and trailing whitespaces
        processedLine = std::regex_replace(processedLine, std::regex("^\\s+|\\s+$"), "");

        // Add the processed line to the result vector if it's not empty
        if (!processedLine.empty()) {
            processedLine = StringUtility::TrimEnd(processedLine);
            lines.push_back(processedLine);
            std::cout << processedLine << '\n';
        }
    }

    std::unordered_map<std::string,std::string> expectedKeyValuePairs;
    expectedKeyValuePairs["host"] = "localhost";
    expectedKeyValuePairs["name"] = "ServerName";
    expectedKeyValuePairs["bind_address"] = "0.0.0.0";
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
            Console::WriteLog("Unexpected key in config: " + key);
            return false;
        }

        keyValuePairs[key] = value;
    }

    if(keyValuePairs.size() != expectedKeyValuePairs.size())
    {
        Console::WriteLog("Config file is incomplete");
        return false;
    }

    std::string host = keyValuePairs["host"];
    std::string name = keyValuePairs["name"];
    std::string bindAddress = keyValuePairs["bind_address"];
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
        Console::WriteLog("Failed to parse port");
        return false;
    }
    
    if(!ParseNumber(keyValuePairs["ssl_port"], sslPort))
    {
        Console::WriteLog("Failed to parse ssl_port");
        return false;
    }

    if(!ParseBool(keyValuePairs["use_https"], useHttps))
    {
        Console::WriteLog("Failed to parse use_https");
        return false;
    }

    if(!ParseBool(keyValuePairs["use_https_forwarding"], useHttpsForwarding))
    {
        Console::WriteLog("Failed to parse use_https_forwarding use_https");
        return false;
    }
    
    if(!ParseNumber(keyValuePairs["max_header_size"], maxHeaderSize))
    {
        Console::WriteLog("Failed to parse max_header_size");
        return false;
    }
    
    if(!ParseNumber(keyValuePairs["buffer_size"], bufferSize))
    {
        Console::WriteLog("Failed to parse buffer_size");
        return false;
    }

    this->host = host;
    this->name = name;
    this->bindAddress = bindAddress;
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
