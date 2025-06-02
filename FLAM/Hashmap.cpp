#include<bits/stdc++.h>
using namespace std;
class MyHashMap {
private:
    vector<vector<pair<int, int>>> buckets;
    const int size = 1000; // Choose an appropriate size for the hash table

    int hash(int key) {
        return key % size;
    }
public:
    MyHashMap() {
        buckets.resize(size);
    }
    void put(int key, int value) {
        int index = hash(key);
        for (auto &pair : buckets[index]) {
            if (pair.first == key) {
                pair.second = value; 
                return;
            }
        }
        buckets[index].emplace_back(key, value);
    }
    int get(int key) {
        int index = hash(key);
        for (const auto &pair : buckets[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return -1;
    }
    void remove(int key) {
        int index = hash(key);
        auto &bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it); 
                return;
            }
        }
    }
};
int main(){
    string line;
    MyHashMap* obj = nullptr;
    while (getline(cin, line)) {
        if (line.empty())continue;
        if (line.back() == ';')line.pop_back();

        if (line.find("MyHashMap")==0) {
            obj = new MyHashMap();
        } else if (line.find("obj.put")==0) {
            int key, value;
            sscanf(line.c_str(), "obj.put(%d, %d)",&key,&value);
            obj->put(key, value);
        } else if (line.find("obj.get")==0) {
            int key;
            sscanf(line.c_str(), "obj.get(%d)",&key);
            cout << obj->get(key) << endl;
        } else if (line.find("obj.remove")==0) {
            int key;
            sscanf(line.c_str(), "obj.remove(%d)",&key);
            obj->remove(key);
        }
    }
    return 0;
}