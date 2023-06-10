#include "trie.h"
#include "string.h"

#define A_LENGTH 128

typedef struct Node{
    struct Node **children;
    int value;
    int is_terminal;
}Trie;

Trie *root = NULL;

Trie* create(){
    Trie *new = (Trie *) malloc(sizeof(Trie));
    new->is_terminal = 0;
    new->children = (Trie**) malloc(sizeof(Trie*)*A_LENGTH);

    for(int i = 0; i<A_LENGTH; i++)
        new->children[i] = NULL;

    return new;
}

Trie *insert(Trie *trie, int value, char *key){
    if(key[0] == '\0') return trie;

    if(!trie) trie = create();

    int iKey = (int) key[0];

    if(key[1]=='\0'){
        if(!trie->children[iKey])
            trie->children[iKey] = create(); 
        
        trie->children[iKey]->value = value;
        trie->children[iKey]->is_terminal = 1;
    }else
        trie->children[iKey] = insert(trie->children[iKey], value, &(key[1]));
    

    return trie;
}

Trie* search(Trie *trie, char *key){
    if(!trie) return NULL;

    if(key[0]=='\0'){
        return (trie->is_terminal)? trie : NULL;
    }

    int iKey = (int) key[0];
    return search(trie->children[iKey], &(key[1]));
}

/*void print_trie_aux(Trie* trie, char *key){
    if(trie){
        printf(key);
        printf("%d\n", trie->is_terminal);

        if(trie->is_terminal){
            printf(key);
            printf(" %d\n", trie->value);
        }
        char *str;
        char new[5];
        for(int i = 0; i<A_LENGTH; i++){
            strcpy(str, key);
            new[0] = i;
            new[1] = '\0';
            strcat(str, new);
            printf("entrou");
            printf(str);
            print_trie_aux(trie->children[i], str);
        }
    }
}

void print_trie(Trie* trie){
    char *aux = "";
    print_trie_aux(trie, aux);
}*/

Trie *t_remove(Trie *trie, char *key){
    if(!trie) return trie;

    Trie *aux = NULL;

    if(key[0]=='\0'){
        trie->is_terminal = 0;
    }
    else {
        int iKey = (int) key[0];
        aux = t_remove(trie->children[iKey], &(key[1]));
        trie->children[iKey] = aux;
    }

    if(aux || trie->is_terminal) return trie;

    for(int i = 0; i<A_LENGTH; i++){
        if(trie->children[i]){
            return trie;
        }
    }

    free(trie->children);
    free(trie);

    return NULL;
}

//###########################################################
//Exported functions:

void trie_insert(char *key, int value){
    root = insert(root, value, key);
}

void trie_remove(char *key){
    root = t_remove(root, key);
}

int trie_search(char *key){
    Trie *goal = search(root, key);

    //retorno provisório
    if(!goal) return -1;

    return goal->value;
}

int main(){
    return 0;
}