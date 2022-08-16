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
    unordered_map() : _max_bucket_count(357913941), vec(1, nullptr), _size(0), _load_factor(0), _max_load_factor(.75), hasher(std::hash<T1>()){}
    unordered_map(unordered_map<T1, T2>&);
    ~unordered_map();

    class iterator {
    public:
        iterator(unordered_map<T1, T2>* m, unordered_map<T1, T2>::Node* n = nullptr, int b = -1) : bucket(b), node(n), map(m), defaultFirst(T1()), defaultSecond(T2()) {}
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
        local_iterator(unordered_map<T1,T2>* m, unordered_map<T1, T2>::Node* n, int b, int p) : iterator::iterator(m, n, b), pos(p) {}
        void operator++();
        bool operator==(local_iterator);
        bool operator!=(local_iterator);
    protected:
        int pos;
    };

    std::pair<iterator, bool> insert(const std::pair<T1, T2>&);
    T2& operator[](const T1&);
    unordered_map& operator=(const unordered_map&);
    iterator begin();
    local_iterator begin(int);
    iterator end();
    local_iterator end(int);
    void clear();
    int bucket(const T1&) const;
    int bucket_count() const;
    int bucket_size(int) const;
    int count(const T1&) const;
    iterator find(const T1&);
    double max_load_factor() const;
    void max_load_factor(double z);
    int max_bucket_count();
    int max_size();
    int size() const;
    bool empty();
    void erase(iterator);
    void erase(T1);
    T2& at(const T1&);
    std::pair<iterator, bool> emplace(T1, T2);
    double load_factor() const;
    void rehash(int);
    void swap(unordered_map&);
    friend class iterator;

private:
    void remove_all();
    int nextPrime(int);
    bool isPrime(int);
    std::vector<Node*> vec;
    int _size;
    double _load_factor;
    double _max_load_factor;
    const int _max_bucket_count;
    const std::hash<T1> hasher;
};

#endif