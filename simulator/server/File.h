#pragma once
#include <string>

class File
{
public:
    std::string name;
    int size;          // KB
    std::string type;
    File() {}
    File(std::string n, int s, std::string t)
    {
        name = n;
        size = s;
        type = t;
    }
};