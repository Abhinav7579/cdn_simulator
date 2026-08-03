#pragma once

#include "../logger/Logger.h"

class Analytics
{
private:

    Logger* logger;

public:

    Analytics(Logger* logger);

    void totalRequests() const;

    void cacheHitRatio() const;

    void averageResponseTime() const;

    void mostRequestedFile() const;

    void requestsPerServer() const;
};