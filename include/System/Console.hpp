#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>

enum class ConsoleColor
{
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Reset
};

class Console
{
public:
    static void WriteLine(const std::string &text, ConsoleColor color = ConsoleColor::White);
    static void Write(const std::string &text, ConsoleColor color = ConsoleColor::White);
    static void WriteLog(const std::string &text);
};

#endif