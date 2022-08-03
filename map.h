#ifndef MAP_H
#define MAP_H

#include <utility>
#include <algorithm>
#include <string>
#include <iostream>

template <typename T, typename F>
struct Node{
    Node(std::pair<T, F> d) : data(d), l(nullptr), r(nullptr), height(0) {}
    int height;
    std::pair<T, F> data;
    Node* l;
    Node* r;
};

template <typename T, typename F>
class map{
public:
    map() : root(nullptr), s(0), ms(1000) {}
    bool empty();
    int size();
    int max_size();
    void insert(std::pair<T, F>);
private:
    Node<T, F>* insert(std::pair<T, F>, Node<T, F>*);
    int height(Node<T, F>*);
    Node<T, F>* L(Node<T, F>*);
    Node<T, F>* LL(Node<T, F>*);
    Node<T, F>* R(Node<T, F>*);
    Node<T, F>* RR(Node<T, F>*);
    Node<T, F>* root;
    int s;
    int ms;
};

#endif