#include "utilities.h++"
#include "StringHash.h++"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <cmath>
using namespace std;

vector<long long> read_keys_from_csv(const string& filename, int key_column_index) {
    vector<long long> keys;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo CSV: " << filename << endl;
        return keys;
    }

    // Se houver cabeçalho, ignora a primeira linha
    if (!getline(file, line)) {
        file.close();
        return keys;
    }

    char delimiter = ';'; // Assumindo delimitador padrão da UFRN: ';'

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int current_column = 0;
        
        while (getline(ss, token, delimiter)) {
            if (current_column == key_column_index) {
                try {
                    long long key_hash = string_to_long_hash(token); 
                    if (key_hash > 0) { 
                        keys.push_back(key_hash);
                    }
                } catch (const exception& e) {
                    // Ignora token inválido
                }
                break;
            }
            ++current_column;
        }
    }
    file.close();
    return keys;
}

vector<int> generate_keys(int count, int max_value) {
    vector<int> keys;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, max_value); 

    for (int i = 0; i < count; ++i) {
        keys.push_back(distrib(gen));
    }
    return keys;
}

// primalidade simples (suficiente para valores moderados)
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; (long long)i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int get_prime_size(int required_size) {
    int p = std::max(2, required_size);
    while (true) {
        if (is_prime(p)) return p;
        ++p;
    }
}
