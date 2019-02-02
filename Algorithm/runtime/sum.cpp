//
//  sum.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

// O(N)
int sumRecursive(int n) {
    if (n == 1)
        return 1;
    return n + sumRecursive(n - 1);
}

// O(logN)
int sumDC(int n) {
    if (n == 1)
        return 1;
    if (n % 2 == 1)
        // When n is odd and not dividable.
        return n + sumDC(n - 1);
    return 2 * sumDC(n/2) + (n/2)*(n/2);
}

//
// TEST CASES
//
void testSum() {

    startTimer();
    int ret = sumRecursive(10000);
    double time = stopTimerRet();
    std::cout << "sumRecursive(10000) = " << ret << " in " << time << " ms\n";;
    assert(ret == 50005000);
    std::cout << "--\n";
    
    startTimer();
    ret = sumDC(10000);
    time = stopTimerRet();
    std::cout << "sumDC(10000) = " << ret << " in " << time << " ms\n";;
    assert(ret == 50005000);
    std::cout << "--\n";

    std::cout << "SUM TEST PASS!\n";
}
