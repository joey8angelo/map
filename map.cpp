#include "map.h"

template <typename T1, typename T2>
map<T1, T2>::~map() {
    clear(root);
}

template <typename T1, typename T2>
bool map<T1, T2>::empty() {
    return root == nullptr;
}

template <typename T1, typename T2>
int map<T1, T2>::size() {
    return this->s;
}

template <typename T1, typename T2>
int map<T1, T2>::max_size() {
    return this->ms;
}

template <typename T1, typename T2>
void map<T1, T2>::insert(std::pair<T1, T2> data) {
    if (s == ms)
        return;
    root = insert(data, root);
    s++;
}

template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::insert(std::pair<T1, T2> data, Node<T1, T2>* node) {
    if (node == nullptr)
        node = new Node<T1, T2>(data);
    else if (data.first < node->data.first){
        node->l = insert(data, node->l);
        if (height(node->l) - height(node->r) == 2){
            if (data.first < node->l->data.first)
                node = L(node);
            else
                node = LL(node);
        }
    }
    else if (data.first > node->data.first){
        node->r = insert(data, node->r);
        if (height(node->r) - height(node->l) == 2) {
            if (data.first > node->r->data.first)
                node = R(node);
            else
                node = RR(node);
        }
    }
    node->height = std::max(height(node->l), height(node->r)) + 1;
    return node;
}

template <typename T1, typename T2>
int map<T1, T2>::height(Node<T1, T2>* node) {
    return (node == nullptr) ? -1 : node->height;
}

template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::L(Node<T1, T2>* node) {
    Node<T1, T2>* curr = node->l;
    node->l = curr->r;
    curr->r = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->l), node->height) + 1;
    return curr;
}

template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::LL(Node<T1, T2>* node) {
    node->l = R(node->l);
    return L(node);
}

template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::R(Node<T1, T2>* node) {
    Node<T1, T2>* curr = node->r;
    node->r = curr->l;
    curr->l = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->r), node->height) + 1;
    return curr;
    
}

template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::RR(Node<T1, T2>* node) {
    node->r = L(node->r);
    return R(node);
}

template <typename T1, typename T2>
void map<T1, T2>::clear() {
    clear(root);
}

template <typename T1, typename T2>
void map<T1, T2>::clear(Node<T1, T2>* node) {
    if (node == nullptr)
        return;
    else {
        clear(node->r);
        clear(node->l);
        delete node;
    }
}