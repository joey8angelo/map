#include <iostream>
#include "unordered_map.cpp"
#include "iterator.cpp"

using std::cout;
using std::endl;

int main() {
    unordered_map<int, int> mp;
    
    for (int i = 0;i < 20; i++) {
        mp.insert(std::pair<int, int>(i, 0));
    }

    unordered_map<int, int> mp2(mp);

    for (unordered_map<int, int>::iterator b = mp2.begin(); b != mp2.end(); ++b) {
        cout << b.first() << " - "<< b.second() << endl;
    }

    return 0;
}