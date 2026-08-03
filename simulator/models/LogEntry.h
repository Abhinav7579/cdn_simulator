#pragma once

#include <string>

using namespace std;

class LogEntry
{
public:

    string filename;

    string serverName;

    bool cacheHit;

    bool originAccessed;

    int responseTime;

    string timestamp;

    LogEntry() {}

    LogEntry(
        string filename,
        string serverName,
        bool cacheHit,
        bool originAccessed,
        int responseTime,
        string timestamp)
    {
        this->filename = filename;
        this->serverName = serverName;
        this->cacheHit = cacheHit;
        this->originAccessed = originAccessed;
        this->responseTime = responseTime;
        this->timestamp = timestamp;
    }
};