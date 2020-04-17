#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;


struct TrieNode
{
    unordered_map<char, TrieNode*> map;
    bool isLeaf = false;
    unordered_set<string> word;
};

void insert(TrieNode*& head, string word)
{
    if (head == nullptr) {
        head = new TrieNode();
    }

    TrieNode* curr = head;
    for (char c: word)
    {
        if (isupper(c))
        {
            if (curr->map.find(c) == curr->map.end())   curr->map[c] = new TrieNode();
            curr = curr->map[c];
        }
    }

    curr->isLeaf = true;
    (curr->word).insert(word);
}

void printAllWords(TrieNode* root)
{
    if (root->isLeaf)
    {
        unordered_set<string> collection = root->word;
        for (string s: collection)  cout << s << endl;
    }
    for (auto pair: root->map)
    {
        TrieNode* child = pair.second;
        if (child)  printAllWords(child);
    }
}

void findAllWords(vector<string> const &dictionary,string pattern)
{

    TrieNode* head = nullptr;
    for (string s: dictionary) {
        insert(head, s);
    }
    TrieNode* curr = head;
    for (char c: pattern) {
        curr = curr->map[c];
        if (curr == nullptr)return;
    }
    printAllWords(curr);
}

int main()
{
    vector<string> dictionary {
            "Hi", "HiTech", "HiTechCity", "Techie", "TechieDelight",
            "Hello", "HelloWorld", "HiTechLab"
    };

    string pattern = "HT";
    findAllWords(dictionary, pattern);
    return 0;
}