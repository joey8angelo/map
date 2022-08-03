#ifndef ITERATOR_H
#define ITERATOR_H

#include "map.h"
#include <stack>

template <typename T1, typename T2>
class iterator : public map<T1, T2>{
private:
    std::stack<Node<T1, T2>*> nextStack;
public:
    iterator(Node<T1, T2>*, int);
    iterator(Node<T1, T2>*, int, int) {} // do nothing - keep stack size 0 indicates last value
    T1& first();
    T2& second();
    void operator++();
    bool operator==(iterator);
    bool operator!=(iterator);

};

#endif