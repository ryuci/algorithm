//
//  maxsum.cpp
//  Algorithm Xcode
//
//  Created by Choong-il Ryu on 31/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

typedef struct _ReturnType {
    double  time;
    int     val;
} ReturnType;

// Max Sum O(n^3)
//
ReturnType maxSum1(const std::vector<int>& a)
{
    ReturnType ret;
    startTimer();
    ret.val = std::numeric_limits<int>::min();
    
    for (int i = 0; i < a.size(); ++i) {
        for (int j = i; j < a.size(); ++j) {
            int sum = 0;
            for (int k = i; k <= j; ++k)
                sum += a[k];
            ret.val = std::max(sum, ret.val);
        }
    }
    ret.time = stopTimerRet();
    return ret;
}

// Max Sum O(n^2)
//
ReturnType maxSum2(const std::vector<int>& a)
{
    ReturnType ret;
    startTimer();
    ret.val = std::numeric_limits<int>::min();

    for (int i = 0; i < a.size(); ++i) {
        int sum = 0;
        for (int j = i; j < a.size(); ++j) {
            sum += a[j];
            ret.val = std::max(sum, ret.val);
        }
    }
    ret.time = stopTimerRet();
    return ret;
}

// Max Sum O(nlogn)
// Divide and Conquer + Greedy
//
int maxSum3(const std::vector<int>& a, int lo, int hi) {
    if (lo == hi)
        return a[lo];
    int mid = (lo + hi) / 2;
    int left = std::numeric_limits<int>::min();
    int right = std::numeric_limits<int>::min();
    int sum = 0;
    for (int i = mid; i >= lo; --i) {
        sum += a[i];
        left = std::max(left, sum);
    }
    sum = 0;
    for (int j = mid + 1; j <= hi; ++j) {
        sum += a[j];
        right = std::max(right, sum);
    }
    int single = std::max(maxSum3(a, lo, mid), maxSum3(a, mid + 1, hi));
    return std::max(left + right, single);
}

// Max Sum O(n)
// Dynamic Programming
//
ReturnType maxSum4(const std::vector<int>& a)
{
    ReturnType ret;
    int psum = 0;
    ret.val = 0;
    startTimer();
    for (int i = 0; i < a.size(); ++i) {
        psum = std::max(0, psum) + a[i];
        ret.val = std::max(psum, ret.val);
    }
    ret.time = stopTimerRet();
    return ret;
}


//
// TEST CASES
//

// Result on iMac 3.5 GHz Intel Core i5, 8 GB 1600 MHz DDR3 XCode Debug Run
//              maxSum1     maxSum2     maxSum3     maxSum4
// N=8:         0.003ms     0.002ms     0.001ms     0ms
// N=10000:     368s        255s        1.22ms      0.108ms
//
void testMaxSum() {
    std::vector<int> a = {-7, 4, -3, 6, 3, -8, 3, 4};
    ReturnType ret[4];
    
    ret[0] = maxSum1(a);
    assert(ret[0].val == 10);
    std::cout << "MAX SUM 1 TEST PASS IN " << ret[0].time << " MSEC!\n";

    ret[1] = maxSum2(a);
    assert(ret[1].val == 10);
    std::cout << "MAX SUM 2 TEST PASS IN " << ret[1].time << " MSEC!\n";

    startTimer();
    ret[2].val = maxSum3(a, 0, (int)a.size()-1);
    ret[2].time = stopTimerRet();
    assert(ret[2].val == 10);
    std::cout << "MAX SUM 3(D&C) TEST PASS IN " << ret[2].time << " MSEC!\n";

    ret[3] = maxSum4(a);
    assert(ret[3].val == 10);
    std::cout << "MAX SUM 4(DP) TEST PASS IN " << ret[3].time << " MSEC!\n";

    a.clear();
    for (int i = 0; i < 10000; ++i)
        a.push_back(rand() % 200 - 100);

    ret[0] = maxSum1(a);
    //assert(ret[0].val == 10);
    std::cout << "MAX SUM 1 TEST PASS IN " << ret[0].time << " MSEC!\n";
    
    ret[1] = maxSum2(a);
    assert(ret[1].val == ret[0].val);
    std::cout << "MAX SUM 2 TEST PASS IN " << ret[1].time << " MSEC!\n";
    
    startTimer();
    ret[2].val = maxSum3(a, 0, (int)a.size()-1);
    ret[2].time = stopTimerRet();
    assert(ret[2].val == ret[1].val);
    std::cout << "MAX SUM 3(D&C) TEST PASS IN " << ret[2].time << " MSEC!\n";

    ret[3] = maxSum4(a);
    assert(ret[3].val == ret[2].val);
    std::cout << "MAX SUM 4(DP) TEST PASS IN " << ret[3].time << " MSEC!\n";

}



