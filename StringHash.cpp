#include "StringHash.h++"

// Calcula um valor hash longo a partir de uma string
long long string_to_long_hash(const std::string& str) {
    long long hash_val = 0;
    const int P = 31; // Número primo comum
    const int M = 1e9 + 9; // Primo grande (para modularização, se necessário)

    for (char c : str) {
        // Combina o hash anterior com o valor ASCII do caractere (mais P)
        hash_val = (hash_val * P + (c - 'a' + 1)) % M; 
        // Se a string for longa, use abs(hash_val) para o h'(k)
    }
    // Retorna o valor absoluto para garantir que seja positivo
    return std::abs(hash_val); 
}