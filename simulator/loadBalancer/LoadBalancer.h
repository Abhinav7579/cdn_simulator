#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "../server/EdgeServer.h"

using namespace std;
enum RoutingStrategy
{
    ROUND_ROBIN,
    GEO_ROUTING
};
class LoadBalancer
{
private:

    vector<EdgeServer*> servers;
    unordered_map<string, EdgeServer*> geoMap;
    RoutingStrategy strategy;

    int currentServer;

public:

    LoadBalancer();

    void addServer(EdgeServer* server);

    EdgeServer* getNextServer();

    void setRoutingStrategy(RoutingStrategy strategy);
    void initializeGeoMap();

    File requestFile(const string& filename);
    File requestFile(const string& filename,
                     const string& state);

    void displayServers() const;
};