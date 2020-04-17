#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;
#include<unordered_set>

struct  Trie{
    int isLeaf ;
    unordered_map<char ,Trie *> children ;
    string word;
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
    curr->word = str;
}

void findaWord( Trie * curr, Trie * temp ,char ch ,int i ,int j, char pattern[4][4],unordered_set<string> &arr){
    while (!curr->isLeaf && temp != curr ){
        temp = curr;
        int x =i , y = j;

        if((x - 1 >= 0 && x - 1 <= 3) && (y - 1 >= 0 && y - 1 <= 3)) if(curr->children[pattern[x - 1][y - 1]])  findaWord(curr->children[pattern[x - 1][y - 1]],temp,pattern[x-1][y-1],x-1,y-1,pattern,arr);
        if((x - 1 >= 0 && x -1 <= 3) && (y >= 0 && y <= 3) ) if(curr->children[pattern[x - 1][y]]) findaWord(curr->children[pattern[x - 1][y ]],temp,pattern[x-1][y],x-1,y,pattern,arr);
        if((x - 1 >= 0 && x -1 <= 3) && (y + 1 >= 0 && y + 1 <= 3 )) if(curr->children[pattern[x - 1][y + 1]])  findaWord(curr->children[pattern[x - 1][y + 1]],temp,pattern[x-1][y+1],x-1,y+1,pattern,arr);
        if((x >= 0 && x <= 3) && (y - 1 >= 0 && y -1  <= 3)) if(curr->children[pattern[x][y - 1]])  findaWord(curr->children[pattern[x][y - 1]],temp,pattern[x][y+1],x,y-1,pattern,arr);
        if((x + 1 >= 0 && x + 1 <= 3 ) && (y -1 >= 0 && y -1 <= 3 )) if(curr->children[pattern[x + 1][y - 1]])  findaWord(curr->children[pattern[x + 1][y - 1]],temp,pattern[x+1][y-1],x+1,y-1,pattern,arr);
        if((x + 1 >= 0 && x + 1 <= 3) &&( y >= 0 && y <= 3)) if(curr->children[pattern[x + 1][y]]) findaWord(curr->children[pattern[x + 1][y]],temp,pattern[x+1][y],x+1,y,pattern,arr);
        if((x >= 0 && x <= 3) && (y + 1 >= 0 && y + 1 <= 3)) if(curr->children[pattern[x][y + 1]]) findaWord(curr->children[pattern[x][y + 1]],temp,pattern[x][y+1],x,y+1,pattern,arr);
        if((x +1 >= 0 && x + 1 <= 3) && (y + 1>= 0 && y + 1 <= 3)) if(curr->children[pattern[x + 1][y + 1]]) findaWord(curr->children[pattern[x + 1][y + 1]],temp,pattern[x+1][y+1],x+1,y+1,pattern,arr);


    }

    if(curr->isLeaf) {
        if(arr.find(curr->word) == arr.end())cout << curr->word<<"\n";
        arr.insert(curr->word);
    }
}

void findAllWords(vector<string> const &dictionary,char pattern[4][4])
{
    unordered_set<string> arr;
    Trie* head = nullptr;
    for (string s: dictionary) {
        insert(head, s);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(head->children[pattern[i][j]] ){
                string str;
                Trie * temp = NULL;
                Trie * curr = head->children[pattern[i][j]];
                findaWord(curr,temp,pattern[i][j],i,j,pattern,arr);
            }
        }
    }

}

int main()
{
    vector<string> dictionary{ "START", "NOTE", "SAND", "STONED" };
    char pattern[4][4] ={{'M', 'S', 'E', 'F'},
    {'R', 'A', 'T', 'D'},
    {'L', 'O', 'N', 'E'},
    {'K', 'A', 'F', 'B'}};
    findAllWords(dictionary,pattern);
    return 0;
}