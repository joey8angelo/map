#include "unordered_map.h"

/* copy constructor */
template <typename T1, typename T2>
unordered_map<T1, T2>::unordered_map(unordered_map<T1, T2>& mp) : _max_bucket_count(357913941), vec(mp.vec.size(), nullptr), size(mp.size), load_factor(mp.load_factor), _max_load_factor(.75), hasher(std::hash<T1>()){
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
    iterator i = find(data.first);
    if (i != end()) {
        return std::pair<iterator, bool>(i, false);
    }
    load_factor = ++size / double(vec.size());
    if (load_factor >= _max_load_factor) {
        if(vec.size() < _max_bucket_count){  // if max_bucket_count reached do not rehash
            rehash();
            load_factor = size / double(vec.size());
        }
        if (size >= _max_bucket_count)
            return std::pair<iterator, bool>(i, false); // return past-the-end iterator if max size reached
    }
    std::size_t hs = hasher(data.first) % vec.size();
    Node* ins = vec[hs];
    if (ins == nullptr) {
        vec[hs] = new Node(data);
        return std::pair<iterator, bool>(iterator(this, vec[hs], hs), true);
    }
    else {
        while (ins->next != nullptr) {
            ins = ins->next;
        }
        ins->next = new Node(data);
        return std::pair<iterator, bool>(iterator(this, ins->next, hs), true);
    }
}

/* rehash a new vector of size nextPrime(vec.size() * 2) */
template <typename T1, typename T2>
void unordered_map<T1, T2>::rehash() {
    int newBuckets = nextPrime(vec.size() * 2);
    std::vector<Node*> newVec(newBuckets, nullptr);
    iterator itr = begin();
    while (itr != end()) {
        std::size_t hs = hasher(itr.first()) % newBuckets;
        if (newVec[hs] == nullptr)
            newVec[hs] = new Node(itr.node->data);
        else {
            Node* curr = newVec[hs];
            while(curr->next != nullptr)
                curr = curr->next;
            curr->next = new Node(itr.node->data);
        }
        ++itr;
    }
    remove_all();
    vec = newVec;
}

/* deletes all elements in the vector without changing its size, load_factor, etc */
template <typename T1, typename T2>
void unordered_map<T1, T2>::remove_all() {
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
        vec[i] = nullptr;
    }
}

/* deletes all elements in the vector */
template <typename T1, typename T2>
void unordered_map<T1, T2>::clear() {
    remove_all();
    size = 0; 
    load_factor = 0;
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
    int p = 0;
    if (vec[b] == nullptr)
        p = -1;
    return unordered_map<T1, T2>::local_iterator(this, vec[b], b, p);
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
int unordered_map<T1, T2>::bucket_count() const{
    return vec.size();
}

/* return the number of elements in a bucket */
template <typename T1, typename T2>
int unordered_map<T1, T2>::bucket_size(int b) const{
    Node* curr = vec[b];
    int i = 0;
    while (curr != nullptr) {
        i++;
        curr = curr->next;
    }
    return i;
}

/* return amount of elements with key, can either be 0 or 1 as there cannot be duplicate keys */
template <typename T1, typename T2>
int unordered_map<T1, T2>::count(const T1& key) const{
    std::size_t hs = hasher(key);
    hs = hs % bucket_count();
    Node* curr = vec[hs];
    while (curr != nullptr) {
        if (curr->data.first == key)
            return 1;
        else
            curr = curr->next;
    }
    return 0;
}

/* return iterator to element with key */
template <typename T1, typename T2>
typename unordered_map<T1, T2>::iterator unordered_map<T1, T2>::find(const T1& key) {
    std::size_t hs = hasher(key) % bucket_count();
    Node* curr = vec[hs];
    while (curr != nullptr) {
        if (curr->data.first == key) {
            return iterator(this, curr, hs);
        }
        curr = curr->next;
    }
    return iterator(this);
}

/* return the bucket number of a key */
template <typename T1, typename T2>
int unordered_map<T1, T2>::bucket(const T1& key) const {
    return hasher(key) % bucket_count();
}

/* return max_bucket_count */
template <typename T1, typename T2>
int unordered_map<T1, T2>::max_bucket_count() {
    return _max_bucket_count;
}

/* return max_load_factor */
template <typename T1, typename T2>
int unordered_map<T1, T2>::max_load_factor() {
    return _max_load_factor;
}

/* return max_size */
template <typename T1, typename T2>
int unordered_map<T1, T2>::max_size() {
    return _max_bucket_count;
}

/* return true if the map is empty */
template <typename T1, typename T2>
bool unordered_map<T1, T2>::empty() {
    return !size;
}

/* remove an element from the map */
template <typename T1, typename T2>
void unordered_map<T1, T2>::erase(iterator itr) {
    if (itr == end()) { // do nothing if iterator is end()
        return;
    }
    Node* curr = vec[itr.bucket]; // store value at first position in the bucket
    if (curr->next == nullptr) { // no other elements delete node
        vec[itr.bucket] = nullptr;
        delete itr.node;
    }
    else {
        if (curr == itr.node) { // if node to delete is the first node make vec point to next node
            vec[itr.bucket] = curr->next;
            delete itr.node;
            return;
        }
        while (curr->next != itr.node) { // iterate until node to delete found
            curr = curr->next;
        }
        curr->next = itr.node->next; // parent node points to node to delete next value
        delete itr.node;
    }
    size--;
    load_factor = size / (double)bucket_count();
}

/* remove an element from the map */
template <typename T1, typename T2>
void unordered_map<T1, T2>::erase(T1& key) {
    erase(find(key));
}

/* if key exists in map returns a reference to its mapped value, if not inserts a new item with key and default value */
template <typename T1, typename T2>
T2& unordered_map<T1, T2>::operator[](const T1& key){
    std::pair<iterator, bool> a = insert(std::pair<T1, T2>(key, T2()));
    return a.first.second();
}

/* returns a reference to the value mapped at key, will throw out_of_range if key does not exist */
template <typename T1, typename T2>
T2& unordered_map<T1, T2>::at(const T1& key) const {
    std::size_t hs = hasher(key) % bucket_count();
    Node* node = vec[hs];
    while (node != nullptr) {
        if (key == node->data.first)
            return node->data.second;
        else
            node = node->next;
    }
    throw std::out_of_range("unordered_map::at");
}

/* inserts new element if the key is unique similar to insert function */
template <typename T1, typename T2>
std::pair<typename unordered_map<T1, T2>::iterator, bool> unordered_map<T1, T2>::emplace(T1 key, T2 value) {
    return insert(std::pair<T1, T2>(key, value));
}

/* make map lhs equal to the values of map rhs */
template <typename T1, typename T2>
unordered_map<T1, T2>& unordered_map<T1, T2>::operator=(const unordered_map<T1, T2>& rhs) {
    remove_all();
    vec = std::vector<Node*>(rhs->vec.size(), nullptr);
    for (int i = 0; i < vec.size(); i++) {
        if (rhs->vec[i] != nullptr) {
            Node* curr = rhs->vec[i];
            vec[i] = new Node(curr->data);
            Node* thisCurr = vec[i];
            while(curr->next != nullptr){
                thisCurr->next = new Node(curr->next->data);
                thisCurr = thisCurr->next;
                curr = curr->next;
            }
        }
    }
    size = rhs->size;
    load_factor = rhs.load_factor;
    return this;
}