#include "LoadBalancer.h"
#include <iostream>

using namespace std;

LoadBalancer::LoadBalancer()
{
    currentServer = 0;
    strategy = ROUND_ROBIN;
}
void LoadBalancer::setRoutingStrategy(RoutingStrategy strategy)
{
    this->strategy = strategy;
}


void LoadBalancer::addServer(EdgeServer* server)
{
    servers.push_back(server);
}

EdgeServer* LoadBalancer::getNextServer()
{
    if (servers.empty())
        return nullptr;

    int checked = 0;

    while (checked < servers.size())
    {
        EdgeServer* server = servers[currentServer];

        currentServer = (currentServer + 1) % servers.size();

        if (server->getServerStatus())
            return server;

        checked++;
    }

    return nullptr;   // all servers are down
}
File LoadBalancer::requestFile(const string& filename)
{
    EdgeServer* server = getNextServer();

    if(server == nullptr)
        throw runtime_error("No Edge Servers Available");

    return server->requestFile(filename);
}

void LoadBalancer::initializeGeoMap()
{
    if(servers.size() < 3)
        return;

    // Delhi Edge
    geoMap["Delhi"] = servers[0];
    geoMap["Punjab"] = servers[0];
    geoMap["Haryana"] = servers[0];
    geoMap["Uttar Pradesh"] = servers[0];
    geoMap["Rajasthan"] = servers[0];
    geoMap["Uttarakhand"] = servers[0];
    geoMap["Himachal Pradesh"] = servers[0];

    // Chennai Edge
    geoMap["Tamil Nadu"] = servers[1];
    geoMap["Kerala"] = servers[1];
    geoMap["Karnataka"] = servers[1];
    geoMap["Andhra Pradesh"] = servers[1];
    geoMap["Telangana"] = servers[1];

    // Kolkata Edge
    geoMap["West Bengal"] = servers[2];
    geoMap["Odisha"] = servers[2];
    geoMap["Jharkhand"] = servers[2];
    geoMap["Bihar"] = servers[2];
    geoMap["Chhattisgarh"] = servers[2];
    geoMap["Assam"] = servers[2];
    geoMap["Sikkim"] = servers[2];
}

File LoadBalancer::requestFile(const string& filename,
                               const string& state)
{
    if(strategy == ROUND_ROBIN)
    {
        return requestFile(filename);
    }

    auto it = geoMap.find(state);

    if(it != geoMap.end())
    {
        cout << "\nGeo Routing : "
             << state
             << " -> Edge Server\n";

        EdgeServer* server = it->second;
        if(server->getServerStatus())
        {
            return server->requestFile(filename);
        }
        cout << server->getServerName()
        << " is DOWN.\n";
        cout << "Trying backup server...\n";
        EdgeServer* backup = getNextServer();
        if(backup == nullptr)
        {
            throw runtime_error("All edge servers are down.");
        }
        cout<<"redirecting to "<<backup->getServerName()<<endl;
        return backup->requestFile(filename);


    }

    cout << "\nState not found. Using Round Robin.\n";

    return requestFile(filename);
}

void LoadBalancer::displayServers() const
{
    cout << "\nTotal Edge Servers : "
         << servers.size()
         << endl;
}

const vector<EdgeServer*>& LoadBalancer::getServers() const
{
    return servers;
}

RoutingStrategy LoadBalancer::getRoutingStrategy() const
{
    return strategy;
}

const unordered_map<string, EdgeServer*>&
LoadBalancer::getGeoMap() const
{
    return geoMap;
}