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
    root = insert(data, root);
}

template <typename T, typename F>
Node<T, F>* map<T, F>::insert(std::pair<T, F> data, Node<T, F>* node) {
    if (node == nullptr)
        node = new Node<T, F>(data);
    else if (data.first() < t->data.first()){
        node->left = insert(data, node->left);
        if (height(node->left) - height(node->right) == 2){
            if (data < node->left->data.first())
                node = L(node);
            else
                node = LL(node);
        }
    }
    else if (data > node->data.first()){
        node->right = insert(data, node->right);
        if (height(node->right) - height(node->left) == 2) {
            if (data > node->right->data.first())
                node = R(node);
            else
                node = RR(node);
        }
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    return node;
}

template <typename T, typename F>
int map<T, F>::height(Node<T, F>* node) {
    return (node == nullptr) ? -1 : node->height;
}

template <typename T, typename F>
Node<T, F>* map<T, F>::L(Node<T, F>* node) {
    //left rotate
}

template <typename T, typename F>
Node<T, F>* map<T, F>::LL(Node<T, F>* node) {
    //double left rotate
}

template <typename T, typename F>
Node<T, F>* map<T, F>::R(Node<T, F>* node) {
    //right rotate
}

template <typename T, typename F>
Node<T, F>* map<T, F>::RR(Node<T, F>* node) {
    //double right rotate
}