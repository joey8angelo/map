#include "unordered_map.h"

template <typename T1, typename T2>
unordered_map<T1, T2>::Node::~Node() {
    if (this->next != nullptr) {
        delete this->next;
    }
}

template <typename T1, typename T2>
unordered_map<T1, T2>::unordered_map(unordered_map<T1, T2>& mp) : vec(mp.vec.size(), nullptr), size(mp.size), load_factor(mp.load_factor), max_load_factor(.75), hasher(std::hash<T1>()){
    for (int i = 0; i < vec.size(); i++) {
        if (mp.vec[i] != nullptr) {
            Node* curr = mp.vec[i];
            vec[i] = new Node(curr->data);
            Node* thisCurr = vec[i];
            while(curr->next != nullptr){
                thisCurr->next = new Node(curr->next->data);
                thisCurr = thisCurr->next;
                curr = curr->next;
            }
        }
    }
}
template <typename T1, typename T2>
unordered_map<T1, T2>::~unordered_map() {
    clear();
}

template <typename T1, typename T2>
std::pair<typename unordered_map<T1, T2>::iterator, bool> unordered_map<T1, T2>::insert(std::pair<T1, T2> data) {
    load_factor = ++size / double(vec.size());
    if (load_factor >= max_load_factor)
        rehash();
    int v = hasher(data.first);
    v = v % vec.size();
    Node* ins = vec[v];
    if (ins == nullptr) {
        vec[v] = new Node(data);
        return std::pair<iterator, bool>(iterator(this, vec[v], v), true);
    }
    else {
        while (ins->next != nullptr) {
            if (ins->data.first == data.first)
                return std::pair<iterator, bool>(iterator(this, ins, v), true);
            ins = ins->next;
        }
        ins->next = new Node(data);
        return std::pair<iterator, bool>(iterator(this, ins->next, v), true);
    }
}

template <typename T1, typename T2>
void unordered_map<T1, T2>::rehash() {
    int newBuckets = nextPrime(vec.size() * 2);
    std::vector<Node*> newVec(newBuckets, nullptr);
    iterator itr = begin();
    while (itr != end()) {
        int hs = hasher(itr.first()) % newBuckets;
        if (newVec[hs] == nullptr)
            newVec[hs] = new Node(itr.node->data);
        else {
            Node* curr = itr.node;
            while(curr->next != nullptr)
                curr = curr->next;
            curr->next = new Node(itr.node->data);
        }
        ++itr;
    }
    clear();
    vec = newVec;
}

template <typename T1, typename T2>
void unordered_map<T1, T2>::clear() {
    for(int i = 0; i < vec.size(); i++) {
        if (vec[i] != nullptr)
            delete vec[i];
    }
}

template <typename T1, typename T2>
int unordered_map<T1, T2>::nextPrime(int n) {
    if (n % 2 == 0) {
        n++;
    }
    while (!isPrime(n))
        n += 2;
    return n;
}

template <typename T1, typename T2>
bool unordered_map<T1, T2>::isPrime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

template <typename T1, typename T2>
typename unordered_map<T1, T2>::iterator unordered_map<T1, T2>::begin() {
    return unordered_map<T1, T2>::iterator(this, vec[0], 0);
}

template <typename T1, typename T2>
typename unordered_map<T1, T2>::iterator unordered_map<T1, T2>::end() {
    return unordered_map<T1, T2>::iterator(this);
}

template <typename T1, typename T2>
typename unordered_map<T1, T2>::reverse_iterator unordered_map<T1, T2>::rbegin() {
    return unordered_map<T1, T2>::reverse_iterator(this, vec[vec.size() - 1], vec.size());
}

template <typename T1, typename T2>
typename unordered_map<T1, T2>::reverse_iterator unordered_map<T1, T2>::rend() {
    return unordered_map<T1, T2>::reverse_iterator(this);
}