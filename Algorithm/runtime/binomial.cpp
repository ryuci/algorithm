//
//  binomial.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 23/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

// TODO:1-23-2019: Consider to add overflow checking.
// Recursive.
static long rBinomial(int n, int r) {
    if (r == 0 || n == r) return 1;
    return rBinomial(n - 1, r - 1) + rBinomial(n - 1, r);
}

// Non-Recursive.
static long nrBinomial(int n, int r) {
    long ret = 1;
    if (r == 0 || n == r) return 1;
    if (r > n - r) r = n - r;
    for (int i = 0; i < r; ++i) {
        ret *= (n - i);
        ret /= (i + 1);
    }
    return ret;
}

// Use memoization to take advantage of overlapping subproblems.
// To use cache, it's assumed always fn returns non negative.
// -1 will be used as cache empty.
static long cache[100][100];
static long dpBinomial(int n, int r) {
    if (r == 0 || n == r) return 1;
    if (cache[n][r] != -1)
        return cache[n][r];
    return cache[n][r] = dpBinomial(n - 1, r - 1) + dpBinomial(n - 1, r);
}

// Result on iMac 3.5 GHz Intel Core i5, 8 GB 1600 MHz DDR3
//                          Case 1      Case 2      Case 3
// N,R:                     5,3         25,12       40,23
// rBinomial():             0.016 ms    27.837 ms   26107.3 ms
// nrBinomial():            0.001 ms    0.001 ms    0.001 ms
// dpBinomial():            0.002 ms    0.002 ms    0.004 ms
//
void testBinomial() {
    // Recursive.
    long ret;
    startTimer(); ret = rBinomial(5, 3); stopTimer(); assert(ret == 10);
    std::cout << "Test Case 1 Result: " << ret << std::endl;
    startTimer(); ret = rBinomial(25, 12); stopTimer(); assert(ret == 5200300);
    std::cout << "Test Case 2 Result: " << ret << std::endl;
    startTimer(); ret = rBinomial(40, 12); stopTimer(); assert(ret == 5586853480);
    std::cout << "Test Case 3 Result: " << ret << std::endl;

    startTimer(); ret = nrBinomial(5, 3); stopTimer(); assert(ret == 10);
    std::cout << "Test Case 1 Result: " << ret << std::endl;
    startTimer(); ret = nrBinomial(25, 12); stopTimer(); assert(ret == 5200300);
    std::cout << "Test Case 2 Result: " << ret << std::endl;
    startTimer(); ret = nrBinomial(40, 12); stopTimer(); assert(ret == 5586853480);
    std::cout << "Test Case 3 Result: " << ret << std::endl;

    // Dynamic programming using memoization.
    // Trick. Works only when 2nd argument is 0 or -1.
    memset(cache, -1, sizeof(cache));
    startTimer(); ret = dpBinomial(5, 3); stopTimer(); assert(ret == 10);
    std::cout << "Test Case 1 Result: " << ret << std::endl;
    memset(cache, -1, sizeof(cache));
    startTimer(); ret = dpBinomial(25, 12); stopTimer(); assert(ret == 5200300);
    std::cout << "Test Case 2 Result: " << ret << std::endl;
    memset(cache, -1, sizeof(cache));
    startTimer(); ret = dpBinomial(40, 12); stopTimer(); assert(ret == 5586853480);
    std::cout << "Test Case 3 Result: " << ret << std::endl;
}
