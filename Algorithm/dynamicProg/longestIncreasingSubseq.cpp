//
//  longestIncreasingSubseq.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 02/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"

// Objective: Find the longest increasing subsequence.
//
class LIS {
public:
    VI _cache;
    VI _seq;
    
    LIS(const VI& seq) : _seq(seq) {
        _cache = VI(seq.size(), -1);
    }
    
    int search(const VI& seq) {
        if (seq.empty()) return 0;
        int ret = 0;
        for (int i = 0; i < seq.size(); ++i) {
            VI tmp;
            for (int j = i+1; j < seq.size(); ++j) {
                if (seq[i] < seq[j])
                    tmp.push_back(seq[j]);
            }
            ret = std::max(ret, 1 + search(tmp));
        }
        return ret;
    }
    //
    int searchDP(const VI& seq) {
        int ret = 0;
        return ret;
    }

    int search() { return search(_seq); }
    int searchDP() { return searchDP(_seq); }
};

void testLIS() {
    VI s1 = {3, 10, 2, 1, 20}; // {3, 10, 20}
    VI s2 = {3, 2}; // 3 or 1
    VI s3 = {50, 3, 10, 7, 40, 80}; // {3, 7, 40, 80}
    
    startTimer();
    LIS lis1(s1);
    int ret = lis1.search();
    double time = stopTimerRet();
    std::cout << "lis1.search() = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 3);
    HR;
    
    startTimer();
    LIS lis2(s2);
    ret = lis2.search();
    time = stopTimerRet();
    std::cout << "lis2.search() = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 1);
    HR;

    startTimer();
    LIS lis3(s3);
    ret = lis3.search();
    time = stopTimerRet();
    std::cout << "lis3.search() = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 4);
    HR;

    std::cout << "LIS TEST PASS!\n";
    
}
