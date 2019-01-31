//
//  hash.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef hash_cpp
#define hash_cpp
#include "helper.hpp"
#include "hash.hpp"

void testHashInsert(HashMap<int>& hm, int key, int value) {
    std::cout << "Insert (" << key << "," << value << ")\n";
    hm.insert(key, value);
    std::cout << "Hash Contents:\n" << hm.toString();
}

void testHash() {
    HashMap<int> hm(13);
    
    // Setter and getter test.
    testHashInsert(hm, 25, 1); assert(hm.get(25) == 1); std::cout << "---\n";
    testHashInsert(hm, 13, 2); assert(hm.get(13) == 2); std::cout << "---\n";
    testHashInsert(hm, 16, 3); assert(hm.get(16) == 3); std::cout << "---\n";
    testHashInsert(hm, 15, 4); assert(hm.get(15) == 4); std::cout << "---\n";
    testHashInsert(hm, 7, 5); assert(hm.get(7) == 5); std::cout << "---\n";
    testHashInsert(hm, 28, 6); assert(hm.get(28) == 6); std::cout << "---\n";
    testHashInsert(hm, 31, 7); assert(hm.get(31) == 7); std::cout << "---\n";
    testHashInsert(hm, 20, 8); assert(hm.get(20) == 8); std::cout << "---\n";
    testHashInsert(hm, 1, 9); assert(hm.get(1) == 9); std::cout << "---\n";
    testHashInsert(hm, 38, 10); assert(hm.get(38) == 10); std::cout << "---\n";
    std::cout << "SETTET & GETTER TEST PASS.\n---\n";

    // Overwrite test.
    testHashInsert(hm, 38, 11); assert(hm.get(38) == 11); std::cout << "---\n";
    testHashInsert(hm, 16, 12); assert(hm.get(16) == 12); std::cout << "---\n";
    std::cout << "OVERWRITE TEST PASS.\n---\n";

    // Read non-existing key.
    // TODO:1-26-2019: I need to return invalid value here. Code will be messy.
    //                 Want to use optional. Shall change compiler to C++17?
    //                 When <V> == <int>, V() == 0. Could cause problem in caller's side.
    //                 WARNING!!!WARNING!!!WARNING!!!
    assert(hm.get(0) == 0); std::cout << "---\n";
    assert(hm.get(2343) == 0); std::cout << "---\n";
    assert(hm.get(18338242) == 0); std::cout << "---\n";
    std::cout << "READ NON-EXISTING KEY TEST PASS.\n---\n";

    // Remove
    assert(hm.remove(0) == false); std::cout << "---\n";
    assert(hm.remove(2343) == false); std::cout << "---\n";
    assert(hm.remove(1) == true); std::cout << "Hash Contents:\n" << hm.toString(); std::cout << "---\n";
    // Check if it follows 12, 0, _DELETED, 2, 3, 4, 5, 6.
    assert(hm.get(38) == 11); std::cout << "Hash Contents:\n" << hm.toString(); std::cout << "---\n";
    std::cout << "REMOVE TEST PASS.\n---\n";
}


#endif /* hash_cpp */
