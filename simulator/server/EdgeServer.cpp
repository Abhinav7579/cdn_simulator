#include "EdgeServer.h"
#include <iostream>

using namespace std;

EdgeServer::EdgeServer(string name,
                       OriginServer* origin,
                       int cacheSize)
    : cache(cacheSize)
{
    serverName = name;
    this->origin = origin;

    cacheHits = 0;
    cacheMisses = 0;
}

File EdgeServer::requestFile(const string& filename)
{
    if(cache.contains(filename))
    {
        cout << "\nCache Hit : " << filename << endl;

        cacheHits++;

        return cache.get(filename);
    }

    cout << "\nCache Miss : " << filename << endl;

    cacheMisses++;

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
