# map and unordered_map

Two associated containers that are formed with a key value and a mapped value, allowing for fast retrieval of elements based on their key.
- [Map](#map)
	+ [map::at](#mapat)
	+ [map::begin](#mapbegin)
	+ [map::clear](#mapclear)
	+ [map::count](#mapcount)
	+ [map::emplace](#mapemplace)
	+ [map::empty](#mapempty)
	+ [map::end](#mapend)
	+ [map::erase](#maperase)
	+ [map::find](#mapfind)
	+ [map::insert](#mapinsert)
	+ [map::max_size](#mapmax_size)
	+ [map::operator[]](#mapoperator)
	+ [map::operator=](#mapoperator)
	+ [map::rbegin](#maprbegin)
	+ [map::rend](#maprend)
	+ [map::size](#mapsize)
	+ [map::swap](#mapswap)
- [Unordered_map](#unordered_map)
    + [unordered_map::at](#unordered_mapat)
    + [unordered_map::begin](#unordered_mapbegin)
    + [unordered_map::bucket](#unordered_mapbucket)
    + [unordered_map::bucket_count](#unordered_mapbucket_count)
    + [unordered_map::bucket_size](#unordered_mapbucket_size)
    + [unordered_map::clear](#unordered_mapclear)
    + [unordered_map::count](#unordered_mapcount)
    + [unordered_map::emplace](#unordered_mapemplace)
    + [unordered_map::empty](#unordered_mapempty)
    + [unordered_map::end](#unordered_mapend)
    + [unordered_map::erase](#unordered_maperase)
    + [unordered_map::find](#unordered_mapfind)
    + [unordered_map::insert](#unordered_mapinsert)
    + [unordered_map::load_factor](#unordered_mapload_factor)
    + [unordered_map::max_bucket_count](#unordered_mapmax_bucket_count)
    + [unordered_map::max_load_factor](#unordered_mapmax_load_factor)
    + [unordered_map::max_size](#unordered_mapmax_size)
    + [unordered_map::operator[]](#unordered_mapoperator)
    + [unordered_map::operator=](#unordered_mapoperator)
    + [unordered_map::rehash](#unordered_maprehash)
    + [unordered_map::size](#unordered_mapsize)
    + [unordered_map::swap](#unordered_mapswap)
# Map
Elements in map are ordered internally in an AVL tree allowing for logarithmic lookups/insertions.
## Member functions
### map::at
```c++
mapped_type& at(const key_type& k);
```
Returns a reference to the mapped value at key value k, throws out_of_range if key does not exist in the map
```c++
map<string, int> mp;

mp["Mars"] = 68;
mp.at("Mars") = 688;

cout << mp.at("Mars") << endl
```
output
```
688
```

### map::begin
```c++
iterator begin();
```
Returns an iterator to the first element in the map
```c++
map<char, int> mp;

mp['c'] = 100;
mp['b'] = 200;
mp['a'] = 300;

for (map<char, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
a - 300
b - 200
c - 100
```

### map::clear
```c++
void clear();
```
Removes all elements from the map and destroys them

```c++
map<int, int> mp;

mp[3] = 1;
mp[2] = 2;
mp[1] = 3;

for (map<int, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}

cout << endl;
mp.clear();

mp[10] = 20;

for (map<int, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
1 - 3
2 - 2
3 - 1

10 - 20
```


### map::count
```c++
int count(const key_type& k) const;
```
Returns the number of matches for key k, all map elements are unique so it will return either 0 or 1
```c++
map<char, int> mp;

mp['a'] = 101;
mp['c'] = 202;

cout << (mp.count('a') ? "a is in map" : "a not in map") << endl;
cout << (mp.count('b') ? "b is in map" : "b not in map") << endl;
```
output
```
a is in map
b not in map
```
### map::emplace
```c++
std::pair<iterator, bool> emplace(key_type, mapped_type);
```
Inserts a new element if the key is unique much like [map::insert](#mapinsert)
```c++
map<int, string> mp;

mp.emplace(5, "dog");
mp.emplace(3, "cat");
mp.emplace(10, "chicken");

for (map<int, string>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
3 - cat
5 - dog
10 - chicken
```
### map::empty
```c++
bool empty() const;
```
Returns whether map is empty
```c++
map<int, int> mp;

cout << (mp.empty() ? "empty" : "not empty") << endl;
mp[5] = 10;
cout << (mp.empty() ? "empty" : "not empty") << endl;
```
output
```
empty
not empty
```
### map::end
```c++
iterator end();
```
Returns an iterator referring to the past-the-end element in the map
```c++
map<char, int> mp;

mp['c'] = 100;
mp['b'] = 200;
mp['a'] = 300;

for (map<char, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
a - 300
b - 200
c - 100
```
### map::erase
```c++
void erase(iterator position);
void erase(const key_type& k);
```
Removes an element from the map
```c++
map<char, int> mp;

mp['a'] = 1;
mp['b'] = 2;
mp['c'] = 3;
mp['d'] = 4;
map<char, int>::iterator it = mp.find('c');
mp.erase(it);
mp.erase('a');

for (it = mp.begin(); it != mp.end(); ++it) {
	cout << it.first() << " - " << it.second() << endl;
}
```
output
```
b - 2
d - 4
```
### map::find
```c++
iterator find(const key_type& k);
```
Searches for an element with key k and returns an iterator to it, of none ar found returns iterator to [map::end](#mapend)
```c++
map<int, int> mp;

mp[10] = 20;

mp.find(10).second() = 30;

cout << mp.find(10).second() << endl;
```
output
```
30
```
### map::insert
```c++
void insert(std::pair<key_type, mapped_type>);
```
Inserts a new key value pair into the map if the key is unique
```c++
map<string, int> mp;

mp.insert(std::pair<string, int>("one", 1));
mp.insert(std::pair<string, int>("two", 2));
```
### map::max_size
```c++
itn max_size() const;
```
Returns the maximum size of the map
```c++
map<string, int> mp;
cout << mp.max_size() << endl;
```
output
```
1000
```
### map::operator[]
```c++
mapped_type& operator[](const key_type& k);
```
Returns the mapped value at the key k, if it does not exist it will create a new element with the key and default mapped_value
```c++
map<int, int> mp;

mp[0] = 10;
mp[1] = 11;
mp[2];
cout << mp[2] << endl;

for (map<int, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
0
0 - 10
1 - 11
2 - 0
```
### map::operator=
```c++
map& operator=(const map& x);
```
Assigns the contents of x into the map replacing its current content
```c++
map<int, int> mp, mp2;

mp[0] = 10;
mp[1] = 11;
mp[2];

mp2 = mp;
for (map<int, int>::iterator i = mp2.begin(); i != mp2.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
0 - 10
1 - 11
2 - 0
```
### map::rbegin
```c++
reverse_iterator rbegin();
```
Returns a reverse_iterator to the last element in the map
```c++
map<int, int> mp;

mp[0] = 10;
mp[1] = 11;
mp[2];

for (map<int, int>::reverse_iterator i = mp.rbegin(); i != mp.rend(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
2 - 0
1 - 11
0 - 10
```
### map::rend
```c++
reverse_iterator rend();
```
Returns a reverse_iterator to the past-the-end element of the map
```c++
map<int, int> mp;

mp[0] = 10;
mp[1] = 11;
mp[2];

for (map<int, int>::reverse_iterator i = mp.rbegin(); i != mp.rend(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
2 - 0
1 - 11
0 - 10
```
### map::size
```c++
int size() const;
```
Returns the size of the map
```c++
map<string, int> mp;

cout << mp.size() << endl;

mp["ball"] = 10;

cout << mp.size() << endl;
```
output
```
0
1
```
### map::swap
```c++
void swap(map& x);
```
Exchanges the content of the map with the content of x
```c++
map<string, int> mp, mp2;

mp["dog"] = 1;
mp["cat"] = 2;

mp2["tiger"] = 10;

mp2.swap(mp);

cout << "mp" << endl;
for (map<string, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}

cout << "mp2" << endl;
for (map<string, int>::iterator i = mp2.begin(); i != mp2.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
mp
tiger - 10
mp2
cat- 2
dog - 1
```

# Unordered_map
Elements are not stored in any particular order, the key value is hashed and placed into buckets. This allows, on average, constant time lookups/insertions.

### unordered_map::at
```c++
mapped_type& at(const key_type& k);
```
Returns a reference to the mapped value at key value k, throws out_of_range if key does not exist in the map
```c++
unordered_map<string, int> mp;

mp["Mars"] = 68;
mp.at("Mars") = 688;

cout << mp.at("Mars") << endl
```
output
```
688
```
### unordered_map::begin
```c++
iterator begin();
local_iterator begin(int n);
```
Returns an iterator to the first element in the map or local iterator to the first element in a bucket
```c++
unordered_map<char, int> mp;

mp['c'] = 100;
mp['b'] = 200;
mp['a'] = 300;

for (unordered_map<char, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
for (int i = 0; i < mp.bucket_count(); ++i) {
    cout << "bucket #" << i << ": ";
    for (unordered_map<char, int>::local_iterator l = mp.begin(i); l != mp.end(i); ++l){
        cout << l.second() << ", ";
    }
    cout << endl;
}
```
output
```
b - 200
c - 100
a - 300
bucket #0: 200, 
bucket #1: 100, 
bucket #2: 
bucket #3: 
bucket #4: 
bucket #5: 
bucket #6: 300,

```
### unordered_map::bucket
```c++
int bucket(const key_type& k) const;
```
Returns the bucket that k would be in
```c++
unordered_map<int, int> mp;

cout << mp.bucket(10) << endl;

mp[10] = 10;

cout << mp.bucket(10) << endl;
```
output
```
0
1
```
### unordered_map::bucket_count
```c++
int bucket_count() const;
```
Returns the number of buckets in the map
```c++
unordered_map<int, int> mp;
cout << "buckets: " << mp.bucket_count() << endl; 
cout << mp.bucket(10) << endl;

mp[10] = 10;

cout << "buckets: " << mp.bucket_count() << endl; 
cout << mp.bucket(10) << endl;
```
output
```
buckets: 1
0
buckets: 3
1
```
### unordered_map::bucket_size
```c++
int bucket_size(int n) const;
```
Returns the size of the bucket n
```c++
unordered_map<int, int> mp;

mp[10] = 10;

cout << "size: " << mp.bucket_size(mp.bucket(10)) << endl;
```
output
```
size: 1
```
### unordered_map::clear
```c++
void clear();
```
Removes all elements from the map and destroys them
```c++
unordered_map<char, int> mp;

mp['a'] = 5;
mp['b'] = 10;
mp['c'] = 20;

for (unordered_map<char, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
    cout << i.first() << " - " << i.second() << endl;
}
mp.clear();
for (unordered_map<char, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
    cout << i.first() << " - " << i.second() << endl;
}
```
output
```
b - 10
c - 20
a - 5
```
### unordered_map::count
```c++
int count(const key_type& k) const;
```
Returns the number of matches for key k, all map elements are unique so it will return either 0 or 1
```c++
unordered_map<char, int> mp;

mp['a'] = 101;
mp['c'] = 202;

cout << (mp.count('a') ? "a is in map" : "a not in map") << endl;
cout << (mp.count('b') ? "b is in map" : "b not in map") << endl;
```
output
```
a is in map
b not in map
```
### unordered_map::emplace
```c++
std::pair<iterator, bool> emplace(key_type, mapped_type);
```
Inserts a new element if the key is unique much like [unordered_map::insert](#unordered_mapinsert)
```c++
unordered_map<int, string> mp;

mp.emplace(5, "dog");
mp.emplace(3, "cat");
mp.emplace(10, "chicken");

for (unordered_map<int, string>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
3 - cat
10 - chicken
5 - dog
```
### unordered_map::empty
```c++
bool empty() const;
```
Returns whether map is empty
```c++
unordered_map<int, int> mp;

cout << (mp.empty() ? "empty" : "not empty") << endl;
mp[5] = 10;
cout << (mp.empty() ? "empty" : "not empty") << endl;
```
output
```
empty
not empty
```
### unordered_map::end
```c++
iterator end();
local_iterator end(int n);
```
Returns an iterator to the last element in the map or local iterator to the last element in a bucket
```c++
unordered_map<char, int> mp;

mp['c'] = 100;
mp['b'] = 200;
mp['a'] = 300;

for (unordered_map<char, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
for (int i = 0; i < mp.bucket_count(); ++i) {
    cout << "bucket #" << i << ": ";
    for (unordered_map<char, int>::local_iterator l = mp.begin(i); l != mp.end(i); ++l){
        cout << l.second() << ", ";
    }
    cout << endl;
}
```
output
```
b - 200
c - 100
a - 300
bucket #0: 200, 
bucket #1: 100, 
bucket #2: 
bucket #3: 
bucket #4: 
bucket #5: 
bucket #6: 300,

```
### unordered_map::erase
```c++
iterator erase(iterator position);
iterator erase(const key_type k);
```
Removes an element from the map
```c++
unordered_map<char, int> mp;

mp['a'] = 1;
mp['b'] = 2;
mp['c'] = 3;
mp['d'] = 4;
map<char, int>::iterator it = mp.find('c');
mp.erase(it);
mp.erase('a');

for (it = mp.begin(); it != mp.end(); ++it) {
	cout << it.first() << " - " << it.second() << endl;
}
```
output
```
b - 2
d - 4
```
### unordered_map::find
```c++
iterator find(const key_type& k);
```
Searches for an element with key k and returns an iterator to it, of none ar found returns iterator to [unordered_map::end](#unordered_mapend)
```c++
unordered_map<int, int> mp;

mp[10] = 20;

mp.find(10).second() = 30;

cout << mp.find(10).second() << endl;
```
output
```
30
```
### unordered_map::insert
```c++
std::pair<iterator, bool> insert(std::pair<key_type, mapped_type>);
```
Inserts a new key value pair into the map if the key is unique
```c++
unordered_map<string, int> mp;

mp.insert(std::pair<string, int>("one", 1));
mp.insert(std::pair<string, int>("two", 2));
```
### unordered_map::load_factor
```c++
double load_factor() const;
```
Returns the current load factor
load_factor = size / bucket_count
```c++
unordered_map<int, int> mp;

mp[10] = 10;

cout << mp.load_factor() << endl;
```
output
```
.333333
```
### unordered_map::max_bucket_count
```c++
int max_bucket_count() const;
```
Returns the maximum number of buckets the map can have
```c++
unordered_map<int, int> mp;

cout << mp.max_bucket_count() << endl;
```
output
```
357913941
```
### unordered_map::max_load_factor
```c++
double max_load_factor() const;
void max_load_factor(double z);
```
Set or get the max_load_factor
```c++
unordered_map<int, int> mp;

cout << mp.max_load_factor() << endl;

mp.max_load_factor(.80);

cout << mp.max_load_factor() << endl;
```
output
```
.75
.8
```
### unordered_map::max_size
```c++
int max_size() const;
```
Returns the maximum number of elements that the map can store
```c++
unordered_map<int, int> mp;

cout << mp.max_size() << endl;
```
output
```
357913941
```
### unordered_map::operator[]
```c++
mapped_type& operator[](const key_type& k);
```
Returns the mapped value at the key k, if it does not exist it will create a new element with the key and default mapped_value
```c++
unordered_map<int, int> mp;

mp[0] = 10;
mp[1] = 11;
mp[2];
cout << mp[2] << endl;

for (unordered_map<int, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
0
0 - 10
1 - 11
2 - 0
```
### unordered_map::operator=
```c++
unordered_map& operator=( const unordered_map& x);
```
Assigns the contents of x into the map replacing its current content
```c++
unordered_map<int, int> mp, mp2;

mp[0] = 10;
mp[1] = 11;
mp[2];

mp2 = mp;
for (unordered_map<int, int>::iterator i = mp2.begin(); i != mp2.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
0 - 10
1 - 11
2 - 0
```
### unordered_map::rehash
```c++
void rehash(int n);
```
Will rehash the container to nextPrime(n) increasing the amount of buckets, will remap all existing elements to their new buckets
nextPrime(n) worst case: (2n - 1)/2
```c++
unordered_map<int, int> mp;

mp.rehash(30);

cout << mp.bucket_count() << endl;
```
output
```
31
```
### unordered_map::size
```c++
int size() const;
```
Returns the number of elements in the map
```c++
unordered_map<int, int> mp;

cout << mp.size() << endl;

mp[10] = 10;
mp[20] = 20;
mp[30] = 30;

cout << mp.size() << endl;
```
output
```
0
3
```
### unordered_map::swap
```c++
void swap(unordered_map& x);
```
Exchanges the content of the map with the content of x
```c++
unordered_map<string, int> mp, mp2;

mp["dog"] = 1;
mp["cat"] = 2;

mp2["tiger"] = 10;

mp2.swap(mp);

cout << "mp" << endl;
for (unordered_map<string, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}

cout << "mp2" << endl;
for (unordered_map<string, int>::iterator i = mp2.begin(); i != mp2.end(); ++i) {
	cout << i.first() << " - " << i.second() << endl;
}
```
output
```
mp
tiger - 10
mp2
cat - 2
dog - 1
```
