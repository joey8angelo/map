#include "map.h"

/* destructor */
template <typename T1, typename T2>
map<T1, T2>::~map() {
    clear(root);
}

/* returns true if map is empty */
template <typename T1, typename T2>
bool map<T1, T2>::empty() const{
    return root == nullptr;
}

/* returns the size of the map */
template <typename T1, typename T2>
int map<T1, T2>::size() const {
    return this->_size;
}

/* returns the max size of the map */
template <typename T1, typename T2>
int map<T1, T2>::max_size() const {
    return this->maxSize;
}

/* inserts a new key value pair into the map */
template <typename T1, typename T2>
void map<T1, T2>::insert(std::pair<T1, T2> data) {
    if (_size == maxSize) // do nothing when max size reached
        return;
    map<T1, T2>::Node* dummy = nullptr;
    map<T1, T2>::Node* node = insert(data, root, dummy);
    if (node == nullptr)
        return;
    else
        root = node;
    _size++;
}

/* removes all elements from the map */
template <typename T1, typename T2>
void map<T1, T2>::clear() {
    clear(root);
    _size = 0;
    root = nullptr;
}

/* swaps contents of two maps, iterators will refer to elements in the other map */
template <typename T1, typename T2>
void map<T1, T2>::swap(map<T1, T2>& rhs) {
    map<T1, T2>::Node* rhsRoot = rhs.root;
    rhs.root = this->root;
    this->root = rhsRoot;
    int rhsS = rhs._size;
    rhs._size = this->_size;
    this->_size = rhsS;
}

/* access operator, if key not found creates a new element with default value */
template <typename T1, typename T2>
T2& map<T1, T2>::operator[](const T1& t){
    map<T1, T2>::Node* curr = root;
    while (curr != nullptr) {
        if (t == curr->data.first)
            return curr->data.second;
        else if (t < curr->data.first) 
            curr = curr->l;
        else
            curr = curr->r;
    }
    map<T1, T2>::Node* ptr = nullptr; // pointer to element after insertion
    root = insert(std::pair<T1, T2>(t, T2()), root, ptr);
    _size++;
    return ptr->data.second;
}

/* copies contents of rhs into lhs, removing its current content */
template <typename T1, typename T2>
map<T1, T2>& map<T1, T2>::operator=(const map<T1, T2>& rhs) {
    clear();
    root = equalHelper(rhs.root);
    _size = rhs._size;
}

/* returns iterator referring to first element in map */
template <typename T1, typename T2>
typename map<T1, T2>::iterator map<T1, T2>::begin() const {
    return map<T1, T2>::iterator(root);
}

/* returns iterator referring to the past-the-end element in map */
template <typename T1, typename T2>
typename map<T1, T2>::iterator map<T1, T2>::end() const {
    return map<T1, T2>::iterator();
}

/* returns reverse_iterator referring to last element in map */
template <typename T1, typename T2>
typename map<T1, T2>::reverse_iterator map<T1, T2>::rbegin() {
    return reverse_iterator(root);
}

/* returns reverse_iterator referring to the past-the-end element in map */
template <typename T1, typename T2>
typename map<T1, T2>::reverse_iterator map<T1, T2>::rend() {
    return reverse_iterator();
}

/* returns iterator of the element with the given key, if no element is found
   returns an iterator to the past-the-end element*/
template <typename T1, typename T2>
typename map<T1, T2>::iterator map<T1, T2>::find(const T1& key) const{
    return map<T1, T2>::iterator(root, key);
}

/* counts elements with specific key
   map can only have one instance of a specific key so return will be 0 or 1 */
template <typename T1, typename T2>
int map<T1, T2>::count(const T1& key) const {
    return find(key) != end() ? 1 : 0;
}

/* inserts new element if key is unique, returns pair<iterator, bool> */
template <typename T1, typename T2>
std::pair<typename map<T1, T2>::iterator, bool> map<T1, T2>::emplace(T1 key, T2 value) {
    map<T1, T2>::Node* ins = nullptr;
    Node* n = insert(std::pair<T1, T2>(key, value), root, ins);
    if (n != nullptr)
        root = n;
    
    if (ins == nullptr)
        return std::pair<map<T1, T2>::iterator, bool>(end(), false);
    else {
        _size++;
        return std::pair<map<T1, T2>::iterator, bool>(find(key), true);
    }
}

/* returns a reference to the value mapped at key, will throw out_of_range if key does not exist */
template <typename T1, typename T2>
T2& map<T1, T2>::at(const T1& key) {
    map<T1, T2>::Node* curr = root;
    while(curr != nullptr) {
        if (key == curr->data.first) {
            return curr->data.second;
        }
        else if (key < curr->data.first) {
            curr = curr->l;
        }
        else
            curr = curr->r;
    }
    throw std::out_of_range("map::at");
}

/* erase a key value pair from the map with an iterator, invalidates all iterators */
template <typename T1, typename T2>
void map<T1, T2>::erase(map<T1, T2>::iterator itr) {
    if (itr == end()) // if itr refers to nothing do nothing
        return;
    
    // do a normal BST delete
    map<T1, T2>::Node* node = itr.nextStack.top(); // store node to delete
    itr.nextStack.pop();

    if (node->l == nullptr && node->r == nullptr) { // case 1: leaf node
        if (!itr.nextStack.empty()) {               // parent of node to delete points to nullptr
            if (itr.nextStack.top()->r == node)
                itr.nextStack.top()->r = nullptr;
            else
                itr.nextStack.top()->l = nullptr;
        }
        else
            root = nullptr; // if node has no parent it is the root
    }
    else if (node->r != nullptr && node->l != nullptr) { // case 2: node has two children
        std::stack<map<T1, T2>::Node*> st = itr.nextStack; // new stack = itr stack
        map<T1, T2>::Node* curr = node;
        st.push(curr);
        curr = curr->l;
        st.push(curr);
        while (curr->r != nullptr) { // store elements in the path to the rightmost node of left subtree
            curr = curr->r;
            st.push(curr);
        }
        std::pair<T1, T2> d = curr->data; // swap node to delete with rightmost node of left subtree
        curr->data = node->data;
        node->data = d;
        map<T1, T2>::iterator itr2 = begin();
        itr2.nextStack = st;
        erase(itr2); // make new iterator with new stack and erase the swapped node
        return;
    }
    else { // case 3: node has 1 child
        if (!itr.nextStack.empty()) {
            if (itr.nextStack.top()->r == node) // point parent to nodes child
                itr.nextStack.top()->r = node->r == nullptr ? node->l : node->r;
            else
                itr.nextStack.top()->l = node->r == nullptr ? node->l : node->r;
        }
        else
            root = node->r == nullptr ? node->l : node->r; // if node has no parent it is the root
    }

    // update heights and rotate when needed nodes above the node to delete
    while (!itr.nextStack.empty()) {
        itr.nextStack.top()->height = std::max(height(itr.nextStack.top()->l), height(itr.nextStack.top()->r)) + 1;

        int bf = height(itr.nextStack.top()->r) - height(itr.nextStack.top()->l); // balance factor
        if (bf == 2) { // positive balance factor 2 requires rotate right

            map<T1, T2>::Node* t;
            map<T1, T2>::Node* prev;

            if (height(itr.nextStack.top()->r->r) >= height(itr.nextStack.top()->r->l)) { // if right bf >= left bf normal rotate
                t = R(itr.nextStack.top());
                prev = itr.nextStack.top();
                itr.nextStack.pop();
            }
            else { // if not rotate 2 times
                t = RR(itr.nextStack.top());
                prev = itr.nextStack.top();
                itr.nextStack.pop();
            }
            if (itr.nextStack.empty()) { // if stack empty the result of rotate is the root
                root = t;
            }
            else{ // if not empty result of rotate is child of top of stack
                if (itr.nextStack.top()->r == prev)
                    itr.nextStack.top()->r = t;
                else
                    itr.nextStack.top()->l = t;
            }
        }
        else if (bf == -2) { // same logic as right

            map<T1, T2>::Node* t;
            map<T1, T2>::Node* prev;

            if (height(itr.nextStack.top()->l->l) >= height(itr.nextStack.top()->l->r)) {
                t = L(itr.nextStack.top());
                prev = itr.nextStack.top();
                itr.nextStack.pop();
            }
            else {
                t = LL(itr.nextStack.top());
                prev = itr.nextStack.top();
                itr.nextStack.pop();
            }
            if (itr.nextStack.empty()) {
                root = t;
            }
            else{
                if (itr.nextStack.top()->r == prev)
                    itr.nextStack.top()->r = t;
                else
                    itr.nextStack.top()->l = t;
            }
        }
        else
            itr.nextStack.pop(); // if no rotate required move on to next node
    }
    delete node;
    _size--;
}

/* erase a key value pair from the map with a key, invalidates all iterators */
template <typename T1, typename T2>
void map<T1, T2>::erase(const T1 key) {
    erase(find(key));
}

/* helper for operator=, copies all elements recursively int linear time*/
template <typename T1, typename T2>
typename map<T1, T2>::Node* map<T1, T2>::equalHelper(map<T1, T2>::Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    map<T1, T2>::Node* curr = new map<T1, T2>::Node(node->data, node->height);
    curr->l = equalHelper(node->l);
    curr->r = equalHelper(node->r);
    return curr;
}

/* delete elements recursively */
template <typename T1, typename T2>
void map<T1, T2>::clear(map<T1, T2>::Node* node) {
    if (node == nullptr)
        return;
    else {
        clear(node->r);
        clear(node->l);
        delete node;
    }
}

/* main insertion logic, returns the new root node, recalculates height of necessary nodes */
template <typename T1, typename T2>
typename map<T1, T2>::Node* map<T1, T2>::insert(std::pair<T1, T2> data, map<T1, T2>::Node* node, map<T1, T2>::Node*& newNode) {
    if (node == nullptr) {
        node = new map<T1, T2>::Node(data);
        newNode = node;
    }
    else if (node->data.first == data.first) {
        return nullptr;
    }
    else if (data.first < node->data.first){
        map<T1, T2>::Node* tmp = insert(data, node->l, newNode);
        if (tmp == nullptr)
            return nullptr;
        else
            node->l = tmp;
        if (height(node->l) - height(node->r) == 2){
            if (data.first < node->l->data.first)
                node = L(node);
            else
                node = LL(node);
        }
    }
    else if (data.first > node->data.first){
        map<T1, T2>::Node* tmp = insert(data, node->r, newNode);
        if (tmp == nullptr)
            return nullptr;
        else
            node->r = tmp;
        if (height(node->r) - height(node->l) == 2) {
            if (data.first > node->r->data.first)
                node = R(node);
            else
                node = RR(node);
        }
    }
    node->height = std::max(height(node->l), height(node->r)) + 1;
    return node;
}

/* returns the height of a given node */
template <typename T1, typename T2>
int map<T1, T2>::height(map<T1, T2>::Node* node) const {
    return (node == nullptr) ? -1 : node->height;
}

/* left rotate the given node */
template <typename T1, typename T2>
typename map<T1, T2>::Node* map<T1, T2>::L(map<T1, T2>::Node* node) {
    map<T1, T2>::Node* curr = node->l;
    node->l = curr->r;
    curr->r = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->l), node->height) + 1;
    return curr;
}

/* double rotate left the given node */
template <typename T1, typename T2>
typename map<T1, T2>::Node* map<T1, T2>::LL(map<T1, T2>::Node* node) {
    node->l = R(node->l);
    return L(node);
}

/* right rotate the given node */
template <typename T1, typename T2>
typename map<T1, T2>::Node* map<T1, T2>::R(map<T1, T2>::Node* node) {
    map<T1, T2>::Node* curr = node->r;
    node->r = curr->l;
    curr->l = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->r), node->height) + 1;
    return curr;
}

/* double rotate right the given node */
template <typename T1, typename T2>
typename map<T1, T2>::Node* map<T1, T2>::RR(Node* node) {
    node->r = L(node->r);
    return R(node);
}