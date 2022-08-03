#include "map.h"

template <typename T, typename F>
bool map<T, F>::empty() {
    return root == nullptr;
}

template <typename T, typename F>
int map<T, F>::size() {
    return this->s;
}

template <typename T, typename F>
int map<T, F>::max_size() {
    return this->ms;
}

template <typename T, typename F>
void map<T, F>::insert(std::pair<T, F> data) {
    if (s == ms)
        return;
    root = insert(data, root);
    s++;
}

template <typename T, typename F>
Node<T, F>* map<T, F>::insert(std::pair<T, F> data, Node<T, F>* node) {
    if (node == nullptr)
        node = new Node<T, F>(data);
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

template <typename T, typename F>
int map<T, F>::height(Node<T, F>* node) {
    return (node == nullptr) ? -1 : node->height;
}

template <typename T, typename F>
Node<T, F>* map<T, F>::L(Node<T, F>* node) {
    Node<T, F>* curr = node->l;
    node->l = curr->r;
    curr->r = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->l), node->height) + 1;
    return curr;
}

template <typename T, typename F>
Node<T, F>* map<T, F>::LL(Node<T, F>* node) {
    node->l = R(node->l);
    return L(node);
}

template <typename T, typename F>
Node<T, F>* map<T, F>::R(Node<T, F>* node) {
    Node<T, F>* curr = node->r;
    node->r = curr->l;
    curr->l = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->r), node->height) + 1;
    return curr;
    
}

template <typename T, typename F>
Node<T, F>* map<T, F>::RR(Node<T, F>* node) {
    node->r = L(node->r);
    return R(node);
}