# Análise e Implementação de Árvores Trie
## Sumário
* [Introdução](#introdução)
* [Tecnologias](#tecnologias)
* [Implementação da Estrutura de Dados](#implementação-da-estrutura-de-dados)
### Introdução
#### a. Árvores Trie
Em ciência da computação, uma trie é uma estrutura de dados do tipo árvore ordenada, que pode ser usada para armazenar um array associativo em que as chaves são normalmente cadeias de caracteres. Ao contrário de uma árvore de busca binária, nenhum nó armazena a chave associada a ele; ao invés disso, a chave é determinada pela sua posição na árvore. Todos os descendentes de qualquer nó têm um prefixo comum com a cadeia associada com aquele nó, e a raiz é associada com a cadeia vazia. Normalmente, valores não são associados com todos os nós, apenas com as folhas e alguns nós internos que correspondem a chaves de interesse.
#### b. Objetivo
O objetivo deste projeto é realizar a análise e a implementação da estrutura de dados Trie e construir uma simples aplicação web que a utilize. Para isso, nós codificamos a árvore numa linguagem de programação que permitisse um *binding* à uma linguagem de script e analisamos a complexidade intríseca do problema e da solução.
### Tecnologias
O projeto foi criado com:
* Python - 3.10.5
* C
* JavaScript
### Documentação das bibliotecas e classes criadas
#### 

#### trie.h

* void trie_insert(char *key, int value); 

    Essa função recebe uma chave string e um valor, e insere na TRIE o valor indicado na posição que representa a chave.

* void trie_remove(char *key);

    Essa função recebe uma chave string e então remove da TRIE o valor inserido na chave.

* char *trie_search(char *key); 

    Essa função recebe uma chave string e retorna uma string no formato:

"{"valid":  _valid-bit_ , "value":  _number_ }"

    Onde _valid-bit_ pode ser 1 (caso o valor realmente existisse na TRIE) ou 0 (caso contrário),
    e value seria o valor contido naquela chave. Ou seja, se o nó não existir, _valid_ = 0. Se o nó existir,
    mas não for terminal, _valid_ = 0.

* char *JSONStringSubTree(char *key);

    Essa função recebe uma chave string e retorna uma string no formato:

"{nodes: {"key": _key_, "value": _number_}}"

    Onde _key_ é a chave de um nó, e _value_ é o valor inserido naquele nó. Caso o nó não seja terminal,
    _value_ pode ser null.

#### trie_py.py

* class Trie

Classe que encapsula todos os métodos importados de trie.h
    
    -insert(key, value)
    
    método que chama trie_insert.
    não possui retorno.

    -remove(key)

    método que chama trie_remove.
    não possui retorno.

    -search(key)

    método que chama trie_search e retorna o valor retornado pela mesma.

#### trieBD.py

* class TrieBD

    classe que utiliza Trie para armazenar informações sobre saldos em contas e transações
    entre contas.

    armazena internamente uma instância de Trie.

    OBS: possui algumas contas inseridas de maneira hardcoded na sua main

    * printAccount(name)

    exibe o retorno self.trie.search(_chave de name_) (instância interna de Trie)
    ou seja, uma string em formato json contendo um valid e um value.

    * transact(origin, destiny, ammount)

    realiza na trie uma transação entre origin e destiny, alterando os saldos das contas e 
    registrando a transação, caso as duas contas existam.

    retorna uma mensagem de sucesso caso a transação tenha sido feita, e uma mensagem de fracasso
    caso contrário.

    * getReport()

    retorna um histórico, que é uma string em formato json que contém uma lista com todas as transações realizadas entre as contas, no formato:

    {"transactions": {"transaction-number": _number_, "value": _number_, "from": _string_, 
    "to": _string_}, ...}

#### server.py

    utiliza websocket para se comunicar com o client, e uma instância de TrieBD para realizar
    transações e retornar o histórico.

### Complexidade

Análises da complexidade se encontram na pasta:

_./analises_
