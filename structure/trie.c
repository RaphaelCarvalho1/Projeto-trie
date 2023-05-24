#include "trie.h"
#include "string.h"

#define A_LENGTH 128

typedef struct Node{
    struct Node **children;
    int value;
    int is_terminal;
}Trie;

int trie_insert(char *key, int value){
    return 0;
}

int trie_remove(char *key){
    return 1;
}

int trie_search(char *key){
    return 2;
}


Trie* create(){
    Trie *new = (Trie *) malloc(sizeof(Trie));
    new->is_terminal = 0;
    new->children = (Trie**) malloc(sizeof(Trie*)*A_LENGTH);

    for(int i = 0; i<A_LENGTH; i++)
        new->children[i] = NULL;

    return new;
}

Trie *insert(Trie *trie, int value, char *key){
    if(!trie) trie = create();

    if(key[0]=='\0'){
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

    if(key[0]=='\0'){
        trie->is_terminal = 0;
    }

    int iKey = (int) key[0];

    trie->children[iKey] = t_remove(trie->children[iKey], &(key[1]));

    int has_child = 0;

    for(int i = 0; i<A_LENGTH; i++){
        if(trie->children[i]){
            has_child = 1;
            break;
        }
    }

    if(!has_child){
        Trie *trash = trie;
        free(trash->children);
        free(trash);

        trie = NULL;
    }

    return trie;
}

int main(){
    Trie *trie = NULL;

    trie = insert(trie, 2, "ala");
    trie = insert(trie, 3, "ali");
    trie = insert(trie, 5, "ei");

    //printf("%d %d %d\n", search(trie, "ali")->value, search(trie, "ala")->value, search(trie, "ei")->value);

    trie = t_remove(trie, "ala");

    if(!search(trie, "ala"))
        printf("nao achou");

    printf("%d %d\n", search(trie, "ei")->value);

    return 0;
}