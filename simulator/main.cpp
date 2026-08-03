#include <iostream>

#include "server/OriginServer.h"
#include "server/EdgeServer.h"
#include "loadBalancer/LoadBalancer.h"

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

    EdgeServer delhi("Delhi", &origin, 3,&logger);
    EdgeServer mumbai("Mumbai", &origin, 3,&logger);
    EdgeServer chennai("Chennai", &origin, 3,&logger);

    // ==========================
    // Create Load Balancer
    // ==========================

    LoadBalancer lb;

    lb.addServer(&delhi);
    lb.addServer(&mumbai);
    lb.addServer(&chennai);

    cout << "\n=========== Sending Requests ===========" << endl;

    lb.requestFile("A");
    lb.requestFile("B");
    lb.requestFile("C");
    lb.requestFile("A");
    lb.requestFile("D");
    lb.requestFile("A");
    lb.requestFile("E");
    lb.requestFile("B");
    lb.requestFile("C");

    // ==========================
    // Display Cache
    // ==========================

    cout << "\n=========== Delhi Cache ===========" << endl;
    delhi.displayCache();

    cout << "\n=========== Mumbai Cache ===========" << endl;
    mumbai.displayCache();

    cout << "\n=========== Chennai Cache ===========" << endl;
    chennai.displayCache();

    // ==========================
    // Display Statistics
    // ==========================

    cout << "\n=========== Statistics ===========" << endl;

    delhi.displayStats();
    mumbai.displayStats();
    chennai.displayStats();

    cout << "\n=========== Request Logs ===========" << endl;

    logger.displayLogs();

    return 0;
    
}