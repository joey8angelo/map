#ifndef ITERATOR_H
#define ITERATOR_H

#include "map.h"
#include <stack>

template <typename T1, typename T2>
class iterator{
private:
    std::stack<Node<T1, T2>*> nextStack;
public:
    iterator(Node<T1, T2>*);
    iterator(Node<T1, T2>*, int) {} // do nothing - keep stack size 0 indicates last value
    iterator(Node<T1, T2>*, const T1&);
    T1& first();
    T2& second();
    void operator++();
    bool operator==(iterator);
    bool operator!=(iterator);

};

#endif