//
//  rshash.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 25/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "rshash.hpp"

void testRsHashInsert(RsHashMap<int>& hm, int key, int value) {
    std::cout << "Insert (" << key << "," << value << ")\n";
    hm.insert(key, value);
    std::cout << "Hash Contents:\n" << hm.toString();
}

void testRsHash() {
    RsHashMap<int> hm(1);
    
    // Setter and getter test.
    testRsHashInsert(hm, 25, 1); assert(hm.get(25) == 1); std::cout << "---\n";
    testRsHashInsert(hm, 13, 2); assert(hm.get(13) == 2); std::cout << "---\n";
    testRsHashInsert(hm, 16, 3); assert(hm.get(16) == 3); std::cout << "---\n";
    testRsHashInsert(hm, 15, 4); assert(hm.get(15) == 4); std::cout << "---\n";
    testRsHashInsert(hm, 7, 5); assert(hm.get(7) == 5); std::cout << "---\n";
    testRsHashInsert(hm, 28, 6); assert(hm.get(28) == 6); std::cout << "---\n";
    testRsHashInsert(hm, 31, 7); assert(hm.get(31) == 7); std::cout << "---\n";
    testRsHashInsert(hm, 20, 8); assert(hm.get(20) == 8); std::cout << "---\n";
    testRsHashInsert(hm, 1, 9); assert(hm.get(1) == 9); std::cout << "---\n";
    testRsHashInsert(hm, 38, 10); assert(hm.get(38) == 10); std::cout << "---\n";
    std::cout << "SETTET & GETTER TEST PASS.\n---\n";
    
    // Overwrite test.
    testRsHashInsert(hm, 38, 11); assert(hm.get(38) == 11); std::cout << "---\n";
    testRsHashInsert(hm, 16, 12); assert(hm.get(16) == 12); std::cout << "---\n";
    std::cout << "OVERWRITE TEST PASS.\n---\n";
    
    // Read non-existing key.
    // TODO:1-26-2019: I need to return invalid value here.
    //                 I don't want to use reference argument to get value and pass/fail status at the same time.
    //                 Want to use optional. Shall I change compiler to C++17?
    //                 When <V> == <int>, V() == 0. Could cause problem in caller's side if 0 is meaningful.
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

// Result on iMac 3.5 GHz Intel Core i5, 8 GB 1600 MHz DDR3
//              Case 1      Case 2      Case 3      Case 4      Case 5
// N:           1           Seq 1M      Rand 1M     Seq 100M    Rand 100M
// O(N):        0.023ms     121.984ms   163.597ms   14,611.1ms  16,876.2ms
// O1/O(N)/N:   1           188.549     140.589     157.415     136.287
//
void testRsHashO1() {
    // O(1) test. Will resizable hash really show O(1) on average?
    //
    std::cout << "HASH ONCE\n";
    RsHashMap<int> hm(1);
    startTimer();
    hm.insert(1, 1);
    double O1 = stopTimerRet();
    std::cout << "O1 = " << O1 << " ms\n";
    std::cout << "---\n";
    
    // Sequatially insert 1M numbers. Too fast.
    //
    std::cout << "HASH SEQ 1M\n";
    const int M = 1000000;
    int count = M;
    startTimer();
    for (int i = 2; i <= count; i++) {
        hm.insert(i, 1);
    }
    double O_n = stopTimerRet();
    std::cout << "O_n = " << O_n << " ms\n";
    std::cout << "O_n/n = " << O_n / count << " ms\n";
    std::cout << "O1 = " << O1 << " ms\n";
    std::cout << "O1/(O_n/n) = " << O1 / O_n * count  << "\n";
    //std::cout << "Hash Contents:\n" << hm.toString();
    std::cout << "---\n";

    // Now try 1M random numbers.
    // TODO:1-27-2019: rand() % 100*M may not show uniform distribution.
    //                 Might need to use std::uniform_int_distribution.
    std::cout << "HASH RANDOM 1M\n";
    count = M;
    startTimer();
    for (int i = 2; i <= count; i++) {
        hm.insert(rand() % count , 1);
    }
    O_n = stopTimerRet();
    std::cout << "O_n = " << O_n << " ms\n";
    std::cout << "O_n/n = " << O_n / count << " ms\n";
    std::cout << "O1 = " << O1 << " ms\n";
    std::cout << "O1/(O_n/n) = " << O1 / O_n * count  << "\n";
    //std::cout << "Hash Contents:\n" << hm.toString();
    std::cout << "---\n";
    
    // Now try 100M sequential numbers.
    //
    std::cout << "HASH SEQ 100M\n";
    count = 100 * M;
    startTimer();
    for (int i = 2; i <= count; i++) {
        hm.insert(i, 1);
    }
    O_n = stopTimerRet();
    std::cout << "O_n = " << O_n << " ms\n";
    std::cout << "O_n/n = " << O_n / count << " ms\n";
    std::cout << "O1 = " << O1 << " ms\n";
    std::cout << "O1/(O_n/n) = " << O1 / O_n * count  << "\n";
    //std::cout << "Hash Contents:\n" << hm.toString();
    std::cout << "---\n";

    // Now try 100M random numbers.
    //
    // TODO:1-27-2019: rand() % 100*M may not show uniform distribution.
    //                 Might need to use std::uniform_int_distribution.
    std::cout << "HASH RANDOM 100M\n";
    count = 100 * M;
    startTimer();
    for (int i = 2; i <= count; i++) {
        hm.insert(rand() % 100*M , 1);
    }
    O_n = stopTimerRet();
    std::cout << "O_n = " << O_n << " ms\n";
    std::cout << "O_n/n = " << O_n / count << " ms\n";
    std::cout << "O1 = " << O1 << " ms\n";
    std::cout << "O1/(O_n/n) = " << O1 / O_n * count  << "\n";
    //std::cout << "Hash Contents:\n" << hm.toString();
    std::cout << "---\n";

}
