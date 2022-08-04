#include "map.h"

/* destructor */
template <typename T1, typename T2>
map<T1, T2>::~map() {
    clear(root);
}

/* returns true if map is empty */
template <typename T1, typename T2>
bool map<T1, T2>::empty() {
    return root == nullptr;
}

/* returns the size of the map */
template <typename T1, typename T2>
int map<T1, T2>::size() {
    return this->_size;
}

/* returns the max size of the map */
template <typename T1, typename T2>
int map<T1, T2>::max_size() {
    return this->maxSize;
}

/* interface for inserting a new key value pair */
template <typename T1, typename T2>
void map<T1, T2>::insert(std::pair<T1, T2> data) {
    if (_size == maxSize) // do nothing when max size reached
        return;
    root = insert(data, root, nullptr);
    _size++;
}

/* main insertion logic, returns the new root node, recalculates height of necessary nodes */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::insert(std::pair<T1, T2> data, Node<T1, T2>* node, Node<T1, T2>*& newNode) {
    if (node == nullptr) {
        node = new Node<T1, T2>(data);
        newNode = node;
    }
    else if (data.first < node->data.first){
        node->l = insert(data, node->l, newNode);
        if (height(node->l) - height(node->r) == 2){
            if (data.first < node->l->data.first)
                node = L(node);
            else
                node = LL(node);
        }
    }
    else if (data.first > node->data.first){
        node->r = insert(data, node->r, newNode);
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

/* returns the height of a given node */
template <typename T1, typename T2>
int map<T1, T2>::height(Node<T1, T2>* node) {
    return (node == nullptr) ? -1 : node->height;
}

/* left rotate the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::L(Node<T1, T2>* node) {
    Node<T1, T2>* curr = node->l;
    node->l = curr->r;
    curr->r = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->l), node->height) + 1;
    return curr;
}

/* double rotate left the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::LL(Node<T1, T2>* node) {
    node->l = R(node->l);
    return L(node);
}

/* right rotate the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::R(Node<T1, T2>* node) {
    Node<T1, T2>* curr = node->r;
    node->r = curr->l;
    curr->l = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->r), node->height) + 1;
    return curr;
    
}

/* double rotate right the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::RR(Node<T1, T2>* node) {
    node->r = L(node->r);
    return R(node);
}

/* interface for removing all elements, update size and root */
template <typename T1, typename T2>
void map<T1, T2>::clear() {
    clear(root);
    _size = 0;
    root = nullptr;
}

/* logic for removing all elements */
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

/* swaps contents of two maps, iterators will refer to elements in the other map */
template <typename T1, typename T2>
void map<T1, T2>::swap(map<T1, T2>& rhs) {
    Node<T1, T2>* rhsRoot = rhs.root;
    rhs.root = this->root;
    this->root = rhsRoot;
    int rhsS = rhs._size;
    rhs._size = this->_size;
    this->_size = rhsS;
}

/* access operator, if key not found creates a new element with default value */
template <typename T1, typename T2>
T2& map<T1, T2>::operator[](T1 t){
    Node<T1, T2>* curr = root;
    while (curr != nullptr) {
        if (t == curr->data.first)
            return curr->data.second;
        else if (t < curr->data.first) 
            curr = curr->l;
        else
            curr = curr->r;
    }
    Node<T1, T2>* ptr = nullptr; // pointer to element after insertion
    insert(std::pair<T1, T2>(t, T2()), root, ptr);
    _size++;
    return ptr->data.second;
}

/* returns iterator referring to first element in map */
template <typename T1, typename T2>
iterator<T1, T2> map<T1, T2>::begin() {
    return iterator<T1, T2>(root);
}

/* returns iterator referring to the past-the-end element in map */
template <typename T1, typename T2>
iterator<T1, T2> map<T1, T2>::end() {
    return iterator<T1, T2>(root, 0);
}