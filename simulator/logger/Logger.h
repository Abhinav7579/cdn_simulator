#pragma once

#include <vector>
#include "../models/LogEntry.h"


class Logger
{
private:

    std::vector<LogEntry> logs;
    

public:

    void addLog(const LogEntry& log);

    void displayLogs() const;

    void clearLogs();

    int totalLogs() const;
    const std::vector<LogEntry>& getLogs() const;
};