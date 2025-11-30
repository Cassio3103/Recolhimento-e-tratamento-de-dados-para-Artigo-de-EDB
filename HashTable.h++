#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <cmath>
using std::vector;

/*O estados dos Slots da tabela*/

const int EMPTY = -1; 
const int DELETED = -2;

class HashTable {
protected:
    int M; // Tamanho da tabela
    vector<int> table;
    int hash_inicial(long long key);

public:
    long long probes_counter; // Variável para rastrear o número total de sondas
    
    // Construtor
    HashTable(int size);
    
    // Métodos virtuais puros (interface comum)
    virtual int next_probe_index(long long key, int i) = 0; // O coracao do probing
    virtual bool insert(long long key);
    virtual bool search(int key);
    
    // Metodos auxiliares
    void reset_probes_counter();
};

// --- CLASSES DERIVADAS (IMPLEMENTAÇÕES DE PROBING) ---

class HashTable_Quadratic : public HashTable {
public:
    HashTable_Quadratic(int size);
    int next_probe_index(long long key, int i) override; // Implementa h(k, i) = (h'(k) + i^2) mod M
};

class HashTable_Linear : public HashTable {
public:
    HashTable_Linear(int size);
    int next_probe_index(long long key, int i) override; // Implementa h(k, i) = (h'(k) + i) mod M
};

class HashTable_SQO : public HashTable{
    public:
        HashTable_SQO(int size);
        int next_probe_index(long long key, int i) override;
};


#endif