#include <iostream>
#include "map.cpp"
#include "iterator.cpp"

int main() {
    map<int, int> mp1, mp2;

    mp1.insert(std::pair<int, int>(1, 2));
    mp1.insert(std::pair<int, int>(3, 4));
    mp1.insert(std::pair<int, int>(5, 6));
    mp1.insert(std::pair<int, int>(7, 8));
    mp1.insert(std::pair<int, int>(7, 8));
    mp1.insert(std::pair<int, int>(7, 8));

    mp1[2];
    mp1.find(2).second() = 3;
    mp1[5] = 20;
    mp1[6] = 7;

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

    if (mp2.find(1001) != mp2.end())
        std::cout << mp2[1001] << std::endl;
    else
        std::cout << "could not find key 1001" << std::endl;

    if (mp2.find(5) != mp2.end())
        std::cout << mp2[5] << std::endl;
    else
        std::cout << "could not find key 5" << std::endl;

    std::cout << "key: " << mp2.find(5).first() << " value: " <<mp2.find(5).second() << std::endl;

    return 0;
}