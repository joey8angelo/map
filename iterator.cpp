#include "iterator.h"

/* constructor */
template <typename T1, typename T2>
iterator<T1, T2>::iterator(Node<T1, T2>* root) : root(root) {
    if(root == nullptr)
        return;
    Node<T1, T2>* curr = root;
    while (curr != nullptr){
        nextStack.push(curr);
        curr = curr->l;
    }
}

/* returns the key that the iterator is referring to */
template <typename T1, typename T2>
T1& iterator<T1, T2>::first() {
    return nextStack.top()->data.first;
}

/* returns the value that the iterator is referring to */
template <typename T1, typename T2>
T2& iterator<T1, T2>::second() {
    return nextStack.top()->data.second;
}

/* increments iterator to the next inOrder value */
template <typename T1, typename T2>
void iterator<T1, T2>::operator++() {
    Node<T1, T2>* curr = nextStack.top()->r;
    nextStack.pop();
    while (curr != nullptr) {
        nextStack.push(curr);
        curr = curr->l;
    }
}

/* check if iterators are equal to each other */
template <typename T1, typename T2>
bool iterator<T1, T2>::operator==(iterator rhs) {
    return this->nextStack == rhs.nextStack;
}

/* check if iterators are not equal to each other */
template <typename T1, typename T2>
bool iterator<T1, T2>::operator!=(iterator rhs) {
    return this->nextStack != rhs.nextStack;
}
