#ifndef MAP_H
#define MAP_H

#include <utility>
#include <algorithm>
#include <string>
#include <iostream>

template <typename T1, typename T2>
class iterator;

template <typename T1, typename T2>
struct Node{
    Node(std::pair<T1, T2> d) : data(d), l(nullptr), r(nullptr), height(0) {}
    int height;
    std::pair<T1, T2> data;
    Node* l;
    Node* r;
};

template <typename T1, typename T2>
class map{
public:
    map() : root(nullptr), _size(0), maxSize(1000) {}
    map(Node<T1, T2>* r, int s): root(r), _size(s) {}
    ~map();
    bool empty();
    int size();
    int max_size();
    void insert(std::pair<T1, T2>);
    void clear();
    void swap(map<T1, T2>&);
    T2& operator[](T1);
    iterator<T1, T2> begin();
    iterator<T1, T2> end();
    iterator<T1, T2> find(const T1&);

private:
    void clear(Node<T1, T2>*);
    Node<T1, T2>* insert(std::pair<T1, T2>, Node<T1, T2>*, Node<T1, T2>*&);
    int height(Node<T1, T2>*);
    Node<T1, T2>* L(Node<T1, T2>*);
    Node<T1, T2>* LL(Node<T1, T2>*);
    Node<T1, T2>* R(Node<T1, T2>*);
    Node<T1, T2>* RR(Node<T1, T2>*);
    int _size;
    int maxSize;
    Node<T1, T2>* root;
};

#endif