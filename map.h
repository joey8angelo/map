#ifndef MAP_H
#define MAP_H

#include <utility>
#include <algorithm>
#include <string>
#include <iostream>

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
    map() : root(nullptr), s(0), ms(1000) {}
    ~map();
    bool empty();
    int size();
    int max_size();
    void insert(std::pair<T1, T2>);
    void clear();
    void swap(map<T1, T2>&);

private:
    void clear(Node<T1, T2>*);
    Node<T1, T2>* insert(std::pair<T1, T2>, Node<T1, T2>*);
    int height(Node<T1, T2>*);
    Node<T1, T2>* L(Node<T1, T2>*);
    Node<T1, T2>* LL(Node<T1, T2>*);
    Node<T1, T2>* R(Node<T1, T2>*);
    Node<T1, T2>* RR(Node<T1, T2>*);
    Node<T1, T2>* root;
    int s;
    int ms;
};

#endif