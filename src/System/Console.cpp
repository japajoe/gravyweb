#include "Console.hpp"
#include "DateTime.hpp"
#include <iostream>
#include <map>

static std::map<ConsoleColor, std::string> consoleColorMap;
LogFunction Console::logFunction = nullptr;
LogFunction Console::errorFunction = nullptr;

static void InitializeConsoleColors()
{
    if(consoleColorMap.size() == 0)
    {
        consoleColorMap[ConsoleColor::Red] = "\x1B[31m";
        consoleColorMap[ConsoleColor::Green] = "\x1B[32m";
        consoleColorMap[ConsoleColor::Yellow] = "\x1B[33m";
        consoleColorMap[ConsoleColor::Blue] = "\x1B[34m";
        consoleColorMap[ConsoleColor::Magenta] = "\x1B[35m";
        consoleColorMap[ConsoleColor::Cyan] = "\x1B[36m";
        consoleColorMap[ConsoleColor::White] = "\x1B[37m";
        consoleColorMap[ConsoleColor::Reset] = "\x1B[0m";
    }
}

void Console::WriteLine(const std::string &text, ConsoleColor color)
{
#ifdef _WIN32
    std::cout << text << '\n';
#else
    InitializeConsoleColors();
    std::cout << consoleColorMap[color] << text << consoleColorMap[ConsoleColor::Reset] << '\n';
#endif
}

void Console::Write(const std::string &text, ConsoleColor color)
{
#ifdef _WIN32
    std::cout << text;
#else
    InitializeConsoleColors();
    std::cout << consoleColorMap[color] << text << consoleColorMap[ConsoleColor::Reset];
#endif
}

void Console::WriteLog(const std::string &text)
{
    if(logFunction)
    {
        logFunction(text);
        return;
    }

    std::string timestamp = DateTime::Now().FormattedTimestamp();
#ifdef _WIN32
    std::cout << timestamp << ' ' << text << '\n';
#else
    InitializeConsoleColors();    
    std::cout << consoleColorMap[ConsoleColor::Green] << timestamp << consoleColorMap[ConsoleColor::Reset] << ' ' << text << '\n';
#endif
}

void Console::WriteError(const std::string &text)
{
    if(errorFunction)
    {
        errorFunction(text);
        return;
    }

    std::string timestamp = DateTime::Now().FormattedTimestamp();
#ifdef _WIN32
    std::cout << timestamp << ' ' << text << '\n';
#else
    InitializeConsoleColors();    
    std::cout << consoleColorMap[ConsoleColor::Green] << timestamp << consoleColorMap[ConsoleColor::Red] << ' ' << text << consoleColorMap[ConsoleColor::Reset] << '\n';
#endif
}

void Console::SetLogFunction(const LogFunction &logFunction)
{
    Console::logFunction = logFunction;
}

void Console::SetErrorFunction(const LogFunction &errorFunction)
{
    Console::errorFunction = errorFunction;
}