#ifndef MAP_H
#define MAP_H

#include <utility>
#include <algorithm>
#include <string>
#include <iostream>
#include <stack>

template <typename T1, typename T2>
class map{
private:

struct Node{
        Node(std::pair<T1, T2> d) : data(d), l(nullptr), r(nullptr), height(0) {}
        Node(std::pair<T1, T2> d, int h) : data(d), l(nullptr), r(nullptr), height(h) {}
        int height;
        std::pair<T1, T2> data;
        Node* l;
        Node* r;
    };
    
public:
    map() : root(nullptr), _size(0), maxSize(1000) {}
    map(map<T1, T2>::Node* r, int s): root(r), _size(s) {}
    ~map();

    class iterator{
    protected:
        std::stack<Node*> nextStack;
        T1 defaultFirst;
        T2 defaultSecond;
    public:
        iterator(map<T1, T2>::Node*);
        iterator() : defaultFirst(T1()), defaultSecond(T2()) {}
        iterator(map<T1, T2>::Node*, const T1&);
        T1& first();
        T2& second();
        void operator++();
        bool operator==(iterator);
        bool operator!=(iterator);
        friend class map<T1, T2>;
    };

    class reverse_iterator: public iterator{
    public:
        reverse_iterator(map<T1, T2>::Node*);
        reverse_iterator(): iterator::iterator() {}
        reverse_iterator(Node* n, const T1& t): iterator::iterator(n, t) {}
        void operator++();
    };  

    bool empty() const;
    int size() const;
    int max_size() const;
    void insert(std::pair<T1, T2>);
    void clear();
    void swap(map<T1, T2>&);
    T2& operator[](const T1&);
    map<T1, T2>& operator=(const map<T1, T2>&);
    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    iterator find(const T1&) const;
    int count(const T1&) const;
    std::pair<iterator, bool> emplace(T1, T2);
    T2& at(const T1&);
    void erase(map<T1, T2>::iterator);
    void erase(const T1);
    friend class iterator;
    friend class reverse_iterator;

private:

    Node* equalHelper(map<T1, T2>::Node*);
    void clear(map<T1, T2>::Node*);
    Node* insert(std::pair<T1, T2>, map<T1, T2>::Node*, map<T1, T2>::Node*&);
    int height(map<T1, T2>::Node*) const;
    Node* L(map<T1, T2>::Node*);
    Node* LL(map<T1, T2>::Node*);
    Node* R(map<T1, T2>::Node*);
    Node* RR(map<T1, T2>::Node*);

    int _size;
    int maxSize;
    Node* root;
};

#endif