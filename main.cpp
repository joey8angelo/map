#include <iostream>
#include "map.cpp"
#include "iterator.cpp"

int main() {
    map<int, int> mp1;

    mp1.insert(std::pair<int, int>(1, 2));
    mp1.insert(std::pair<int, int>(3, 4));
    mp1.insert(std::pair<int, int>(5, 7));
    mp1.insert(std::pair<int, int>(7, 8));

    mp1[2] = 3;
    mp1[5] = 6;

    for (iterator<int, int> b = mp1.begin(); b != mp1.end(); ++b) {
        std::cout << b.first() << " - " << b.second() << std::endl;
    }
    
    
    return 0;
}