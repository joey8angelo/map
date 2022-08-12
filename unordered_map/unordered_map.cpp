#include "unordered_map.h"

/* copy constructor */
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

/* destructor */
template <typename T1, typename T2>
unordered_map<T1, T2>::~unordered_map() {
    clear();
}

/* inserts a new element if the key does not exist already */
template <typename T1, typename T2>
std::pair<typename unordered_map<T1, T2>::iterator, bool> unordered_map<T1, T2>::insert(const std::pair<T1, T2>& data) {
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

/* rehash a new vector of size nextPrime(vec.size() * 2) */
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

/* deletes all elements in the vector */
template <typename T1, typename T2>
void unordered_map<T1, T2>::clear() {
    for(int i = 0; i < vec.size(); i++) {
        if (vec[i] != nullptr){
            Node* curr = vec[i];
            Node* next = curr->next;
            while (curr->next != nullptr) {
                delete curr;
                curr = next;
                next = next->next;
            }
            delete curr;
        }
    }
}

/* find the nearest prime after n */
template <typename T1, typename T2>
int unordered_map<T1, T2>::nextPrime(int n) {
    if (n % 2 == 0) {
        n++;
    }
    while (!isPrime(n))
        n += 2;
    return n;
}

/* primality test */
template <typename T1, typename T2>
bool unordered_map<T1, T2>::isPrime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

/* return an iterator to the first element in the vector */
template <typename T1, typename T2>
typename unordered_map<T1, T2>::iterator unordered_map<T1, T2>::begin() {
    Node* curr = vec[0];
    int i = 0;
    while (curr == nullptr && ++i < vec.size())
        curr = vec[i];
    if (curr == nullptr)
        i = -1;
    return unordered_map<T1, T2>::iterator(this, curr, i);
}

/* return a local_iterator to the element at bucket b */
template <typename T1, typename T2>
typename unordered_map<T1, T2>::local_iterator unordered_map<T1, T2>::begin(int b) {
    return unordered_map<T1, T2>::local_iterator(this, vec[b], b);
}

/* return iterator to past-the-end element */
template <typename T1, typename T2>
typename unordered_map<T1, T2>::iterator unordered_map<T1, T2>::end() {
    return unordered_map<T1, T2>::iterator(this);
}

/*return local_iterator to past-the-end element */
template <typename T1, typename T2>
typename unordered_map<T1, T2>::local_iterator unordered_map<T1, T2>::end(int b) {
    return unordered_map<T1, T2>::local_iterator(this, nullptr, b, -1);
}

/* return the amount of buckets in the map */
template <typename T1, typename T2>
int unordered_map<T1, T2>::bucket_count() {
    return vec.size();
}