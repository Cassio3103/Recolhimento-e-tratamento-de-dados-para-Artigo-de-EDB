#include "utilities.h++"
#include "StringHash.h++"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

vector<long long> read_keys_from_csv(const string& filename, int key_column_index) {
    vector<long long> keys;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo CSV: " << filename << endl;
        return keys;
    }

    getline(file, line); // Ignora o cabeçalho
    char delimiter = ';'; // Assumindo delimitador padrão da UFRN: ';'

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int current_column = 0;
        
        while (getline(ss, token, delimiter)) {
            if (current_column == key_column_index) {
                try {
                    // SUBSTITUA stoi(token) pelo string_to_long_hash
                    long long key_hash = string_to_long_hash(token); 
                    if (key_hash > 0) { 
                        keys.push_back(key_hash);
                    }
                } catch (const exception& e) {
                    // Ignora
                }
                break;
            }
            current_column++;
        }
    }
    file.close();
    return keys;
}

vector<int> generate_keys(int count, int max_value) {
    vector<int> keys;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, max_value); 

    for (int i = 0; i < count; ++i) {
        keys.push_back(distrib(gen));
    }
    return keys;
}

// Em utilities.cpp (Implementação)

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int get_prime_size(int required_size) {
    int p = required_size;
    while (true) {
        if (is_prime(p)) return p;
        p++;
    }
}