#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;


struct  Trie{
    int isLeaf ;
    unordered_map<char ,Trie *> children ;
};

struct Trie * getNewTrieNode(){
    Trie * Node =  new Trie();
    Node->isLeaf = 0;
    return Node;
}

void insert(struct Trie *& head,string str){
    if(head == NULL) head = getNewTrieNode();
    struct Trie * curr = head;
    for(int i = 0;i < str.length();i++){
        if (curr->children.find(str[i]) == curr->children.end()) curr->children[str[i]] = getNewTrieNode();
        curr = curr->children[str[i]];

    }
    curr->isLeaf = 1;
}



void findAllWords(vector<string> const &dictionary,string pattern)
{

    Trie* head = nullptr;
    for (string s: dictionary) {
        insert(head, s);
    }
    string temp;
    Trie* curr = head;
    int cond = 0;
    for (char c: pattern) {
        curr = curr->children[c];
        if (curr == nullptr) curr = head->children[c];
        temp = temp + c;

        if(curr->isLeaf)  {temp = temp + " "; cond++;}
    }
    cout  <<  temp;
    if(cond) cout <<"\nString can be segmented ";
}

int main()
{
    vector<string> dictionary{ "this", "th", "is", "famous", "Word", "break", "b",
                               "r", "e", "a", "k", "br", "bre", "brea", "ak", "problem" };
    string pattern = "Wordbreakproblem";
    findAllWords(dictionary,pattern);
    return 0;
}