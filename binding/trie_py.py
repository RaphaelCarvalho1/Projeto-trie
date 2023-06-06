from ctypes import *

_triem = cdll.LoadLibrary("./structure/trie.dll")

_triem.trie_insert.argtypes = [c_char_p, c_int]

_triem.trie_insert.restype = c_int

_triem.trie_remove.argtypes = [c_char_p]

_triem.trie_remove.restype = c_int

_triem.trie_search.argtypes = [c_char_p]

_triem.trie_search.restype = c_int

class Trie:
    def insert(self, key, value):
        return _triem.trie_insert(key, value)
    
    def remove(self, key):
        return _triem.trie_remove(key)
    
    def search(self, key):
        return _triem.trie_remove(key)