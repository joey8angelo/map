#include <iostream>
#include "map.cpp"
#include "iterator.cpp"

int main() {
    map<int, int> mp1, mp2;

    mp1.insert(std::pair<int, int>(1, 2));
    mp1.insert(std::pair<int, int>(3, 4));
    mp1.insert(std::pair<int, int>(5, 7));
    mp1.insert(std::pair<int, int>(7, 8));

    mp1[2] = 3;
    mp1[5] = 6;

    for (iterator<int, int> b = mp1.begin(); b != mp1.end(); ++b) {
        std::cout << b.first() << " - " << b.second() << std::endl;
    }
    mp1.clear();
    if (mp1.empty()) {
        for (int i = 0; i < mp1.max_size(); i++) {
            mp1[i] = i + 1;
        }
    }
    mp1.swap(mp2);
    std::cout << "mp1 size: " << mp1.size() << std::endl;
    std::cout << "mp2 size: " << mp2.size() << std::endl;

    return 0;
}