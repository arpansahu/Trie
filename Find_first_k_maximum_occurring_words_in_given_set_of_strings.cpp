#include <iostream>
#include "unordered_map"
#include "string"
#include "queue"
#include "vector"
using namespace std;

struct  Trie{
    string isLeaf ;
    int count ;
    unordered_map<char,Trie *> children ;
};

struct Node
{
    string key;
    int count;
};

struct comp
{
    bool operator()(const Node lhs, const Node rhs) const
    {
        return lhs.count < rhs.count;
    }
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

void  preOrderTraversalOfTrie(Trie * const curr,priority_queue<Node,vector<Node>,comp> &pq){
    if (curr == nullptr) return ;

    for(auto i : curr->children){
        if(i.second->count) pq.push({i.second->isLeaf,i.second->count});
        preOrderTraversalOfTrie(i.second,pq);
    }
}

void findKfrequentWords(string keys[], int n, int k){
    Trie * head = getNewTrieNode();
    for(int i = 0;i < n ; i++) insert(head,keys[i]);

    priority_queue<Node,vector<Node>,comp> pq;

    preOrderTraversalOfTrie(head,pq);

    while (k-- && !pq.empty()){
        cout <<pq.top().count<<" "<<pq.top().key<<"\n";
        pq.pop();
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

    int k = 4;

    findKfrequentWords(keys,sizeof(keys)/ sizeof(keys[0]),k);



    return 0;
}