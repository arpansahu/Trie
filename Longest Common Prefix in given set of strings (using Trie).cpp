#include <iostream>
#include  <unordered_map>
#include "vector"
using namespace std;

struct Trie{
    int isLeaf ;
    unordered_map<char, Trie *> children;
};

Trie * getNewTrieNode(){
    Trie *  Node = new Trie();
    Node->isLeaf = 0;
    return Node;
}

void insert(Trie * head , string  str){
    Trie * curr = head;
    for(int i = 0;i< str.length() ; i++){
        if(curr->children.find(str[i]) == curr->children.end()) curr->children[str[i]] = getNewTrieNode();
        curr = curr->children[str[i]];

    }
}

string findLCP(string * key,int n ){
    Trie * head  =  getNewTrieNode();

    for (int i = 0; i < n; ++i) {
        insert(head,key[i]);
    }
    string lowest_common_prefix ;

    Trie  * curr = head;
    while(curr && (curr->isLeaf == 0) && (curr->children.size() == 1)){
        auto it = curr->children.begin();
        lowest_common_prefix += it->first;
        curr = it->second;
    }
    return lowest_common_prefix;

}
int main()
{
    // given set of keys
    string keys[21] =
            {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
             "codeless", "codependence", "codependency", "codependent",
             "codependents", "codes", "codesign", "codesigned", "codeveloped",
             "codeveloper", "codex", "codify", "codiscovered", "codrive"};



    cout << "Longest Common Prefix is " << findLCP(keys, sizeof(keys)/sizeof(keys[0]));

    return 0;
}