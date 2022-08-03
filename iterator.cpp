#include "iterator.h"

template <typename T1, typename T2>
iterator<T1, T2>::iterator(Node<T1, T2>* root, int s) : map<T1, T2>(root, s) {
    Node<T1, T2>* curr = root;
    while (curr != nullptr){
        nextStack.push(curr);
        curr = curr->l;
    }
}

template <typename T1, typename T2>
T1& iterator<T1, T2>::first() {
    return nextStack.top()->data.first;
}

template <typename T1, typename T2>
T2& iterator<T1, T2>::second() {
    return nextStack.top()->data.second;
}

template <typename T1, typename T2>
void iterator<T1, T2>::operator++() {
    Node<T1, T2>* curr = nextStack.top()->r;
    nextStack.pop();
    while (curr != nullptr) {
        nextStack.push(curr);
        curr = curr->l;
    }
}

template <typename T1, typename T2>
bool iterator<T1, T2>::operator==(iterator rhs) {
    return this->nextStack == rhs.nextStack;
}

template <typename T1, typename T2>
bool iterator<T1, T2>::operator!=(iterator rhs) {
    return this->nextStack != rhs.nextStack;
}
