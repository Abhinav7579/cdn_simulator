#include "SimulationExporter.h"

#include <iostream>

using namespace std;

void SimulationExporter::exportSimulation(
    const OriginServer& origin,
    const LoadBalancer& lb,
    const Analytics& analytics,
    const Logger& logger
) const
{
    cout << "{\n";

    exportOrigin(origin);
    cout << ",\n";

    exportLoadBalancer(lb);
    cout << ",\n";

    exportServers(lb);
    cout << ",\n";

    exportAnalytics(analytics);
    cout << ",\n";

    exportLogs(logger);

    cout << "\n}\n";
}

void SimulationExporter::exportOrigin(
    const OriginServer& origin
) const
{
    cout << "  \"origin\": {\n";
    cout << "    \"files\": [\n";

    const auto& files = origin.getFiles();

    int count = 0;

    for (const auto& file : files)
    {
        cout << "      {\n";

        cout << "        \"name\": \""
             << file.second.name
             << "\",\n";

        cout << "        \"size\": "
             << file.second.size
             << ",\n";

        cout << "        \"type\": \""
             << file.second.type
             << "\"\n";

        cout << "      }";

        count++;

        if (count != files.size())
            cout << ",";

        cout << "\n";
    }

    cout << "    ]\n";
    cout << "  }";
}

void SimulationExporter::exportLoadBalancer(
    const LoadBalancer& lb
) const
{
    cout << "  \"loadBalancer\": {\n";

    cout << "    \"strategy\": \"";

    switch (lb.getRoutingStrategy())
    {
        case ROUND_ROBIN:
            cout << "ROUND_ROBIN";
            break;

        case GEO_ROUTING:
            cout << "GEO_ROUTING";
            break;
    }

    cout << "\"\n";

    cout << "  }";
}

void SimulationExporter::exportServers(
    const LoadBalancer& lb
) const
{
    cout << "  \"servers\": [\n";

    const auto& servers = lb.getServers();

    for (int i = 0; i < servers.size(); i++)
    {
        EdgeServer* server = servers[i];

        cout << "    {\n";

        cout << "      \"name\": \""
             << server->getServerName()
             << "\",\n";

        cout << "      \"status\": "
             << (server->getServerStatus() ? "true" : "false")
             << ",\n";

        cout << "      \"cacheHits\": "
             << server->getCacheHits()
             << ",\n";

        cout << "      \"cacheMisses\": "
             << server->getCacheMisses()
             << ",\n";

        cout << "      \"currentLoad\": "
             << server->getCurrentLoad()
             << "\n";

        cout << "    }";

        if (i != servers.size() - 1)
            cout << ",";

        cout << "\n";
    }

    cout << "  ]";
}

void SimulationExporter::exportAnalytics(
    const Analytics& analytics
) const
{
    cout << "  \"analytics\": {\n";

    cout << "    \"totalRequests\": "
         << analytics.getTotalRequests()
         << ",\n";

    cout << "    \"cacheHitRatio\": "
         << analytics.getCacheHitRatio()
         << ",\n";

    cout << "    \"averageResponseTime\": "
         << analytics.getAverageResponseTime()
         << ",\n";

    cout << "    \"mostRequestedFile\": \""
         << analytics.getMostRequestedFile()
         << "\"\n";

    cout << "  }";
}

void SimulationExporter::exportLogs(
    const Logger& logger
) const
{
    cout << "  \"logs\": [\n";

    const auto& logs = logger.getLogs();

    for (int i = 0; i < logs.size(); i++)
    {
        const auto& log = logs[i];

        cout << "    {\n";

        cout << "      \"filename\": \""
             << log.filename
             << "\",\n";

        cout << "      \"server\": \""
             << log.serverName
             << "\",\n";

        cout << "      \"cacheHit\": "
             << (log.cacheHit ? "true" : "false")
             << ",\n";

        cout << "      \"originAccessed\": "
             << (log.originAccessed ? "true" : "false")
             << ",\n";

        cout << "      \"responseTime\": "
             << log.responseTime
             << ",\n";

        cout << "      \"timestamp\": \""
             << log.timestamp
             << "\"\n";

        cout << "    }";

        if (i != logs.size() - 1)
            cout << ",";

        cout << "\n";
    }

    cout << "  ]";
}