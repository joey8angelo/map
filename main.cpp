#include <iostream>
#include "map.cpp"

int main() {
    map<int, int> mp;

    for (int i = 0; i < 1005; i++) {
        mp.insert(std::pair<int, int>(i, 0));
        std::cout << mp.size() << std::endl;
    }
    
    return 0;
}