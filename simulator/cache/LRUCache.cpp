#include "LRUCache.h"
#include <iostream>

using namespace std;

LRUCache::Node::Node(string filename_, File file_)
{
    filename = filename_;
    file = file_;

    next = nullptr;
    prev = nullptr;
}

LRUCache::LRUCache(int capacity)
{
    cap = capacity;

    head = new Node("", File());
    tail = new Node("", File());

    head->next = tail;
    tail->prev = head;
}

void LRUCache::deleteNode(Node* node)
{
    Node* pre = node->prev;
    Node* after = node->next;

    pre->next = after;
    after->prev = pre;
}

void LRUCache::insertAfterHead(Node* node)
{
    Node* temp = head->next;

    node->next = temp;
    node->prev = head;

    head->next = node;
    temp->prev = node;
}

bool LRUCache::contains(const string& filename)
{
    return mp.find(filename) != mp.end();
}

File LRUCache::get(const string& filename)
{
    if (!contains(filename))
        throw runtime_error("File not found in cache");

    Node* node = mp[filename];

    deleteNode(node);
    insertAfterHead(node);

    return node->file;
}

void LRUCache::put(const File& file)
{
    string filename = file.name;

    if (contains(filename))
    {
        Node* node = mp[filename];

        node->file = file;

        deleteNode(node);
        insertAfterHead(node);
    }
    else
    {
        if (mp.size() == cap)
        {
            Node* node = tail->prev;

            mp.erase(node->filename);

            deleteNode(node);

            delete node;
        }

        Node* node = new Node(filename, file);

        mp[filename] = node;

        insertAfterHead(node);
    }
}

void LRUCache::displayCache() const
{
    cout << "\nCurrent Cache\n\n";

    Node* cur = head->next;

    while (cur != tail)
    {
        cout << cur->filename << endl;
        cur = cur->next;
    }
}