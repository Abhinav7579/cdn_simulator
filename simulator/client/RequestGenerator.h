#pragma once

#include <vector>

#include "../models/Request.h"

class RequestGenerator
{
private:

    std::vector<std::string> files;

    std::vector<std::string> states;

public:

    RequestGenerator();

    Request generateRequest();

    std::vector<Request> generateRequests(int n);
};