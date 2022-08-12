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

    for (unordered_map<int, int>::iterator i = mp2.begin(); i != mp2.end(); ++i) {
        cout << i.first() << " - "<< i.second() << endl;
    }

    for (int i = 0; i < mp2.bucket_count(); i++) {
        cout << "bucket #" << i << " contains: ";
        for (unordered_map<int, int>::local_iterator j = mp2.begin(i); j != mp2.end(i); ++j) {
            cout << j.first() << " " << j.second() << endl;
        }
    }

    return 0;
}