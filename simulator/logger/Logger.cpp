#include "Logger.h"
#include <iostream>

using namespace std;

void Logger::addLog(const LogEntry& log)
{
    

    logs.push_back(log);
}

void Logger::displayLogs() const
{
   
    cout << "\n================ Request Logs ================\n";

    for(const auto& log : logs)
    {
        cout << "Time: " << log.timestamp << endl;
        cout << "File: " << log.filename << endl;
        cout << "Server: " << log.serverName << endl;
        cout << "Cache: " << (log.cacheHit ? "Hit" : "Miss") << endl;
        cout << "Response Time: " << log.responseTime << " ms" << endl;
        cout << "----------------------------------------\n";
    }
}

void Logger::clearLogs()
{
    logs.clear();
}

int Logger::totalLogs() const
{
    return logs.size();
}

const std::vector<LogEntry>& Logger::getLogs() const
{
    return logs;
}