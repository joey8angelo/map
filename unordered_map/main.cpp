#include <iostream>
#include <string>
#include "unordered_map.cpp"
#include "iterator.cpp"

using std::cout;
using std::endl;
using std::string;

int main() {

    {
        unordered_map<string, int> mp;
        mp["Mercury"] = 89;
        mp["Venus"] = 226;
        mp["Earth"] = 366;
        mp["Mars"] = 688;
        mp["Jupiter"] = 4334;
        mp["Saturn"] = 10760;
        mp["Uranus"] = 30688;

        unordered_map<string, int> mp2(mp);
        mp.clear();

        mp2.emplace("Neptune", 60191);

        for (unordered_map<string, int>::iterator i = mp2.begin(); i != mp2.end(); ++i) {
            i.second() -= 1;
            cout << i.first() << ": " << i.second() << endl;
        }
    }
    {
        unordered_map<string, string> mp;
        for (int i = 0; i < 50; i++) {
            mp[std::to_string(i)] = std::to_string(i);
        }

        mp.find("30").second() = "value at key \"30\" is this string";
        mp.erase(mp.find("30"));
        cout << "30 would have been in bucket #" << mp.bucket("30") << endl;

        for (int i = 0; i < mp.bucket_count(); i++) {
            cout << "bucket #" << i << ": ";
            for (unordered_map<string, string>::local_iterator l = mp.begin(i); l != mp.end(i); ++l) {
                cout << l.second() << ", ";
            }
            cout << endl;
        }

        cout << "key \"41\" - " << mp.at("41") << endl;
    }
    return 0;
}