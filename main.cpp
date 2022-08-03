#include <iostream>
#include "map.cpp"

int main() {
    map<int, int> mp1;

    mp1.insert(std::pair<int, int>(1, 2));
    mp1.insert(std::pair<int, int>(3, 4));
    mp1.insert(std::pair<int, int>(5, 6));
    mp1.insert(std::pair<int, int>(7, 8));

    std::cout << mp1[1] << std::endl;
    mp1[2] = 5;
    std::cout << mp1[2] << std::endl;
    std::cout << mp1[3] << std::endl;
    std::cout << mp1[4] << std::endl;
    
    
    return 0;
}