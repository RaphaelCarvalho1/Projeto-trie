#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifdef BUILD_DLL
// the dll exports
#define EXPORT __declspec(dllexport)
#else
// the exe imports
#define EXPORT __declspec(dllimport)
#endif

// function to be imported/exported

EXPORT int trie_insert(char *key, int value); 

EXPORT int trie_remove(char *key);; 

EXPORT int trie_search(char *key); 

