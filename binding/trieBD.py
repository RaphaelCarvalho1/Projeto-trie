from trie_py import Trie
import json

class TrieBD:

    def __init__(self):
        self.trie = Trie()

        self.trie.insert("c Rute", 200)
        self.trie.insert("c Raphael", 200)
        self.trie.insert("c Sara", 200)
        self.trie.insert("c Christiano", 200)
        self.trie.insert("c Bruno", 200)

    def printAccount(self, nome):
        print(self.trie.search("c "+nome))

    def transact(self, originAccount, destinyAccount, amount):

        balanceOrg = json.loads(self.trie.search("c "+originAccount))

        balanceDest = json.loads(self.trie.search("c "+destinyAccount))

        if(balanceDest["valid"] == 0 or balanceOrg["valid"] == 0):
            return
        
        print("ah")

        balanceOrg["value"] -= amount
        balanceDest["value"] += amount

        self.trie.insert("c "+originAccount, balanceOrg["value"])
        self.trie.insert("c "+destinyAccount, balanceDest["value"])

        transactionsHeader = json.loads(self.trie.search("t "+originAccount+"-"+destinyAccount))

        transactionCount = 1

        if(transactionsHeader["valid"] == 1): 
            transactionCount += transactionsHeader["value"]

        self.trie.insert("t "+originAccount+"-"+destinyAccount+" "+str(transactionCount), amount)

        self.trie.insert("t "+originAccount+"-"+destinyAccount, transactionCount)

    def getReport(self, origin, destiny):
        subtree = self.trie.JSONStringSubTree("t "+origin+"-"+destiny)

        nodes = json.loads(subtree)["nodes"]

        out = "{\"transactions\":["

        for node in nodes:
            if(node["value"] == None): 
                continue

            index = node["key"].replace("t "+origin+"-"+destiny+" ", "")

            value = node["value"]

            out += "{\"transaction-number\": "+index+", \"value\": "+str(value)+"},"

        out = out[0:len(out)-1]+"]}"

        return out
