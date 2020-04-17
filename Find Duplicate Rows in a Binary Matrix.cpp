#include <iostream>
#include "vector"
#include "unordered_map"
using namespace std;

struct Trie
{
    bool isLeaf;
    unordered_map<bool , Trie *> children;
};

Trie* getNewTrieNode()
{
    Trie* node = new Trie;
    node->isLeaf = false;
    return node;
}

bool insert(Trie*& head, bool* arr)
{
    Trie* curr = head;
    for (int i = 0; i < 5; i++)
    {
        if (curr->children.find(arr[i]) == curr->children.end())     curr->children[arr[i]] = getNewTrieNode();
        curr = curr->children[arr[i]];
    }

    if (curr->isLeaf) {
        return false;
    }

    return curr->isLeaf = true;
}

int main()
{
    // given set of keys
    bool keys[5][5] =
            {{1, 0, 0, 1, 0},
             {0, 1, 1, 0, 0},
             {1, 0, 0, 1, 0},
             {0, 0, 1, 1, 0},
             {0, 1, 1, 0, 0}};

    Trie * head = getNewTrieNode();
    for (int i = 0; i < 5; ++i) {
        if(!insert(head,keys[i])) cout << "Duplicate row found: Row #" << i + 1 << '\n';
    }

    return 0;
}