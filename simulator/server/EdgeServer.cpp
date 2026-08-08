#include "EdgeServer.h"
#include "../config/Config.h"
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
    isAlive = true;
}

File EdgeServer::requestFile(const string& filename)
{
    addRequest(filename);
    if(cache.contains(filename))
    {
        if(Config::verbose){
        cout << "\nCache Hit : " << filename << endl;
        }

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
        completeRequest();
        return cache.get(filename);
    }
    if(Config::verbose){
    cout << "\nCache Miss : " << filename << endl;
    }

    cacheMisses++;
   

    File file = origin->getFile(filename);

    cache.put(file);
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
    if(Config::verbose){
    cout << "Fetched from Origin Server\n";
    cout << "Stored in Cache\n";
    }
    completeRequest();
    return file;
}
void EdgeServer::displayCache() const
{
    if(Config::verbose){
    cout << "\nCache of " << serverName << endl;
    }

    cache.displayCache();
}

void EdgeServer::displayStats() const
{
    if(Config::verbose){
    cout << "\nServer : " << serverName << endl;

    cout << "Cache Hits : " << cacheHits << endl;

    cout << "Cache Misses : " << cacheMisses << endl;

    cout << "Current Load : "
     << getCurrentLoad()
     << endl;
    }
}


void EdgeServer::setServerStatus(bool status)
{
    isAlive = status;
}

bool EdgeServer::getServerStatus() const
{
    return isAlive;
}
string EdgeServer::getServerName() const
{
    return serverName;
}

void EdgeServer::displayStatus() const
{
    if(Config::verbose){
    cout << serverName << " : "
         << (isAlive ? "UP" : "DOWN")
         << endl;
    }
}

void EdgeServer::addRequest(const string& filename)
{
    activeRequests.push(filename);
}

void EdgeServer::completeRequest()
{
    if(!activeRequests.empty())
        activeRequests.pop();
}

int EdgeServer::getCurrentLoad() const
{
    return activeRequests.size();
}

int EdgeServer::getCacheHits() const
{
    return cacheHits;
}

int EdgeServer::getCacheMisses() const
{
    return cacheMisses;
}

const LRUCache& EdgeServer::getCache() const
{
    return cache;
}