#pragma once

#include <unordered_map>
#include <string>
#include "OriginServer.h"
#include "../cache/LRUCache.h"
#include "../logger/Logger.h"
#include <queue>


class EdgeServer
{
private:
    bool isAlive;
    Logger* logger;
    std::string serverName;

    LRUCache cache;

    OriginServer* origin;

    int cacheHits;
    int cacheMisses;
    std::queue<std::string> activeRequests;

public:

    EdgeServer(std::string name, OriginServer* origin, int cacheSize, Logger* logger);

    File requestFile(const std::string& filename);

    void displayCache() const;

    void displayStats() const;

    void setServerStatus(bool status);

    bool getServerStatus() const;
    string getServerName() const;
    void displayStatus() const;

    void addRequest(const std::string& filename);

    void completeRequest();

    int getCurrentLoad() const;

};