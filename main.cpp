#include <iostream>
#include "map.cpp"
#include "iterator.cpp"

using std::cout;
using std::endl;

int main() {
    map<int, int> mp1, mp2;

    mp1.insert(std::pair<int, int>(1, 2));
    mp1.insert(std::pair<int, int>(3, 4));
    mp1.insert(std::pair<int, int>(5, 6));
    mp1.insert(std::pair<int, int>(7, 8));
    mp1.insert(std::pair<int, int>(7, 8));

    if (!mp1.emplace(7, 8).second)
        cout << "key 7 already in map" << endl;
    else
        cout << "7, 8 emplaced" << endl;

    if (!mp1.emplace(8, 9).second)
        cout << "key 8 already in map" << endl;
    else
        cout << "8, 9 emplaced" << endl;

    mp1[2];
    mp1.find(2).second() = 3;
    mp1[5] = 20;
    mp1[6] = 7;

    for (iterator<int, int> b = mp1.begin(); b != mp1.end(); ++b) {
        cout << b.first() << " - " << b.second() << endl;
    }
    mp1.clear();
    if (mp1.empty()) {
        for (int i = 0; i < mp1.max_size(); i++) {
            mp1[i] = i + 1;
        }
    }

    mp1.swap(mp2);
    cout << "mp1 size: " << mp1.size() << endl;
    cout << "mp2 size: " << mp2.size() << endl;

    if (mp2.find(1001) != mp2.end())
        cout << mp2[1001] << endl;
    else
        cout << "could not find key 1001" << endl;

    if (mp2.find(5) != mp2.end())
        cout << mp2[5] << endl;
    else
        cout << "could not find key 5" << endl;

    cout << mp2.find(5).first() << endl;

    mp1 = mp2;

    cout << mp1.find(5).first() << endl;

    mp1 = map<int, int>();
    mp1[4];

    try {
        cout << mp1.at(5) << endl;
    } catch(std::out_of_range& m) {
        cout << "Out of range: " << m.what() << endl;
    }

    try {
        mp1.at(4) = 10;
        cout << "insert " << mp1.at(4) << " at key 4 with map::at" << endl;
    } catch(std::out_of_range& m) {
        cout << "Out of range: " << m.what() << endl;
    }

    return 0;
}