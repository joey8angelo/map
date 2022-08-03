#include <iostream>
#include "map.cpp"

int main() {
    map<int, int> mp1, mp2;

    mp1.insert(std::pair<int, int>(1, 2));
    mp1.insert(std::pair<int, int>(3, 4));
    mp1.insert(std::pair<int, int>(5, 6));
    mp1.insert(std::pair<int, int>(7, 8));

    mp2.insert(std::pair<int, int>(0, 1));
    mp2.insert(std::pair<int, int>(2, 3));
    mp2.insert(std::pair<int, int>(4, 5));
    mp2.insert(std::pair<int, int>(6, 7));

    mp1.swap(mp2);
    
    
    return 0;
}