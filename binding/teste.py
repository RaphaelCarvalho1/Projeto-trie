from trie_py import Trie
import json

trie = Trie();

trie.insert("a", 12);

trie.insert("abracadabra", 13);

stres = trie.JSONStringSubTree("av");

print(stres)

result = json.loads(stres);

print(result)#, result["value"])