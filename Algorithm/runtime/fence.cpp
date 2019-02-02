//
//  fence.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 22/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"
#include <vector>

// Get maximum width of square. The width of each lumber in h is 1.
// O(n^2)
//
static int fenceBF(const std::vector<int>& h, bool logOn) {
    int ret = 0;
    int N = (int)h.size();
    for (int left = 0; left < N; ++left) {
        int minHeight = h[left];
        for (int right = left; right < N; ++right) {
            minHeight = std::min(minHeight, h[right]);
            ret = std::max(ret, (right - left + 1) * minHeight);
        }
        if (logOn)
            // TODO:1-23-2019: "\r" seems not working.
            std::cout << "\r" << ((double)left / N * 100) << "%";
    }
    if (logOn)
        std::cout << std::endl;
    return ret;
}

// Fence using divide and conquer.
// Solve T(n) by 2T(n/2) + O(n), where O(n) is time to solve
// the problem in overlapped area. T(n) is same to merge sort,
// so O(nlogn).
//
static int fenceDC(const std::vector<int>& h, int left, int right) {
    int ret = 0;
    // Base case. Only 1 lumber left.
    if (left == right) return h[left];
    // Divide
    int mid = (left + right) / 2;
    // Conquer
    ret = std::max(fenceDC(h, left, mid), fenceDC(h, mid + 1, right));
    // Calculate from the middle just in case max square may overlap both sides.
    // Will find max between current area in ret and that of square in the middle.
    int lo = mid, hi = mid + 1;
    int height = std::min(h[lo], h[hi]);
    // Compare against sqauare of [mid,mid+1].
    ret = std::max(ret, height);
    // Expand sqare until it covers all lumbers.
    // TODO:1-23-2019: I'm lost. Study again.
    while (left < lo || hi < right) {
        // Expand to higher direction between h[lo-1] and h[hi+1].
        if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
            ++hi;
            height = std::min(height, h[hi]);
        }
        else {
            --lo;
            height = std::min(height, h[lo]);
        }
        ret = std::max(ret, height * (hi - lo + 1));
    }
    return ret;
}

static std::vector<int> testCase1 = {7, 1, 5, 9, 6, 7, 3};
static std::vector<int> testCase2 = {1, 4, 4, 4, 4, 1, 1};
static std::vector<int> testCase3 = {1, 8, 2, 2};
static std::vector<int> testCase4;

// Result on iMac 3.5 GHz Intel Core i5, 8 GB 1600 MHz DDR3
//                          Case 1      Case 2      Case 3      Case 4
// N:                       7           7           4           20,000
// fenceBruteForce():       0.002 ms    0.001 ms    0.001 ms    1610.09 ms
// fenceDivideNConquer():   0.003 ms    0.001 ms    0.001 ms    3.935 ms
//
void testFence() {
    int ret;
    // Brute Force
    startTimer(); ret = fenceBF(testCase1, false); stopTimer(); assert(ret == 20);
    std::cout << "Test Case 1 Result: " << ret << std::endl;
    startTimer(); ret = fenceBF(testCase2, false); stopTimer(); assert(ret == 16);
    std::cout << "Test Case 2 Result: " << ret << std::endl;
    startTimer(); ret = fenceBF(testCase3, false); stopTimer(); assert(ret == 8);
    std::cout << "Test Case 3 Result: " << ret << std::endl;
    // Make it tough!
    for (int i = 0; i < 20000; i++)
        testCase4.push_back(rand() % 9999 + 1);
    startTimer(); ret = fenceBF(testCase4, false); stopTimer();
    std::cout << "Test Case 4 Result: " << ret << std::endl;

    // Divide & Conquer
    startTimer(); ret = fenceDC(testCase1, 0, (int)testCase1.size() - 1); stopTimer(); assert(ret == 20);
    std::cout << "Test Case 1 Result: " << ret << std::endl;
    startTimer(); ret = fenceDC(testCase2, 0, (int)testCase2.size() - 1); stopTimer(); assert(ret == 16);
    std::cout << "Test Case 2 Result: " << ret << std::endl;
    startTimer(); ret = fenceDC(testCase3, 0, (int)testCase3.size() - 1); stopTimer(); assert(ret == 8);
    std::cout << "Test Case 3 Result: " << ret << std::endl;
    startTimer(); ret = fenceDC(testCase4, 0, (int)testCase4.size() - 1); stopTimer();
    std::cout << "Test Case 4 Result: " << ret << std::endl;
}
