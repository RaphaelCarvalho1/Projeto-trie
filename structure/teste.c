#include "trie.h"

int main(){

   trie_insert("aa", 10);
   trie_insert("ab", 11);

   trie_remove("aa");

   printf("%d %d\n", trie_search("aa"), trie_search("ab"));
   printf("ah\n");

   return 0;
}