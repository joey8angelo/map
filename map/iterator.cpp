#include "map.h"

/* constructor */
template <typename T1, typename T2>
map<T1, T2>::iterator::iterator(Node<T1, T2>* root) {
    if(root == nullptr)
        return;
    Node<T1, T2>* curr = root;
    while (curr != nullptr){
        nextStack.push(curr);
        curr = curr->l;
    }
}

/* constructor for iterator to find an internal node, iterator will be a past-the-end iterator if key not found */
template <typename T1, typename T2>
map<T1, T2>::iterator::iterator(Node<T1, T2>* root, const T1& key) {
    if(root == nullptr)
        return;
    Node<T1, T2>* curr = root;
    while(curr != nullptr) {
        nextStack.push(curr);
        if (curr->data.first == key)
            return;
        else if (key < curr->data.first)
            curr = curr->l;
        else
            curr = curr->r;
    }
    while(!nextStack.empty()){
        nextStack.pop();
    }
}

/* returns the key that the iterator is referring to */
template <typename T1, typename T2>
T1& map<T1, T2>::iterator::first() {
    return nextStack.top()->data.first;
}

/* returns the value that the iterator is referring to */
template <typename T1, typename T2>
T2& map<T1, T2>::iterator::second() {
    return nextStack.top()->data.second;
}

/* increments iterator to the next inOrder value */
template <typename T1, typename T2>
void map<T1, T2>::iterator::operator++() {
    if(nextStack.empty())
        return;
    Node<T1, T2>* curr = nextStack.top()->r;
    nextStack.pop();
    while (curr != nullptr) {
        nextStack.push(curr);
        curr = curr->l;
    }
}

/* return true if iterators are equal to each other */
template <typename T1, typename T2>
bool map<T1, T2>::iterator::operator==(iterator rhs) {
    return this->nextStack == rhs.nextStack;
}

/* return true if iterators are not equal to each other */
template <typename T1, typename T2>
bool map<T1, T2>::iterator::operator!=(iterator rhs) {
    return this->nextStack != rhs.nextStack;
}

/* constructor */
template <typename T1, typename T2>
map<T1, T2>::reverse_iterator::reverse_iterator(Node<T1, T2>* root) : iterator::iterator() {
        if(root == nullptr)
        return;
    Node<T1, T2>* curr = root;
    while (curr != nullptr){
        iterator::nextStack.push(curr);
        curr = curr->r;
    }
}

/* increments iterator to the next reverse inOrder value */
template <typename T1, typename T2>
void map<T1, T2>::reverse_iterator::operator++() {
    if(iterator::nextStack.empty())
        return;
    Node<T1, T2>* curr = iterator::nextStack.top()->l;
    iterator::nextStack.pop();
    while (curr != nullptr) {
        iterator::nextStack.push(curr);
        curr = curr->r;
    }
}