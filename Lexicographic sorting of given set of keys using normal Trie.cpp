#include <iostream>

#include "string"
using namespace std;

#define ALPHABET 26




struct  Trie{
    string isLeaf ;
    Trie * children[ALPHABET] ;
};

Trie * getNewTrieNode(){
    Trie *  Node = new Trie();
    for (int i = 0; i < ALPHABET; ++i) {
        Node->children[i] = NULL;
    }
    return Node;
}

void insert(Trie* &head, string const &str)
{
    Trie* curr = head;
    for (char ch: str)
    {
        if (curr->children[ch - 'a'] == nullptr) curr->children[ch - 'a'] = new Trie();
        curr = curr->children[ch - 'a'];
    }

    curr->isLeaf = str;
}

bool preOrderTraversalOfTrie(Trie* const curr, Trie const *root)
{
    if (curr == nullptr) return false;
    for (int i = 0; i < ALPHABET; i++)
    {
        if (curr->children[i] != nullptr)
        {if (curr->children[i]->isLeaf.length() > 0) 
                cout << curr->children[i]->isLeaf << '\n';
        preOrderTraversalOfTrie(curr->children[i], root);
        }
    }
}


int main()
{
    // given set of keys
    string keys[] =
            {"lexicographic", "sorting", "of", "a", "set", "of", "keys", "can",
             "be", "accomplished", "with", "a", "simple", "trie", "based",
             "algorithm", "we", "insert", "all", "keys", "in", "a", "trie",
             "output", "all", "keys", "in", "the", "trie", "by", "means", "of",
             "preorder", "traversal", "which", "results", "in", "output", "that",
             "is", "in", "lexicographically", "increasing", "order", "preorder",
             "traversal", "is", "a", "kind", "of", "depth", "first", "traversal"};
    Trie * head = getNewTrieNode();
    for(auto i : keys) insert(head,i);

    preOrderTraversalOfTrie(head,head);

    return 0;
}