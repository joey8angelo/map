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
        ~Node();
        std::pair<T1, T2> data;
        Node* next;
    };

public:
    unordered_map() : vec(1, nullptr), size(0), load_factor(0), max_load_factor(.75), hasher(std::hash<T1>()){}
    unordered_map(unordered_map<T1, T2>&);
    ~unordered_map();

    class iterator {
    public:
        iterator(unordered_map<T1, T2>* m) : bucket(-1), node(nullptr), map(m) {}
        iterator(unordered_map<T1, T2>*, unordered_map<T1, T2>::Node*, int);
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
    };
    class reverse_iterator : public iterator {
    public:
        reverse_iterator() : iterator::iterator() {}
        reverse_iterator(unordered_map<T1, T2>::Node* n, int b) : iterator::iterator(n, b) {}
        void operator++();
    private:
        std::stack<Node*> st;
    };

    std::pair<iterator, bool> insert(std::pair<T1, T2>);
    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();
    void clear();
    friend class iterator;
    friend class reverse_iterator;

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