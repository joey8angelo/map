#include <iostream>
#include <string>
#include "unordered_map.cpp"
#include "iterator.cpp"

using std::cout;
using std::endl;
using std::string;

int main() {
    unordered_map<string, string> mp;
    
    for (int i = 0;i < 20; i++) {
        mp.insert(std::pair<string, string>(std::to_string(i), "Hello"));
    }

    unordered_map<string, string> mp2(mp);
    mp.clear();
    mp["one"] = "two";
    mp["two"];
    mp["two"] = "three";

    for (unordered_map<string, string>::iterator i = mp.begin(); i != mp.end(); ++i) {
        cout << i.first() << " - "<< i.second() << endl;
    }

    for (unordered_map<string, string>::iterator i = mp2.begin(); i != mp2.end(); ++i) {
        cout << i.first() << " - "<< i.second() << endl;
    }

    mp2.find("5").second() = "Hello #5";

    for (int i = 0; i < mp2.bucket_count(); i++) {
        cout << "bucket #" << i << " contains: ";
        for (unordered_map<string, string>::local_iterator j = mp2.begin(i); j != mp2.end(i); ++j) {
            cout << j.first() << "-" << j.second() << ", ";
        }
        cout << endl;
    }

    return 0;
}