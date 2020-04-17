#include <iostream>
#include <unordered_map>

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

void insert(struct Trie *& head,char * str){
    if(head == NULL) head = getNewTrieNode();
    struct Trie * curr = head;
    while(*str){
        if (curr->children.find(*str) == curr->children.end()) curr->children[*str] = getNewTrieNode();
        curr = curr->children[*str];
        str++;
    }
    curr->isLeaf = 1;
}

int search(struct Trie * head,char * str){

    if(head == NULL) return 0;

    struct Trie * curr = head;
    while(*str){
        curr = curr->children[*str];
        if(curr == NULL) return 0;
        str++;
    }
    return curr->isLeaf;
}

int havechildren(struct Trie * curr){
    for(auto i : curr->children) if(i.second != NULL) return 1;
    return 0;
}

int deletion(struct Trie ** curr,char * str){
    if(*curr == NULL) return 0;
    if(*str){
        if(curr != NULL && (*curr)->children.find(*str) != (*curr)->children.end() && deletion(&((*curr)->children[*str]),str +1) && (*curr)->isLeaf == 0){
            if(!havechildren(*curr)) {
                delete(*curr);
                (*curr) = NULL;
                return 1;
            }else return 0;
        }
    }
    if(*str == '\0' && (*curr)->isLeaf) {
        if(!havechildren(*curr)){
            delete(*curr);
            (*curr) = NULL;
            return 1;
        }else{
            (*curr)->isLeaf = 0;
            return 0;
        }
    }

}

int main(){
    struct Trie* head = getNewTrieNode();

    insert(head, "hello");
    printf("%d ", search(head, "hello"));       // print 1

    insert(head, "helloworld");
    printf("%d ", search(head, "helloworld"));  // print 1

    printf("%d ", search(head, "helll"));       // print 0 (Not present)

    insert(head, "hell");
    printf("%d ", search(head, "hell"));        // print 1

    insert(head, "h");
    printf("%d \n", search(head, "h"));         // print 1 + newline

    deletion(&head, "hello");
    printf("%d ", search(head, "hello"));       // print 0 (hello deleted)
    printf("%d ", search(head, "helloworld"));  // print 1
    printf("%d \n", search(head, "hell"));      // print 1 + newline

    deletion(&head, "h");
    printf("%d ", search(head, "h"));           // print 0 (h deleted)
    printf("%d ", search(head, "hell"));        // print 1
    printf("%d\n", search(head, "helloworld")); // print 1 + newline

    deletion(&head, "helloworld");
    printf("%d ", search(head, "helloworld"));  // print 0
    printf("%d ", search(head, "hell"));        // print 1

    deletion(&head, "hell");
    printf("%d\n", search(head, "hell"));       // print 0 + newline

    if (head == NULL)
        printf("Trie empty!!\n");               // Trie is empty now

    printf("%d ", search(head, "hell"));        // print 0

    return 0;
}