#include <iostream>

#include "utils/SimulationExporter.h"
#include "server/OriginServer.h"
#include "server/EdgeServer.h"
#include "loadBalancer/LoadBalancer.h"
#include "analytics/Analytics.h"
#include "client/RequestGenerator.h"
#include "logger/Logger.h"

using namespace std;

int main(int argc, char* argv[])
{
    bool jsonMode = false;

    if(argc > 1)
    {
        if(string(argv[1]) == "--json")
        {
            jsonMode = true;
        }
    }

    // ==========================
    // Create Origin Server
    // ==========================

    OriginServer origin;

    origin.addFile(File("A", 10, "Image"));
    origin.addFile(File("B", 20, "Image"));
    origin.addFile(File("C", 30, "Image"));
    origin.addFile(File("D", 40, "Image"));
    origin.addFile(File("E", 50, "Image"));

    // ==========================
    // Create Logger
    // ==========================

    Logger logger;

    // ==========================
    // Create Edge Servers
    // ==========================

    EdgeServer delhi("Delhi Edge", &origin, 3, &logger);
    EdgeServer chennai("Chennai Edge", &origin, 3, &logger);
    EdgeServer kolkata("Kolkata Edge", &origin, 3, &logger);

    // ==========================
    // Create Load Balancer
    // ==========================

    LoadBalancer lb;

    lb.addServer(&delhi);
    lb.addServer(&chennai);
    lb.addServer(&kolkata);

    lb.initializeGeoMap();

    lb.setRoutingStrategy(GEO_ROUTING);

    // ==========================
    // Display Initial State
    // ==========================

    if(!jsonMode)
    {
        cout << "=========== Origin Server ===========" << endl;
        origin.displayFiles();

        cout << "\n=========== Sending Requests ===========" << endl;
    }

    // ==========================
    // Generate Requests
    // ==========================

    RequestGenerator generator;

    int totalRequests = 10;

    vector<Request> requests =
        generator.generateRequests(totalRequests);

    for(const auto& request : requests)
    {
        lb.requestFile(
            request.filename,
            request.state
        );
    }

    // ==========================
    // Console Output
    // ==========================

    if(!jsonMode)
    {
        cout << "\n=========== Delhi Cache ===========" << endl;
        delhi.displayCache();

        cout << "\n=========== Kolkata Cache ===========" << endl;
        kolkata.displayCache();

        cout << "\n=========== Chennai Cache ===========" << endl;
        chennai.displayCache();

        cout << "\n=========== Statistics ===========" << endl;

        delhi.displayStats();
        kolkata.displayStats();
        chennai.displayStats();

        cout << "\n=========== Request Logs ===========" << endl;

        logger.displayLogs();
    }

    // ==========================
    // Analytics
    // ==========================

    Analytics analytics(&logger);

    // ==========================
    // Export
    // ==========================

    if(jsonMode)
    {
        SimulationExporter exporter;

        exporter.exportSimulation(
            origin,
            lb,
            analytics,
            logger
        );
    }
    else
    {
        cout << "\n=========== Analytics ===========" << endl;

        analytics.totalRequests();
        analytics.cacheHitRatio();
        analytics.averageResponseTime();
        analytics.mostRequestedFile();
        analytics.requestsPerServer();
    }

    return 0;
}