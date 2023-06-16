#include "trie.h"

int main(){

   trie_insert("a", 13);
   trie_insert("abracadabra", 12);

   //trie_insert("abacaxi", 3);

   //trie_insert("a tonito", 5);

   char *str = JSONStringSubTree("a");

   printf("%s \n", str);

   return 0;
}