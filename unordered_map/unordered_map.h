#ifndef UNORDERED_MAP
#define UNORDERED_MAP

#include <functional>
#include <stack>
#include <vector>

template <typename T1, typename T2>
class unordered_map {
private:
    struct Node {
        Node(std::pair<T1, T2> d) : data(d), next(nullptr) {}
        std::pair<T1, T2> data;
        Node* next;
    };

public:
    unordered_map() : vec(1, nullptr), size(0), load_factor(0), max_load_factor(.75), hasher(std::hash<T1>()){}
    unordered_map(unordered_map<T1, T2>&);
    ~unordered_map();

    class iterator {
    public:
        iterator(unordered_map<T1, T2>* m) : bucket(-1), node(nullptr), map(m), defaultFirst(T1()), defaultSecond(T2()) {}
        iterator(unordered_map<T1, T2>* m, unordered_map<T1, T2>::Node* n, int b) : bucket(b), node(n), map(m), defaultFirst(T1()), defaultSecond(T2()) {}
        T1& first();
        T2& second();
        void operator++();
        bool operator==(iterator);
        bool operator!=(iterator);
        friend class unordered_map;
    protected:
        Node* node;
        int bucket;
        unordered_map<T1, T2>* map;
        T1 defaultFirst;
        T2 defaultSecond;
    };
    class local_iterator: public iterator {
    public:
        local_iterator(unordered_map<T1,T2>* m, unordered_map<T1, T2>::Node* n, int b, int p = 0) : iterator::iterator(m, n, b), pos(p) {}
        void operator++();
        bool operator==(local_iterator);
        bool operator!=(local_iterator);
    protected:
        int pos;
    };

    std::pair<iterator, bool> insert(const std::pair<T1, T2>&);
    iterator begin();
    local_iterator begin(int);
    iterator end();
    local_iterator end(int);
    void clear();
    int bucket(const T1&);
    int bucket_count();
    friend class iterator;

private:
    void rehash();
    int nextPrime(int);
    bool isPrime(int);
    std::vector<Node*> vec;
    int size;
    double load_factor;
    double max_load_factor;
    const std::hash<T1> hasher;
};

#endif