#include "HashTable.h++"
#include "utilities.h++"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip> // Para setprecision
#include <chrono>  // Para medição de tempo

using namespace std;

// DECLARAÇÕES: Mantenha sempre o tipo long long para as chaves
void run_experiment(const vector<long long>& keys, int M, double alpha, ostream& os);
void print_header(ostream& os);


int main(int argc, char* argv[]) {
    // Verifica argumentos
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <caminho_para_csv> <indice_da_coluna_chave>" << endl;
        return 1;
    }

    string filename = argv[1];
    int key_column_index = stoi(argv[2]);

    // 1. LEITURA DE CHAVES (Retorna vector<long long>)
    vector<long long> keys = read_keys_from_csv(filename, key_column_index);

    if (keys.empty()) {
        cerr << "Nao ha chaves validas para processar. Verifique o arquivo e o indice." << endl;
        return 1;
    }

    int num_keys = keys.size();
    
    // 2. DEFINICAO DOS FATORES DE CARGA (Para testar o limite, até 0.99)
    vector<double> load_factors = {0.50, 0.70, 0.80, 0.90, 0.95, 0.99}; 

    // Imprime o cabeçalho do CSV de saída
    print_header(cout);

    // 3. EXECUÇÃO DO EXPERIMENTO
    for (double alpha : load_factors) {
        
        // CALCULA o tamanho M ideal para o fator de carga (N/alpha)
        int required_size = (int)std::ceil(num_keys / alpha);
        
        // OBRIGATÓRIO: Força M a ser o próximo número primo (Correção de estabilidade)
        int M = get_prime_size(required_size); 

        // Roda o experimento para o M primo encontrado
        run_experiment(keys, M, alpha, cout);
    }

    return 0;
}

void run_experiment(const vector<long long>& keys, int M, double alpha, ostream& os) {
    
    int num_keys = keys.size();

    // 1. Inicializa as Hash Tables com o M PRIMO
    // Nota: M é passado para o construtor de cada tabela.
    HashTable_Linear ht_sl(M);
    HashTable_Quadratic ht_sq(M);
    HashTable_SQO ht_sqo(M);

    // 2. Insere as chaves e coleta métricas

    // SL
    long long total_probes_sl = 0;
    auto start_sl = chrono::high_resolution_clock::now();
    for (long long key : keys) total_probes_sl += ht_sl.insert(key);
    auto end_sl = chrono::high_resolution_clock::now();
    long long time_sl = chrono::duration_cast<chrono::microseconds>(end_sl - start_sl).count();

    // SQ
    long long total_probes_sq = 0;
    auto start_sq = chrono::high_resolution_clock::now();
    for (long long key : keys) total_probes_sq += ht_sq.insert(key);
    auto end_sq = chrono::high_resolution_clock::now();
    long long time_sq = chrono::duration_cast<chrono::microseconds>(end_sq - start_sq).count();
    
    // SQ Otimizada
    long long total_probes_sqo = 0;
    auto start_sqo = chrono::high_resolution_clock::now();
    for (long long key : keys) total_probes_sqo += ht_sqo.insert(key);
    auto end_sqo = chrono::high_resolution_clock::now();
    long long time_sqo = chrono::duration_cast<chrono::microseconds>(end_sqo - start_sqo).count();

    // 3. Imprime os Resultados
    double nms_sl = (double)total_probes_sl / num_keys;
    double nms_sq = (double)total_probes_sq / num_keys;
    double nms_sqo = (double)total_probes_sqo / num_keys;

    os << fixed << setprecision(2) << alpha << ",";
    os << M << "," << num_keys << ",";
    os << fixed << setprecision(4) << nms_sl << ",";
    os << time_sl << ",";
    os << fixed << setprecision(4) << nms_sq << ",";
    os << time_sq << ",";
    os << fixed << setprecision(4) << nms_sqo << ",";
    os << time_sqo << endl;
}

void print_header(ostream& os) {
    os << "Alpha,M_Size,N_Keys,NMS_SL,Time_SL_us,NMS_SQ,Time_SQ_us,NMS_SQO,Time_SQO_us" << endl;
}