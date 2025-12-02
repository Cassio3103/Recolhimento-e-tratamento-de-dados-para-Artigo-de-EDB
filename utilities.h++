#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
using std::vector;
using std::string;

// Declaração da função para ler o dataset
vector<long long> read_keys_from_csv(const string& filename, int key_column_index);

// Declaração da função para gerar dados aleatórios (se necessário)
vector<int> generate_keys(int count, int max_value);

// Checa se é primo
bool is_prime(int n);
// Encontra o próximo primo
int get_prime_size(int required_size);

#endif // UTILITIES_H
