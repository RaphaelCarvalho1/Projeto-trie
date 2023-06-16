#include "trie.h"
#include "string.h"

#define A_LENGTH 128

typedef struct ListNode{
    struct ListNode *prox;
    char *key;
}List;

List *List_new(char *key){
    List *new = (List *) malloc(sizeof(List));
    new->prox = NULL;
    new->key = key;
    return new;
}

List *List_insert(List *l, char *key){
    if(!l) return List_new(key);
    return List_insert(l->prox, key);
}

List *List_concat(List *l1, List *l2){
    if(!l1) return l2;
    l1->prox = List_concat(l1->prox, l2);
    return l1;
}

int listLen(List *l){
    if(!l) return 0;
    return strlen(l->key)+listLen(l->prox);
}

int listCount(List *l){
    if(!l) return 0;
    return 1+listCount(l->prox);
}

void List_print(List *l){
    if(l){
        printf("%s\n", l->key);
        List_print(l->prox);
    }
}

void freeList(List *l){
    if(!l) return;
    freeList(l->prox);
    free(l->key);
    free(l);
}

typedef struct Node{
    struct Node *children[A_LENGTH];
    int value;
    int is_terminal;
}Trie;

Trie *root = NULL;

void itoStr(int val, char *out);

//Trie manipulation

Trie* create(){
    Trie *new = (Trie *) malloc(sizeof(Trie));
    new->is_terminal = 0;

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

//Log functions

List *getStringTree(Trie *trie, char *key){
    if(!trie) return NULL; 

    char valueStr[sizeof(int)*8+1];

    if(trie->is_terminal)
        itoStr(trie->value, valueStr);
    else{
        valueStr[0] = 'n';
        valueStr[1] = 'u';
        valueStr[2] = 'l';
        valueStr[3] = 'l';
        valueStr[4] = '\0';
    }

    char *out = (char*) malloc(sizeof(char)*(20 + strlen(key)+strlen(valueStr)));

    out[0] = '\0';

    strcat(out, "{\"key\":\"");
    strcat(out, key);
    strcat(out, "\",\"value\":");
    strcat(out, valueStr);
    strcat(out, "}");

    List *l = NULL, *aux = NULL;

    l = List_insert(l, out);

    for(int i=0; i<A_LENGTH; i++){
        char *newKey = (char*) malloc(sizeof(char)*(1 + strlen(key)));

        newKey[0] = '\0';
        
        char *newChar = (char*) malloc(sizeof(char)*3);
        newChar[0] = i;
        newChar[1] = '\0';

        strcat(newKey, key);
        strcat(newKey, newChar);

        aux = getStringTree(trie->children[i], newKey);

        l = List_concat(l, aux);
    }

    return l;
}

char *concatListString(List *l){
    int length = listLen(l), count = listCount(l);

    char *out = (char*) malloc(sizeof(char)*(20 + length + count*2));
    out[0] = '\0';

    strcat(out, "{\"nodes\": [");

    List *aux = l;

    while(aux){
        strcat(out, aux->key);
        strcat(out, ", ");
        aux = aux->prox;
    }

    out[length+count*2+9] = ']';
    out[length+count*2+10] = '}';
    out[length+count*2+11] = '\0';

    return out;
}

char *getStringSubTree(Trie *trie, char *key){
    Trie *node = search(trie, key);

    char *out;

    if(!node) {
        out = (char*) malloc(sizeof(char)*14);
        out[0] = '\0';

        strcat(out, "{\"nodes\": []}");

        return out;
    }

    List *l = getStringTree(node, key);

    out = concatListString(l->prox);

    return out;
}

//###########################################################
//Exported functions:

void itoStr(int val, char *out){
    int i = 0, aux, abs = val>0? val: -val;

    if(!val){
        out[0] = '0';
        out[1] = '\0';
        return;
    }


    if(val<0){
        out[0] = '-';
        i++;
    }

    aux = abs;
	
    while(aux>0){
        aux = aux/10;
        i++;
    }

    out[i] = '\0';
    i--;

    aux = abs;

    while(aux>0){
        int next = aux/10;

        int digit = aux - next*10;

        char cDigit = 48 + digit;

        out[i] = cDigit;

        aux = next;

        i--;
    }
	
}

void searchOut(char *valid, int value, char *out){
    char valueStr[sizeof(int)*8+1];

    itoStr(value, valueStr);

    strcat(out, "{\"valid\":");

    strcat(out, valid);

    strcat(out, ",\"value\":");

    strcat(out, valueStr);

    strcat(out, "}");
}

char *trie_search(char *key){
    Trie *goal = search(root, key);

    int length = 0;

    char *out;

    //retorno provisório
    if(!goal) {
        length = 23;
        out = (char*) malloc(sizeof(char)*(length));

        out[0] = '\0';

        searchOut("0", 1, out);
    }else {
        int aux = goal->value;

        while(aux){
            aux/=10;
            length++;
        }

        out = (char*) malloc(sizeof(char)*(22+length));
        out[0] = '\0';

        searchOut("1", goal->value, out);
    }

    return out;
}

void trie_insert(char *key, int value){
    root = insert(root, value, key);
}

void trie_remove(char *key){
    root = t_remove(root, key);
}

char *JSONStringSubTree(char *key){
    char *out = getStringSubTree(root, key);

    return out;
}

int main(){

    trie_insert("abacaxi", 0);

    printf("%s\n",trie_search("abacaxi"));

    char out[10];
    out[0] = '\0';

    itoStr(0, out);

    printf("%s\n", out);

    return 0;
}