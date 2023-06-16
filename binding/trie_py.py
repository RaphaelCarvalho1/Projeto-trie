from ctypes import *

_triem = cdll.LoadLibrary("./structure/trie.so")

_triem.trie_insert.argtypes = [c_char_p, c_int]

_triem.trie_remove.argtypes = [c_char_p]

_triem.trie_search.argtypes = [c_char_p]

_triem.trie_search.restype = c_char_p

_triem.JSONStringSubTree.argtypes = [c_char_p]

_triem.JSONStringSubTree.restype = c_char_p

class Trie:
    def insert(self,key, value):
        _triem.trie_insert(key.encode(), value)
    
    def remove(self, key):
        _triem.trie_remove(key.encode())
    
    def search(self, key):
        out =_triem.trie_search(key.encode())
        return clean(str(out))
    
    def JSONStringSubTree(self, key):
        out =_triem.JSONStringSubTree(key.encode())

        return clean(str(out))
    

def clean(searchOut):
    out = ""

    level = 0

    for char in searchOut:
        if char == "{":
            level+=1

        if level > 0:
            out+=char

        if char == "}" :
            level-=1

    return out