#include "EdgeServer.h"
#include <iostream>

using namespace std;

EdgeServer::EdgeServer(string name,
                       OriginServer* origin,
                       int cacheSize, Logger* logger)
    : cache(cacheSize)
{
    serverName = name;
    this->origin = origin;
    this->logger = logger;
    cacheHits = 0;
    cacheMisses = 0;
}

File EdgeServer::requestFile(const string& filename)
{
    if(cache.contains(filename))
    {
        cout << "\nCache Hit : " << filename << endl;

        cacheHits++;

        
        logger->addLog(
    LogEntry(
        filename,
        serverName,
        true,
        false,
        20,
        "10:30:15"
    )
);
        return cache.get(filename);
    }

    cout << "\nCache Miss : " << filename << endl;

    cacheMisses++;
    logger->addLog(
    LogEntry(
        filename,
        serverName,
        false,
        true,
        200,
        "10:30:15"
    )
);

    File file = origin->getFile(filename);

    cache.put(file);

    cout << "Fetched from Origin Server\n";
    cout << "Stored in Cache\n";

    return file;
}
void EdgeServer::displayCache() const
{
    cout << "\nCache of " << serverName << endl;

    cache.displayCache();
}

void EdgeServer::displayStats() const
{
    cout << "\nServer : " << serverName << endl;

    cout << "Cache Hits : " << cacheHits << endl;

    cout << "Cache Misses : " << cacheMisses << endl;
}
