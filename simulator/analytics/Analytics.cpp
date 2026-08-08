#include "Analytics.h"
#include <iostream>
#include <iomanip>
#include "../config/Config.h"
#include <unordered_map>
#include <string>
using namespace std;

Analytics::Analytics(Logger* logger)
{
    this->logger = logger;
}

void Analytics::totalRequests() const
{
    if(Config::verbose){
    cout << "\nTotal Requests : "
         << getTotalRequests()
         << endl;
    }
}


void Analytics::cacheHitRatio() const
{
    if(Config::verbose){
    cout
        << "\nCache Hit Ratio : "
        << fixed
        << setprecision(2)
        << getCacheHitRatio()
        << "%"
        << endl;
    }
}

void Analytics::averageResponseTime() const
{
    if(Config::verbose){
     cout << "\nAverage Response Time : "
         << fixed << setprecision(2)
         << getAverageResponseTime()
         << " ms" << endl;
    }
   
}


void Analytics::mostRequestedFile() const
{
    if(Config::verbose){
   cout << "\nMost Requested File : "
         << getMostRequestedFile()
         << endl;
    }
}


void Analytics::requestsPerServer() const
{
    const auto& logs = logger->getLogs();

    if(logs.empty())
    {
        if(Config::verbose){
        cout << "No requests found.\n";
        }
        return;
    }

    unordered_map<string,int> serverRequests;

    for(const auto& log : logs)
    {
        serverRequests[log.serverName]++;
    }

    if(Config::verbose){
    cout << "\nRequests Per Server\n";
    cout << "-------------------------\n";
    }

    for(const auto& server : serverRequests)
    {
        if(Config::verbose){
        cout << server.first
             << " : "
             << server.second
             << endl;
        }
    }
}

int Analytics::getTotalRequests() const
{
    return logger->getLogs().size();
}

double Analytics::getCacheHitRatio() const
{
    const auto& logs = logger->getLogs();

    if(logs.empty())
        return 0;

    int hits = 0;

    for(const auto& log : logs)
    {
        if(log.cacheHit)
            hits++;
    }

    return (double)hits * 100 / logs.size();
}

double Analytics::getAverageResponseTime() const
{
     const auto& logs = logger->getLogs();

    if(logs.empty())
    {
        return 0;
    }

    int totalTime = 0;

    for(const auto& log : logs)
    {
        totalTime += log.responseTime;
    }

    double average = (double)totalTime / logs.size();

    return average;
}

string Analytics::getMostRequestedFile() const
{
     const auto& logs = logger->getLogs();
    
    if(logs.empty())
    {
        return "";
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
    
    return mostRequested;
    


}