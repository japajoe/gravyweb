#include "Console.hpp"
#include "DateTime.hpp"
#include <map>
#include <iostream>

static std::map<ConsoleColor, std::string> consoleColorMap;

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
    InitializeConsoleColors();

    std::string &col = consoleColorMap[color];
    std::string &colreset = consoleColorMap[ConsoleColor::Reset];
    std::cout << col << text << colreset << '\n';
}

void Console::Write(const std::string &text, ConsoleColor color)
{
    InitializeConsoleColors();

    std::string &col = consoleColorMap[color];
    std::string &colreset = consoleColorMap[ConsoleColor::Reset];
    std::cout << col << text << colreset;
}

void Console::WriteLog(const std::string &text)
{
    InitializeConsoleColors();

    std::string timestamp = DateTime::Now().FormattedTimestamp();

    std::string &colTime = consoleColorMap[ConsoleColor::Green];
    std::string &colreset = consoleColorMap[ConsoleColor::Reset];
    std::cout << colTime << timestamp << colreset << ' ' << text << colreset << '\n';
}