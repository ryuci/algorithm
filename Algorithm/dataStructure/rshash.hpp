//
//  rshash.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 25/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef rshash_hpp
#define rshash_hpp

#include "hash.hpp"
#include <iostream>
#include <deque>
#include <sstream>

// Resizable Hash
// Inherit HashMap in linear probing mode.
//
template <typename V>
class RsHashMap : public HashMap<V> {
protected:
    int _size;
    
    //inline int hashCode(int key) { return key % _capacity; }
    void resize() {
        // Make bigger hash map.
        RsHashMap<V> newHm(HashMap<V>::_capacity * 2);
        // Move (K,V) from old to new hash map.
        // Note that K % _capacityOld and K % _capacityNew are not necessarily same.
        for (int i = 0; i < HashMap<V>::_capacity; i++) {
            if (HashMap<V>::_arr[i].key != HashMap<V>::_DELETED &&
                HashMap<V>::_arr[i].key != HashMap<V>::_EMPTY)
                
                newHm.insert(HashMap<V>::_arr[i].key, HashMap<V>::_arr[i].value);
        }
        HashMap<V>::_arr = newHm._arr;
        HashMap<V>::_capacity *= 2;
    }
    
public:
    // Start from capacity 1 hashmap.
    RsHashMap(int capacity) : HashMap<V>(capacity) {
        _size = 0;
    }
    
    // Insert - returns true if successful.
    //
    bool insert(int key, V value) {
        int deletedIndex = HashMap<V>::_DELETED;
        int index = HashMap<V>::hashCode(key);
        for (int i = 0; i < HashMap<V>::_capacity; i++) {
            // TODO:1-26-2019: Very confusing. We should comapre _arr[hashCode(key)].key,
            //                 not _arr[key]. Read carefully.
            //
            if (HashMap<V>::_arr[index].key == HashMap<V>::_EMPTY || HashMap<V>::_arr[index].key == key) {
                // Hit
                HashMap<V>::_arr[index] = HashNode<V>(key, value);
                if (++_size == HashMap<V>::_capacity) resize();
                return true;
            }
            else if (deletedIndex == HashMap<V>::_DELETED &&
                     HashMap<V>::_arr[index].key == HashMap<V>::_DELETED) {
                // Defer decision because key may be in one of following cells.
                deletedIndex = index;
            }
            std::cerr << "Collision in putter!\n";
            index = ++index % HashMap<V>::_capacity;
        }
        // Searched all over the hash map and we have available deleted cell.
        // Use it.
        if (deletedIndex != HashMap<V>::_DELETED) {
            HashMap<V>::_arr[deletedIndex] = HashNode<V>(key, value);
            if (++_size == HashMap<V>::_capacity) resize();
            return true;
        }
        // Should not be reachable. Let's test it.
        assert(0);
        // Full. No empty or deleted cell.
        //_capacity *= 2;
        //_arr.resize(_capacity, HashNode<V>{_EMPTY, 0});
        //std::cerr << "Hash Map Full!! Resized to " << _capacity << ".\n";
        return false;
    };
    
    V get(int key) {
        return HashMap<V>::get(key);
    }
    
    bool remove(int key) {
        bool ret = HashMap<V>::remove(key);
        if (ret == true) --_size;
        return ret;
    }
    
    std::string toString() {
        std::stringstream ret;
        for (int i = 0; i < HashMap<V>::_capacity; i++) {
            ret << i << "(" ;
            if (HashMap<V>::_arr[i].key == HashMap<V>::_EMPTY) ret << "E";
            else if (HashMap<V>::_arr[i].key == HashMap<V>::_DELETED) ret << "D";
            else ret << HashMap<V>::_arr[i].key;
            ret << "," << HashMap<V>::_arr[i].value << ")\n";
        };
        return ret.str();
    };

};

void testRsHash();
void testRsHashO1();

#endif /* rshash_hpp */
