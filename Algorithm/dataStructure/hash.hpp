//
//  hash.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef hash_hpp
#define hash_hpp
#include <iostream>
#include <deque>
#include <sstream>

template <typename V>
struct HashNode
{
    // Key is assumed to non-negative since negative will be used for special cases.
    int key;
    V value;
    HashNode(int _key, V _value) : key(_key), value(_value) {};
};

template <typename V>
class HashMap {
protected:
    std::deque<HashNode<V>> _arr;
    int _capacity;
    static const int _EMPTY = -1;
    static const int _DELETED = -2;

    inline int hashCode(int key) { return key % _capacity; }

    // Used to make generic class that selectively supports one of linear probing,
    // quadradic probing, and double hashing.
    // Note how member function pointer is declared.
    bool (HashMap::*putter)(int,V);
    V (HashMap::*getter)(int);
    bool (HashMap::*remover)(int);
    
    // Insert - returns true if successful.
    //
    bool insert_linear_probing(int key, V value) {
        int deletedIndex = _DELETED;
        int index = hashCode(key);
        for (int i = 0; i < _capacity; i++) {
            // TODO:1-26-2019: Very confusing. We should comapre _arr[hashCode(key)].key,
            //                 not _arr[key]. Tread carefully.
            //
            if (_arr[index].key == _EMPTY || _arr[index].key == key) {
                // Hit
                _arr[index] = HashNode<V>(key, value);
                return true;
            }
            else if (_arr[index].key == _DELETED) {
                // Defer decision because key may be in one of following cells.
                deletedIndex = index;
            }
            std::cerr << "Collision in putter!\n";
            index = ++index % _capacity;
        }
        // Searched all over the hash map and we have available deleted cell.
        // Use it.
        if (deletedIndex != _DELETED) {
            _arr[deletedIndex] = HashNode<V>(key, value);
            return true;
        }
        // Full. No empty or deleted cell.
        std::cerr << "Hash Map Full!!\n";
        return false;
    };
    bool insert_quadratic_probing(int key, V value) { return false; };
    bool insert_double_hashing(int key, V value) { return false; };
    
    // Get - returns value if successful.
    // What if not successful? Read TODO:1-26-2019.
    //
    V get_linear_probing(int key) {
        int index = hashCode(key);
        for (int i = 0; i < _capacity; i++) {
            if (_arr[index].key == key) {
                // Hit
                return _arr[index].value;
            }
            else if (_arr[index].key == _EMPTY) {
                // End of search.
                // TODO:1-26-2019: I need to return invalid value here.
                //                 I don't want to use reference argument to get value and
                //                 pass/fail status at the same time.
                //                 Want to use optional. Shall I change compiler to C++17?
                //                 When <V> == <int>, V() == 0. Could cause problem in caller's side if 0 is meaningful.
                //                 WARNING!!!WARNING!!!WARNING!!!
                return V();
            }
            std::cout << "Collision in getter!\n";
            index = ++index % _capacity;
        }
        // Searched all over the hash map and we don't find the key.
        std::cout << "Searched all for nothing!!\n";
        return V();
    };
    V get_quadratic_probing(int key) { return V(); };
    V get_double_hashing(int key) { return V(); };
    
    // Remove - returns true if successful.
    //
    bool remove_linear_probing(int key) {
        int index = hashCode(key);
        for (int i = 0; i < _capacity; i++) {
            if (_arr[index].key == key) {
                // Hit
                // Shall not set key to _EMPTY, which will disrupt putter and getter.
                // Ex: 3 4 5 -> 3 _EMPTY 5: Can't find 5 during collision handling.
                //     3 4 5 -> 3 _DELETED 5: Collision handling will keep searching upto 5.
                _arr[index].key = _DELETED;
                //_arr[index].value = V();
                return true;
            }
            else if (_arr[index].key == _EMPTY) {
                // End of search.
                return false;
            }
            std::cout << "Collision in remover!\n";
            index = ++index % _capacity;
        }
        // Searched all over the hash map and we don't find the key.
        std::cout << "Searched all for nothing!!\n";
        return false;
    };
    bool remove_quadratic_probing(int key) { return false; };
    bool remove_double_hashing(int key) { return false; };

public:
    HashMap(int capacity = 163, std::string mode="linear probing") {
        _capacity = capacity;
        _arr.assign(_capacity, HashNode<V>{_EMPTY, 0});
        if (mode == "quadratic probing") {
            putter = &HashMap::insert_quadratic_probing;
            getter = &HashMap::get_quadratic_probing;
        }
        else if (mode == "double hashing") {
            putter = &HashMap::insert_double_hashing;
            getter = &HashMap::get_double_hashing;
        }
        else {
            // Default is linear probing.
            putter = &HashMap::insert_linear_probing;
            getter = &HashMap::get_linear_probing;
            remover = &HashMap::remove_linear_probing;
        }
    }
    
    bool insert(int key, V value) { return (this->*putter)(key, value); };
    V get(int key) { return (this->*getter)(key); };
    bool remove(int key) { return (this->*remover)(key); };
    
    std::string toString() {
        std::stringstream ret;
        for (int i = 0; i < _capacity; i++) {
            ret << i << "(" ;
            if (_arr[i].key == _EMPTY) ret << "E";
            else if (_arr[i].key == _DELETED) ret << "D";
            else ret << _arr[i].key;
            ret << "," << _arr[i].value << ")\n";
        };
        return ret.str();
    };
};

void testHash();

#endif /* hash_hpp */
