#include "map.h"

/* constructor */
template <typename T1, typename T2>
map<T1, T2>::iterator::iterator(map<T1, T2>::Node* root) : defaultFirst(T1()), defaultSecond(T2()) {
    if(root == nullptr)
        return;
    map<T1, T2>::Node* curr = root;
    while (curr != nullptr){
        nextStack.push(curr);
        curr = curr->l;
    }
}

/* constructor for iterator to find an internal node, iterator will be a past-the-end iterator if key not found */
template <typename T1, typename T2>
map<T1, T2>::iterator::iterator(map<T1, T2>::Node* root, const T1& key) : defaultFirst(T1()), defaultSecond(T2()) {
    if(root == nullptr)
        return;
    map<T1, T2>::Node* curr = root;
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
    if (nextStack.empty())
        return defaultFirst;
    else
        return nextStack.top()->data.first;
}

/* returns the value that the iterator is referring to */
template <typename T1, typename T2>
T2& map<T1, T2>::iterator::second() {
    if (nextStack.empty())
        return defaultSecond;
    else
        return nextStack.top()->data.second;
}

/* increments iterator to the next inOrder value */
template <typename T1, typename T2>
void map<T1, T2>::iterator::operator++() {
    if(nextStack.empty())
        return;
    map<T1, T2>::Node* curr = nextStack.top()->r;
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
map<T1, T2>::reverse_iterator::reverse_iterator(map<T1, T2>::Node* root) : iterator::iterator() {
        if(root == nullptr)
        return;
    map<T1, T2>::Node* curr = root;
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
    map<T1, T2>::Node* curr = iterator::nextStack.top()->l;
    iterator::nextStack.pop();
    while (curr != nullptr) {
        iterator::nextStack.push(curr);
        curr = curr->r;
    }
}