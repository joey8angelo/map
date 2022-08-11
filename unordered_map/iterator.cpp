#include "unordered_map.h"
template <typename T1, typename T2>
unordered_map<T1, T2>::iterator::iterator(unordered_map<T1, T2>* m, unordered_map<T1, T2>::Node* n, int b) : bucket(b), node(n), map(m) {
    if (map->vec[0] == nullptr)
        ++(*this);
}

template <typename T1, typename T2>
T1& unordered_map<T1, T2>::iterator::first() {
    return node->data.first;
}

template <typename T1, typename T2>
T2& unordered_map<T1, T2>::iterator::second() {
    return node->data.second;
}

template <typename T1, typename T2>
void unordered_map<T1, T2>::iterator::operator++() {
    
    if (node == nullptr) {
        while (node == nullptr) {
            if (++bucket >= map->vec.size()) {
                bucket = -1;
                return;
            }
            node = map->vec[bucket];
        }
    }
    else if (node->next == nullptr) {
        node = nullptr;
        while (node == nullptr) {
            if (++bucket >= map->vec.size()) {
                bucket = -1;
                break;
            }
            else {
                node = map->vec[bucket];
            }
        }
    }
    else
        node = node->next;
}

template <typename T1, typename T2>
bool unordered_map<T1, T2>::iterator::operator==(iterator rhs) {
    if (node == rhs.node && bucket == rhs.bucket && map == rhs.map)
        return true;
    else
        return false;
}

template <typename T1, typename T2>
bool unordered_map<T1, T2>::iterator::operator!=(iterator rhs) {
    return !operator==(rhs);
}

template <typename T1, typename T2>
void unordered_map<T1, T2>::reverse_iterator::operator++(){
    st.pop();
    if(st.empty()) {
        if (--iterator::bucket <= 0) {
            iterator::node = nullptr;
            iterator::bucket = -1;
            return;
        }
        iterator::node = vec[iterator::bucket];
        if (iterator::node == nullptr){
            while (iterator::node == nullptr) {
                if(iterator::bucket <= 0) {
                    iterator::bucket = -1;
                    return;
                }
                iterator::node = vec[iterator::bucket--];
            }
            return;
        }
        while(iterator::node->next != nullptr) {
            st.push(iterator::node);
            iterator::node = iterator::node->next;
        }
        iterator::node = st.top();
    }
    else
        iterator::node = st.top();
}