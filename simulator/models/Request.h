#pragma once

#include <string>

using namespace std;

class Request
{
public:

    string filename;

    string state;

    Request() {}

    Request(string filename,
            string state)
    {
        this->filename = filename;
        this->state = state;
    }
};