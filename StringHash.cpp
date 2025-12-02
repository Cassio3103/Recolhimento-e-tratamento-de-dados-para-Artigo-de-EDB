#include "StringHash.h++"
#include <cmath>

long long string_to_long_hash(const std::string& str) {
    long long hash_val = 0;
    const long long P = 31LL; // base polinomial
    const long long MOD = 1000000009LL; // primo grande

    for (unsigned char c : str) {
        hash_val = (hash_val * P + (long long)c) % MOD;
    }
    return std::llabs(hash_val);
}
