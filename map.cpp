#include "map.h"

/* destructor */
template <typename T1, typename T2>
map<T1, T2>::~map() {
    clear(root);
}

/* returns true if map is empty */
template <typename T1, typename T2>
bool map<T1, T2>::empty() {
    return root == nullptr;
}

/* returns the size of the map */
template <typename T1, typename T2>
int map<T1, T2>::size() {
    return this->_size;
}

/* returns the max size of the map */
template <typename T1, typename T2>
int map<T1, T2>::max_size() {
    return this->maxSize;
}

/* interface for inserting a new key value pair */
template <typename T1, typename T2>
void map<T1, T2>::insert(std::pair<T1, T2> data) {
    if (_size == maxSize) // do nothing when max size reached
        return;
    Node<T1, T2>* dummy = nullptr;
    Node<T1, T2>* node = insert(data, root, dummy);
    if (node == nullptr)
        return;
    else
        root = node;
    _size++;
}

/* main insertion logic, returns the new root node, recalculates height of necessary nodes */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::insert(std::pair<T1, T2> data, Node<T1, T2>* node, Node<T1, T2>*& newNode) {
    if (node == nullptr) {
        node = new Node<T1, T2>(data);
        newNode = node;
    }
    else if (node->data.first == data.first) {
        return nullptr;
    }
    else if (data.first < node->data.first){
        Node<T1, T2>* tmp = insert(data, node->l, newNode);
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
        Node<T1, T2>* tmp = insert(data, node->r, newNode);
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
int map<T1, T2>::height(Node<T1, T2>* node) {
    return (node == nullptr) ? -1 : node->height;
}

/* left rotate the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::L(Node<T1, T2>* node) {
    Node<T1, T2>* curr = node->l;
    node->l = curr->r;
    curr->r = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->l), node->height) + 1;
    return curr;
}

/* double rotate left the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::LL(Node<T1, T2>* node) {
    node->l = R(node->l);
    return L(node);
}

/* right rotate the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::R(Node<T1, T2>* node) {
    Node<T1, T2>* curr = node->r;
    node->r = curr->l;
    curr->l = node;
    node->height = std::max(height(node->l), height(node->r)) + 1;
    curr->height = std::max(height(curr->r), node->height) + 1;
    return curr;
    
}

/* double rotate right the given node */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::RR(Node<T1, T2>* node) {
    node->r = L(node->r);
    return R(node);
}

/* interface for removing all elements, update size and root */
template <typename T1, typename T2>
void map<T1, T2>::clear() {
    clear(root);
    _size = 0;
    root = nullptr;
}

/* logic for removing all elements */
template <typename T1, typename T2>
void map<T1, T2>::clear(Node<T1, T2>* node) {
    if (node == nullptr)
        return;
    else {
        clear(node->r);
        clear(node->l);
        delete node;
    }
}

/* swaps contents of two maps, iterators will refer to elements in the other map */
template <typename T1, typename T2>
void map<T1, T2>::swap(map<T1, T2>& rhs) {
    Node<T1, T2>* rhsRoot = rhs.root;
    rhs.root = this->root;
    this->root = rhsRoot;
    int rhsS = rhs._size;
    rhs._size = this->_size;
    this->_size = rhsS;
}

/* access operator, if key not found creates a new element with default value */
template <typename T1, typename T2>
T2& map<T1, T2>::operator[](const T1& t){
    Node<T1, T2>* curr = root;
    while (curr != nullptr) {
        if (t == curr->data.first)
            return curr->data.second;
        else if (t < curr->data.first) 
            curr = curr->l;
        else
            curr = curr->r;
    }
    Node<T1, T2>* ptr = nullptr; // pointer to element after insertion
    root = insert(std::pair<T1, T2>(t, T2()), root, ptr);
    _size++;
    return ptr->data.second;
}

/* returns iterator referring to first element in map */
template <typename T1, typename T2>
iterator<T1, T2> map<T1, T2>::begin() {
    return iterator<T1, T2>(root);
}

/* returns iterator referring to the past-the-end element in map 
   unlike std::map the end iterator cannot be accessed and will cause a seg fault */
template <typename T1, typename T2>
iterator<T1, T2> map<T1, T2>::end() {
    return iterator<T1, T2>();
}

/* returns iterator of the element with the given key, if no element is found
   returns an iterator to the past-the-end element*/
template <typename T1, typename T2>
iterator<T1, T2> map<T1, T2>::find(const T1& key) {
    return iterator<T1, T2>(root, key);
}

/* counts elements with specific key
   map can only have one instance of a specific key so return will be 0 or 1 */
template <typename T1, typename T2>
int const map<T1, T2>::count(const T1& key) {
    return find(key) != end() ? 1 : 0;
}

/* inserts new element if key is unique returns pair<iterator, bool> */
template <typename T1, typename T2>
std::pair<iterator<T1, T2>, bool> map<T1, T2>::emplace(T1 key, T2 value) {
    Node<T1, T2>* ins = nullptr;
    insert(std::pair<T1, T2>(key, value), root, ins);
    if (ins == nullptr)
        return std::pair<iterator<T1, T2>, bool>(end(), false);
    else
        return std::pair<iterator<T1, T2>, bool>(find(key), true);
}

/* copies contents of rhs into lhs, removing its current content */
template <typename T1, typename T2>
map<T1, T2>& map<T1, T2>::operator=(const map<T1, T2>& rhs) {
    clear();
    root = equalHelper(rhs.root);
    _size = rhs._size;
}

/* helper for operator=, linearly copies all elements recursively */
template <typename T1, typename T2>
Node<T1, T2>* map<T1, T2>::equalHelper(Node<T1, T2>* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node<T1, T2>* curr = new Node<T1, T2>(node->data, node->height);
    curr->l = equalHelper(node->l);
    curr->r = equalHelper(node->r);
    return curr;
}

/* returns a reference to the value mapped at key, will throw out_of_range if key does not exist */
template <typename T1, typename T2>
T2& map<T1, T2>::at(const T1& key) {
    Node<T1, T2>* curr = root;
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

/* erase an key value pair from the map with an iterator, invalidates all iterators */
template <typename T1, typename T2>
void map<T1, T2>::erase(iterator<T1, T2> itr) {
    if (itr == end()) // if itr refers to nothing do nothing
        return;
    
    // do a normal BST delete
    Node<T1, T2>* node = itr.nextStack.top(); // store node to delete
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
        std::stack<Node<T1, T2>*> st = itr.nextStack; // new stack = itr stack
        Node<T1, T2>* curr = node;
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
        iterator<T1, T2> itr2 = begin();
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

            Node<T1, T2>* t;
            Node<T1, T2>* prev;

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

            Node<T1, T2>* t;
            Node<T1, T2>* prev;

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

template <typename T1, typename T2>
void map<T1, T2>::erase(const T1& key) {
    erase(find(key));
}