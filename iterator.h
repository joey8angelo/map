#ifndef ITERATOR_H
#define ITERATOR_H

#include "map.h"
#include <stack>

template <typename T1, typename T2>
class iterator{
protected:
    std::stack<Node<T1, T2>*> nextStack;
public:
    iterator(Node<T1, T2>*);
    iterator() {} // do nothing - keep stack size 0 indicates last value
    iterator(Node<T1, T2>*, const T1&);
    T1& first();
    T2& second();
    void operator++();
    bool operator==(iterator);
    bool operator!=(iterator);
    friend class map<T1, T2>;
};

template <typename T1, typename T2>
class reverse_iterator: public iterator<T1, T2>{
public:
    reverse_iterator(Node<T1, T2>*);
    reverse_iterator(): iterator<T1, T2>::iterator() {}
    reverse_iterator(Node<T1, T2>* n, const T1& t): iterator<T1, T2>::iterator(n, t) {}
    void operator++();
};

#endif