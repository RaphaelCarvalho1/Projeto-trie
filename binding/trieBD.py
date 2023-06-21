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

    def printAccount(self, name):
        print(self.trie.search("c "+name))

    def transact(self, originAccount, destinyAccount, ammount):

        balanceOrg = json.loads(self.trie.search("c "+originAccount))

        balanceDest = json.loads(self.trie.search("c "+destinyAccount))

        if(balanceDest["valid"] == 0 or balanceOrg["valid"] == 0):
            return "Alguma das contas não é válida."
        
        print("ah")

        balanceOrg["value"] -= ammount
        balanceDest["value"] += ammount

        self.trie.insert("c "+originAccount, balanceOrg["value"])
        self.trie.insert("c "+destinyAccount, balanceDest["value"])

        transactionsHeader = json.loads(self.trie.search("t "+originAccount+"-"+destinyAccount))

        transactionCount = 1

        if(transactionsHeader["valid"] == 1): 
            transactionCount += transactionsHeader["value"]

        self.trie.insert("t "+originAccount+"-"+destinyAccount+" "+str(transactionCount), ammount)

        self.trie.insert("t "+originAccount+"-"+destinyAccount, transactionCount)

        return "Transação realizada com sucesso!"

    def getReport(self):
        names = ["Raphael", "Rute", "Bruno", "Sara", "Christiano"]

        out = "{\"transactions\":["

        for origin in names:
            for destiny in names:
                if(origin==destiny):
                    continue

                subtree = self.trie.JSONStringSubTree("t "+origin+"-"+destiny)
                nodes = json.loads(subtree)["nodes"]

                for node in nodes:
                    if(node["value"] == None): 
                        continue

                    index = numericEnd(node["key"])
                    value = node["value"]

                    out += "{\"transaction-number\": "+index+", \"value\": "+str(value)+",\"from\":\""+origin+"\",\"to\":\""+destiny+"\"},"


        out = out[0:len(out)-1]+"]}"

        return out

def numericEnd(string):
    out = ""

    for i in range(len(string)-1, -1, -1):
        if(not string[i].isnumeric()):
            break

        out= string[i] + out

    return out