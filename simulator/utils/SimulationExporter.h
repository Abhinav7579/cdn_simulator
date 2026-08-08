#pragma once

#include "../server/OriginServer.h"
#include "../loadBalancer/LoadBalancer.h"
#include "../analytics/Analytics.h"
#include "../logger/Logger.h"

class SimulationExporter
{
private:

    void exportOrigin(
        const OriginServer& origin
    ) const;

    void exportLoadBalancer(
        const LoadBalancer& lb
    ) const;

    void exportServers(
        const LoadBalancer& lb
    ) const;

    void exportAnalytics(
        const Analytics& analytics
    ) const;

    void exportLogs(
        const Logger& logger
    ) const;

public:

    void exportSimulation(
        const OriginServer& origin,
        const LoadBalancer& lb,
        const Analytics& analytics,
        const Logger& logger
    ) const;
};