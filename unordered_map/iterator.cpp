#include "unordered_map.h"

/* return reference to first value iterator refers to */
template <typename T1, typename T2>
T1& unordered_map<T1, T2>::iterator::first() {
    if (node == nullptr)
        return defaultFirst;
    else
        return node->data.first;
}

/* return reference to second value iterator refers to */
template <typename T1, typename T2>
T2& unordered_map<T1, T2>::iterator::second() {
    if (node == nullptr)
        return defaultSecond;
    else
        return node->data.second;
}

/* iterates to next element in map */
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

/* return true if iterators are equal to each other */
template <typename T1, typename T2>
bool unordered_map<T1, T2>::iterator::operator==(iterator rhs) {
    if (node == rhs.node && bucket == rhs.bucket && map == rhs.map)
        return true;
    else
        return false;
}

/* return true if iterators are not equal to each other */
template <typename T1, typename T2>
bool unordered_map<T1, T2>::iterator::operator!=(iterator rhs) {
    return !operator==(rhs);
}

/* iterates to next element in the bucket */
template <typename T1, typename T2>
void unordered_map<T1, T2>::local_iterator::operator++() {
    if (iterator::node->next == nullptr || iterator::node == nullptr) {
        pos = -1;
        iterator::node = nullptr;
        return;
    }
    else {
        iterator::node = iterator::node->next;
        pos += 1;
    }
}

/* return true if local_iterators are equal to each other */
template <typename T1, typename T2>
bool unordered_map<T1, T2>::local_iterator::operator==(local_iterator rhs) {
    if (iterator::node == rhs.node && iterator::bucket == rhs.bucket && iterator::map == rhs.map && pos == rhs.pos)
        return true;
    else
        return false;
}

/* return true if local_iterators are not equal to each other */
template <typename T1, typename T2>
bool unordered_map<T1, T2>::local_iterator::operator!=(local_iterator rhs) {
    return !operator==(rhs);
}