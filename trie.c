#include "stdio.h"
#include "stdlib.h"

#define A_LENGTH 256

typedef struct Node{
    struct Node **children;
    int value;
    int is_terminal;
}Trie;

Trie* create(){
    Trie *novo = (Trie *) malloc(sizeof(Trie));
    novo->is_terminal = 0;
    novo->children = (Trie**) malloc(sizeof(Trie*)*A_LENGTH);

    for(int i = 0; i<A_LENGTH; i++)
        novo->children[i] = NULL;

    return novo;
}

Trie *insert(Trie *trie, int value, char *key){
    if(!trie) trie = create();

    if(key[1]=='\0'){
        trie->value = value;
        trie->is_terminal = 1;
    }else{
        int iKey = (int) key[0];
        trie->children[iKey] = insert(trie->children[iKey], value, &(key[1]));
    }

    return trie;
}

Trie* search(Trie *trie, char *key){
    if(!trie) return NULL;

    if(key[1]=='\0'){
        return (trie->is_terminal)? trie : NULL;
    }

    int iKey = (int) key[0];
    return trie->children[iKey] = search(trie->children[iKey], &(key[1]));
}

Trie* remove(Trie *trie, char *key){
    
}

int main(){
    Trie *trie = NULL;

    trie = insert(trie, 2, "ala");

    Trie *searched = search(trie, "a");

    if(searched)
        printf("%d", searched->value);
    else
        printf("nao achou");
    //teste("oloco");

    return 0;
}