#pragma once

#include <unordered_map>
#include <string>
#include "OriginServer.h"
#include "../cache/LRUCache.h"
#include "../logger/Logger.h"

class EdgeServer
{
private:
    Logger* logger;
    std::string serverName;

    LRUCache cache;

    OriginServer* origin;

    int cacheHits;
    int cacheMisses;

public:

    EdgeServer(std::string name, OriginServer* origin, int cacheSize, Logger* logger);

    File requestFile(const std::string& filename);

    void displayCache() const;

    void displayStats() const;
};