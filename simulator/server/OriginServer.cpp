#include "OriginServer.h"
#include <iostream>

using namespace std;

void OriginServer::addFile(const File& file)
{
    files[file.name] = file;
}

void OriginServer::removeFile(const string& filename)
{
    files.erase(filename);
}

bool OriginServer::hasFile(const string& filename) const
{
    return files.find(filename) != files.end();
}

File OriginServer::getFile(const string& filename) const
{
    auto it = files.find(filename);

    if(it != files.end())
        return it->second;

    throw runtime_error("File not found");
}

void OriginServer::displayFiles() const
{
    cout << "\nOrigin Server Files\n";

    for(auto &x : files)
    {
        cout << x.second.name
             << " "
             << x.second.size << "KB "
             << x.second.type << endl;
    }
}