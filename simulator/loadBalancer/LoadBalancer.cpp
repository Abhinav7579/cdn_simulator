#include "LoadBalancer.h"
#include <iostream>

using namespace std;

LoadBalancer::LoadBalancer()
{
    currentServer = 0;
}
void LoadBalancer::addServer(EdgeServer* server)
{
    servers.push_back(server);
}

EdgeServer* LoadBalancer::getNextServer()
{
    if(servers.empty())
        return nullptr;
    
 
    EdgeServer* server = servers[currentServer];
    currentServer = (currentServer + 1) % servers.size();
    return server;
}
File LoadBalancer::requestFile(const string& filename)
{
    EdgeServer* server = getNextServer();

    if(server == nullptr)
        throw runtime_error("No Edge Servers Available");

    return server->requestFile(filename);
}

void LoadBalancer::displayServers() const
{
    cout << "\nTotal Edge Servers : "
         << servers.size()
         << endl;
}
