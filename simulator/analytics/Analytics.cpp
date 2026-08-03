#include "Analytics.h"
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>
using namespace std;

Analytics::Analytics(Logger* logger)
{
    this->logger = logger;
}

void Analytics::totalRequests() const
{
    cout << "\nTotal Requests : "
         << logger->getLogs().size()
         << endl;
}


void Analytics::cacheHitRatio() const
{
    const auto& logs = logger->getLogs();

    if(logs.empty())
    {
        cout << "No requests found.\n";
        return;
    }

    int hits = 0;

    for(const auto& log : logs)
    {
        if(log.cacheHit)
            hits++;
    }

    double ratio = (double)hits * 100 / logs.size();

    cout << "\nCache Hit Ratio : "
         << fixed << setprecision(2)
         << ratio << "%" << endl;
}

void Analytics::averageResponseTime() const
{
    const auto& logs = logger->getLogs();

    if(logs.empty())
    {
        cout << "No requests found.\n";
        return;
    }

    int totalTime = 0;

    for(const auto& log : logs)
    {
        totalTime += log.responseTime;
    }

    double average = (double)totalTime / logs.size();

    cout << "\nAverage Response Time : "
         << fixed << setprecision(2)
         << average
         << " ms" << endl;
}


void Analytics::mostRequestedFile() const
{
    const auto& logs = logger->getLogs();

    if(logs.empty())
    {
        cout << "No requests found.\n";
        return;
    }

    unordered_map<string, int> frequency;

    for(const auto& log : logs)
    {
        frequency[log.filename]++;
    }

    string mostRequested;
    int maxRequests = 0;

    for(const auto& entry : frequency)
    {
        if(entry.second > maxRequests)
        {
            maxRequests = entry.second;
            mostRequested = entry.first;
        }
    }

    cout << "\nMost Requested File : "
         << mostRequested
         << " (" << maxRequests << " requests)"
         << endl;
}


void Analytics::requestsPerServer() const
{
    const auto& logs = logger->getLogs();

    if(logs.empty())
    {
        cout << "No requests found.\n";
        return;
    }

    unordered_map<string,int> serverRequests;

    for(const auto& log : logs)
    {
        serverRequests[log.serverName]++;
    }

    cout << "\nRequests Per Server\n";
    cout << "-------------------------\n";

    for(const auto& server : serverRequests)
    {
        cout << server.first
             << " : "
             << server.second
             << endl;
    }
}