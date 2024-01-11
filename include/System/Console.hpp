#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <functional>

using LogFunction = std::function<void(const std::string&)>;

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
private:
    static LogFunction logFunction;
    static LogFunction errorFunction;
public:
    static void WriteLine(const std::string &text, ConsoleColor color = ConsoleColor::White);
    static void Write(const std::string &text, ConsoleColor color = ConsoleColor::White);
    static void WriteLog(const std::string &text);
    static void WriteError(const std::string &text);
    static void SetLogFunction(const LogFunction &logFunction);
    static void SetErrorFunction(const LogFunction &errorFunction);
};

#endif