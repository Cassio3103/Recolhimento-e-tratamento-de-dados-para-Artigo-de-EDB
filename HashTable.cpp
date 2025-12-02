#include "HashTable.h++"
#include <cmath>
#include <cstdlib>

// --- IMPLEMENTAÇÃO BASE HashTable ---

HashTable::HashTable(int size) : M(size), table(size, EMPTY_SLOT), probes_counter(0) { }

void HashTable::reset_probes_counter() {
    probes_counter = 0;
}

int HashTable::hash_inicial(long long key) {
    // Usa valor absoluto e retorna um índice no intervalo [0, M-1]
    long long h = std::llabs(key);
    return (int)(h % M);
}

long long HashTable::insert(long long key) {
    if (key == EMPTY_SLOT || key == DELETED_SLOT) return 0; // inválido

    // Tentar até M sondagens (se não achar, tabela considerada cheia)
    for (long long i = 0; i < (long long)M; ++i) {
        int index = next_probe_index(key, i);

        if (table[index] == EMPTY_SLOT || table[index] == DELETED_SLOT) {
            table[index] = key;
            return i + 1; // numero de sondagens (1-based)
        }

        if (table[index] == key) {
            // chave já presente; contar sondagens efetuadas até aqui
            return i + 1;
        }
    }
    // Falha - tabela cheia ou não cobriu todos os indices úteis
    return (long long)M;
}

bool HashTable::search(long long key) {
    if (key == EMPTY_SLOT || key == DELETED_SLOT) return false;

    for (long long i = 0; i < (long long)M; ++i) {
        int index = next_probe_index(key, i);
        probes_counter++;

        if (table[index] == EMPTY_SLOT) {
            // Campo vazio encontrado -> chave não está na tabela
            return false;
        }
        if (table[index] == key) {
            return true;
        }
    }
    return false;
}

// --- IMPLEMENTAÇÃO HashTable_Linear ---
HashTable_Linear::HashTable_Linear(int size) : HashTable(size) {}

int HashTable_Linear::next_probe_index(long long key, long long i) {
    int h0 = hash_inicial(key);
    long long idx = (long long)h0 + i;
    idx %= M;
    if (idx < 0) idx += M;
    return (int)idx;
}

// --- IMPLEMENTAÇÃO HashTable_Quadratic ---
HashTable_Quadratic::HashTable_Quadratic(int size) : HashTable(size) {}

int HashTable_Quadratic::next_probe_index(long long key, long long i) {
    int h0 = hash_inicial(key);
    long long quad = i * i;
    long long idx = (long long)h0 + quad;
    idx %= M;
    if (idx < 0) idx += M;
    return (int)idx;
}

// --- IMPLEMENTAÇÃO HashTable_SQO (Sondagem Quadrática Otimizada) ---
HashTable_SQO::HashTable_SQO(int size) : HashTable(size) {}

int HashTable_SQO::next_probe_index(long long key, long long i) {
    int h0 = hash_inicial(key);

    // --- calcula j dependente da chave (corrige o problema de usar j fixo) ---
    // queremos um pequeno offset j >= 1; limitamos j para um valor pequeno (ex: <=7)
    // e também garantimos que j < M para evitar comportamento degenerado quando M pequeno.
    int maxCandidate = 7;
    if (M - 1 < maxCandidate) maxCandidate = std::max(1, M - 1); // garante >=1

    int j_offset = 1 + (int)(std::llabs(key) % maxCandidate); // 1..maxCandidate

    // --- cálculo do passo de sondagem ---
    long long linear_term = (long long)j_offset * i;
    long long quadratic_term = i * i;
    long long probe_step = linear_term + quadratic_term;

    long long idx = (long long)h0 + probe_step;
    idx %= M;
    if (idx < 0) idx += M;
    return (int)idx;
}