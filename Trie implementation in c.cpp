#include <stdio.h>
#include "stdlib.h"

#define MAX_ALPHABETS 26

struct  Trie{
    int isLeaf ;
    struct Trie * children [MAX_ALPHABETS];
};

struct Trie * getNewTrieNode(){
    struct Trie * Node = (struct Trie *) malloc(sizeof(struct Trie));
    Node->isLeaf = 0;
    for (int i = 0; i < MAX_ALPHABETS; ++i) {
        Node->children[i] = NULL;
    }
    return Node;
}

void insert(struct Trie * head,char * str){
    struct Trie * curr = head;
    while(*str){
        if (curr->children[*str - 'a'] == NULL) curr->children[*str - 'a'] = getNewTrieNode();
        curr = curr->children[*str - 'a'];
        str++;
    }
    curr->isLeaf = 1;
}

int search(struct Trie * head,char * str){

    if(head == NULL) return 0;

    struct Trie * curr = head;
    while(*str){
        curr = curr->children[*str - 'a'];
        if(curr == NULL) return 0;
        str++;
    }
    return curr->isLeaf;
}

int havechildren(struct Trie * curr){
    for (int i = 0; i < MAX_ALPHABETS; ++i) {
        if(curr->children[i]) return 1;
    }
    return 0;
}

int deletion(struct Trie ** curr,char * str){
    if(*curr == NULL) return 0;
    if(*str){
        if(curr != NULL && (*curr)->children[*str - 'a'] != NULL && deletion(&((*curr)->children[*str - 'a']),str +1) && (*curr)->isLeaf == 0){
            if(!havechildren(*curr)) {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }else return 0;
        }
    }
    if(*str == '\0' && (*curr)->isLeaf) {
        if(!havechildren(*curr)){
            free(*curr);
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