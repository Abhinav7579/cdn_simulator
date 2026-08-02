#pragma once
#include <unordered_map>
#include <string>
#include "../server/File.h"

using namespace std;

class LRUCache
{
public:

    class Node
    {
    public:
        string filename;
        File file;

        Node* next;
        Node* prev;

        Node(string filename_, File file_);
    };

private:

    Node* head;
    Node* tail;

    unordered_map<string, Node*> mp;

    int cap;

    void deleteNode(Node* node);
    void insertAfterHead(Node* node);

public:

    LRUCache(int capacity);

    bool contains(const string& filename);

    File get(const string& filename);

    void put(const File& file);

    void displayCache() const;
};