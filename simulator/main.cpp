#include <iostream>

#include "server/OriginServer.h"
#include "server/EdgeServer.h"
#include "loadBalancer/LoadBalancer.h"
#include "analytics/Analytics.h"
#include "client/RequestGenerator.h"
#include "logger/Logger.h"
using namespace std;

int main()
{
    //==========================
    //Create Origin Server
    //==========================

    OriginServer origin;

    origin.addFile(File("A", 10, "Image"));
    origin.addFile(File("B", 20, "Image"));
    origin.addFile(File("C", 30, "Image"));
    origin.addFile(File("D", 40, "Image"));
    origin.addFile(File("E", 50, "Image"));

    cout << "=========== Origin Server ===========" << endl;
    origin.displayFiles();

    // ==========================
    // Create Edge Servers
    // ==========================
    Logger logger;

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

    cout << "\n=========== Sending Requests ===========" << endl;
    
   RequestGenerator generator;
   int totalRequests = 100;

   vector<Request> requests = generator.generateRequests(totalRequests);

   for(const auto& request : requests)
    {
     lb.requestFile(
        request.filename,
        request.state
     );
    }

    // ==========================
    // Display Cache
    // ==========================

    cout << "\n=========== Delhi Cache ===========" << endl;
    delhi.displayCache();

    cout << "\n=========== kokata Cache ===========" << endl;
    kolkata.displayCache();

    cout << "\n=========== Chennai Cache ===========" << endl;
    chennai.displayCache();

    // ==========================
    // Display Statistics
    // ==========================

    cout << "\n=========== Statistics ===========" << endl;

    delhi.displayStats();
    kolkata.displayStats();
    chennai.displayStats();

    cout << "\n=========== Request Logs ===========" << endl;

    logger.displayLogs();

    Analytics analytics(&logger);

   analytics.totalRequests();
   analytics.cacheHitRatio();
   analytics.averageResponseTime();
   analytics.mostRequestedFile();
   analytics.requestsPerServer();

    return 0;

    
}