#include <iostream>
#include "unordered_map";
#include "string"
using namespace std;

struct  Trie{
    string isLeaf ;
    int count ;
    unordered_map<char,Trie *> children ;
};

Trie * getNewTrieNode(){
    Trie *  Node = new Trie();
    Node->count = 0;
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
    curr->count += 1;
}

void  preOrderTraversalOfTrie(Trie * const curr,int &max_count ,string & key){
    if (curr == nullptr) return ;

    for(auto i : curr->children){
        if(max_count < i.second->count){
            key = i.second->isLeaf;
            max_count = i.second->count;
        }
        preOrderTraversalOfTrie(i.second,max_count,key);
    }
}
int main()
{
    // given set of keys
    string keys[] =
            {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
             "codeless", "codec", "codecs", "codependence", "codex", "codify",
             "codependents", "codes", "code", "coder", "codesign", "codec",
             "codeveloper", "codrive", "codec", "codecs", "codiscovered"};
    Trie * head = getNewTrieNode();
    for(auto i : keys) insert(head,i);
    int max_count = 0;
    string key ;
    preOrderTraversalOfTrie(head,max_count,key);
    cout << max_count <<" "<<key;
    return 0;
}