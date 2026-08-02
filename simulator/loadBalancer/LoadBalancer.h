#pragma once

#include <vector>
#include <string>

#include "../server/EdgeServer.h"

using namespace std;

class LoadBalancer
{
private:

    vector<EdgeServer*> servers;

    int currentServer;

public:

    LoadBalancer();

    void addServer(EdgeServer* server);

    EdgeServer* getNextServer();

    File requestFile(const string& filename);

    void displayServers() const;
};