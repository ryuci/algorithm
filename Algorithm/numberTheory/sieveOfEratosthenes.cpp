//
//  sieveOfEratosthenes.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 04/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "numberTheory.hpp"

VB isPrime;

static bool eratosthenes(int upto) {
    try {
        isPrime.assign(upto+1, false);
    } catch (std::length_error& e) {
        std::cout << e.what() << " requested too much momory. Aborting.\n";
        return false;
    }
    isPrime[0] = isPrime[1] = false;
    int sqrtn = int(sqrt(upto));
    for (int i = 2; i < sqrtn; ++i) {
        if (isPrime[i])
            for (int j = i*i; j <= upto; j += i)
                isPrime[i] = false;
    }
    return true;
}
void testEratosthenes() {
    double time;
    bool ret;
    
    startTimer();
    ret = eratosthenes(MILLION);
    time = stopTimerRet();
    std::cout << "eratosthenes(MILLION) in " << time << " ms\n";
    HR;

    startTimer();
    ret = eratosthenes(BILLION);
    time = stopTimerRet();
    std::cout << "eratosthenes(BILLION) in " << time << " ms\n";
    HR;

    startTimer();
    ret = eratosthenes(TRILLION);
    time = stopTimerRet();
    std::cout << "eratosthenes(TRILLION) in " << time << " ms\n";
    HR;

    std::cout << "ERATOSTHENES TEST PASS!\n";

}
