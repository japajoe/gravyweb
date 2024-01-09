#include "Console.hpp"
#include "DateTime.hpp"
#include <map>

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
#ifdef _WIN32
    std::cout << text << '\n';
#else
    InitializeConsoleColors();
    std::string &col = consoleColorMap[color];
    std::string &colreset = consoleColorMap[ConsoleColor::Reset];
    std::cout << col << text << colreset << '\n';
#endif
}

void Console::Write(const std::string &text, ConsoleColor color)
{
#ifdef _WIN32
    std::cout << text;
#else
    InitializeConsoleColors();
    std::string &col = consoleColorMap[color];
    std::string &colreset = consoleColorMap[ConsoleColor::Reset];
    std::cout << col << text << colreset;
#endif
}

void Console::WriteLog(const std::string &text)
{
    std::string timestamp = DateTime::Now().FormattedTimestamp();
#ifdef _WIN32
    std::cout << timestamp << ' ' << text << '\n';
#else
    InitializeConsoleColors();    
    std::string &colTime = consoleColorMap[ConsoleColor::Green];
    std::string &colreset = consoleColorMap[ConsoleColor::Reset];
    std::cout << colTime << timestamp << colreset << ' ' << text << colreset << '\n';
#endif
}