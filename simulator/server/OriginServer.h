#pragma once

#include <unordered_map>
#include <string>
#include "File.h"

class OriginServer
{
private:

    std::unordered_map<std::string, File> files;

public:

    void addFile(const File& file);

    void removeFile(const std::string& filename);

    bool hasFile(const std::string& filename) const;

    File getFile(const std::string& filename) const;

    void displayFiles() const;
};