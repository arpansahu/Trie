#include <iostream>
#include "unordered_map";
#include "string"
using namespace std;






struct  Trie{
    string isLeaf ;
    unordered_map<char,Trie *> children ;
};

Trie * getNewTrieNode(){
    Trie *  Node = new Trie();
    return Node;
}

void insert(Trie * head , string  str){
    struct Trie * curr = head;
    for (char ch: str)
    {
        if (curr->children.find(ch) == curr->children.end()) curr->children[ch] = new Trie();
        curr = curr->children[ch];
    }
    curr->isLeaf = str;
}

int  preOrderTraversalOfTrie(Trie * const curr,Trie * const root ){
    if (curr == nullptr) return 0;
    for (auto  i = 'a'; i <= 'z'; i++)
    {
        if (curr->children.find(i) != curr->children.end())
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