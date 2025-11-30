#include "HashTable.h++"
#include <iostream>

// --- IMPLEMENTAÇÃO DA CLASSE BASE HashTable ---

HashTable::HashTable(int size) : M(size), table(size, EMPTY), probes_counter(0) {}

void HashTable::reset_probes_counter() {
    probes_counter = 0;
}

int HashTable::hash_inicial(long long key) {
    return std::abs(key) % M;
}

// Implementação Comum de Insert (usa next_probe_index())
bool HashTable::insert(long long key) {
    if (key == EMPTY || key == DELETED) return false; 

    for (int i = 0; i < M; ++i) {
        int index = next_probe_index(key, i); // Chama o probing específico
        probes_counter++;

        if (table[index] == EMPTY || table[index] == DELETED) {
            table[index] = key;
            return true;
        }

        if (table[index] == key) {
            return true; // Chave já existe
        }
    }
    return false; // Falha (Tabela cheia ou loop)
}

// Implementação Comum de Search (usa next_probe_index())
bool HashTable::search(int key) {
    if (key == EMPTY || key == DELETED) return false;

    for (int i = 0; i < M; ++i) {
        int index = next_probe_index(key, i); // Chama o probing específico
        probes_counter++;

        if (table[index] == EMPTY) {
            return false; // Parar: chave nunca esteve aqui
        }
        if (table[index] == key) {
            return true; // Sucesso
        }
    }
    return false;
}

// --- IMPLEMENTAÇÃO DA CLASSE DERIVADA HashTable_Quadratic ---

HashTable_Quadratic::HashTable_Quadratic(int size) : HashTable(size) {}
HashTable_SQO::HashTable_SQO(int size) : HashTable(size) {}

int HashTable_Quadratic::next_probe_index(long long key, int i) {
    int initial_index = hash_inicial(key);
    // Sondagem Quadrática: h(k, i) = (h'(k) + i^2) mod M
    return (initial_index + i * i) % M; 
}

// --- IMPLEMENTAÇÃO DA CLASSE DERIVADA HashTable_Linear ---

HashTable_Linear::HashTable_Linear(int size) : HashTable(size) {}

int HashTable_Linear::next_probe_index(long long key, int i) {
    int initial_index = hash_inicial(key);
    // Sondagem Linear: h(k, i) = (h'(k) + i) mod M
    return (initial_index + i) % M; 
}

/*Aqui, estou adicionando a implementação da classe derivada
HasTable_SQO (Otimizada)*/

int HashTable_SQO::next_probe_index(long long key, int i) {
    // 1. Primeiro Hash (h1(k))
    // O h1(k) é seu hash inicial simples (geralmente key % M)
    int h1_index = hash_inicial(key); 
    
    // 2. O SEGUNDO HASH (h2(k)): Fator de Diversidade (Otimização)
    const int P = 503; // Primo para garantir boa distribuição do h2(k)
    
    // Calcula h2(k) = 1 + (key % P), garantindo que h2(k) nunca seja 0.
    long long h2_factor = 1 + (key % P); 

    // 3. CÁLCULO DO PASSO DE SONDA: Combinando h2(k)*i (Double Hashing) e i^2 (Quadrático)
    
    // Usamos long long para todas as operações intermediárias
    long long i_long = (long long)i;
    
    // Termo Linear (Diversidade): h2(k) * i
    long long linear_term = h2_factor * i_long; 
    
    // Termo Quadrático: i^2
    long long quadratic_term = i_long * i_long; 

    // O passo total: (h2(k) * i + i^2)
    long long probe_step = linear_term + quadratic_term;
    
    // 4. RETORNO FINAL: (h1(k) + probe_step) mod M
    // A soma deve ser em long long antes do módulo M.
    return (int)((h1_index + probe_step) % M); 
}