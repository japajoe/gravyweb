#ifndef STRINGBUILDER_HPP
#define STRINGBUILDER_HPP

#include <string>

class StringBuilder
{
private:
    std::string target;
public:
    StringBuilder()
    {
        target.clear();
    }

    void Append(const std::string &s)
    {
        target.append(s);
    }

    void AppendLine(const std::string &s)
    {
        target.append(s + "\n");
    }

    std::string ToString() const
    {
        return target;
    }
};

#endif