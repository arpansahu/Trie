#include <iostream>

using namespace std;
#define  ALPHABETS_SIZE 128

class Trie{

public:
    int isLeaf;
    struct Trie * children [ALPHABETS_SIZE];

    Trie(){
        this->isLeaf = 0;
        for (int i = 0; i < ALPHABETS_SIZE; ++i) {
            this->children[i] = nullptr;
        }
    }
    void insert(string);
    int search(string);
    int deletion(Trie *& ,string);
    int havechildren(Trie const *);
};



void Trie :: insert(string str){
    struct Trie * curr = this;
    for(int i = 0; i< str.length() ; i++){
        if(!curr->children[str[i]]) curr->children[str[i]] = new Trie();
        curr = curr->children[str[i]];
    }
    curr->isLeaf = 1;
}

int Trie :: search(string str){
    if(this == nullptr) return 0;
    struct Trie *  curr = this;
    for (int i = 0; i < str.length(); ++i) {
        curr = curr->children[str[i]];
        if(!curr) return 0;
    }
    return curr->isLeaf;
}

int Trie :: havechildren(Trie const * head){

    for (int i = 0; i < ALPHABETS_SIZE ; ++i) {
        if(head->children[i]) return 1;
    }
    return 0;
}
int Trie :: deletion(struct Trie *& curr,string str){
    if(curr == nullptr) return 1;
    if(str.length()){
        if(curr != nullptr && (curr)->children[str[0]] != NULL && deletion(curr->children[str[0]],str.substr(1)) && curr->isLeaf == 0){
            if(!havechildren(curr)) {
                delete(curr);
                curr = nullptr;
                return 1;
            }else return 0;
        }
    }
    if(str.length() == 0 && curr->isLeaf){
        if(!havechildren(curr)){
            delete(curr);
            curr = nullptr;
            return 1;
        } else{
            curr->isLeaf = 0;
            return 0;
        }
    }

}

int main(){
    Trie* head = new  Trie();

    head->insert( "hello");
    printf("%d ", head->search( "hello"));       // print 1

    head->insert( "helloworld");
    printf("%d ", head->search( "helloworld"));  // print 1

    printf("%d ", head->search( "helll"));       // print 0 (Not present)

    head->insert( "hell");
    printf("%d ", head->search( "hell"));        // print 1

    head->insert( "h");
    printf("%d \n", head->search( "h"));         // print 1 + newline

    head->deletion(head, "hello");
    printf("%d ", head->search("hello"));       // print 0 (hello deleted)
    printf("%d ", head->search( "helloworld"));  // print 1
    printf("%d \n", head->search( "hell"));      // print 1 + newline

    head->deletion(head, "h");
    printf("%d ", head->search( "h"));           // print 0 (h deleted)
    printf("%d ", head->search( "hell"));        // print 1
    printf("%d\n", head->search( "helloworld")); // print 1 + newline

    head->deletion(head, "helloworld");
    printf("%d ", head->search( "helloworld"));  // print 0
    printf("%d ", head->search("hell"));        // print 1

    head->deletion(head, "hell");
    printf("%d\n", head->search( "hell"));       // print 0 + newline

    if (head == NULL)
        printf("Trie empty!!\n");               // Trie is empty now

    printf("%d ", head->search( "hell"));        // print 0

    return 0;
}