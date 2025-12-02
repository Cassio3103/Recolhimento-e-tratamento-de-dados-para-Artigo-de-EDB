#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <climits>

constexpr long long EMPTY_SLOT = LLONG_MIN;
constexpr long long DELETED_SLOT = LLONG_MIN + 1;

class HashTable {
public:
    HashTable(int size);
    virtual ~HashTable() = default;

    // Insert returns number of probes performed (1-based)
    virtual long long insert(long long key);

    // Search returns true if found
    virtual bool search(long long key);

    // Reset counter of probes used in searches (separate diagnostic)
    void reset_probes_counter();

    // Getter table size
    int size() const { return M; }

protected:
    // Compute base hash index h'(k)
    int hash_inicial(long long key);

    // Each derived class implements its probing function
    virtual int next_probe_index(long long key, long long i) = 0;

    int M;
    std::vector<long long> table;
    long long probes_counter;
};

// Derived classes
class HashTable_Linear : public HashTable {
public:
    HashTable_Linear(int size);
    virtual int next_probe_index(long long key, long long i) override;
};

class HashTable_Quadratic : public HashTable {
public:
    HashTable_Quadratic(int size);
    virtual int next_probe_index(long long key, long long i) override;
};

class HashTable_SQO : public HashTable {
public:
    HashTable_SQO(int size);
    virtual int next_probe_index(long long key, long long i) override;
};

#endif // HASHTABLE_H