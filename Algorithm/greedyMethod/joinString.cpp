//
//  joinString.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 03/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "greedyMethod.hpp"
#include <queue>

static int concat(const VI& lengths) {
    std::priority_queue<int, VI, std::greater<int>> pq;
    for (int i = 0; i < lengths.size(); ++i)
        pq.push(lengths[i]);
    int ret = 0;
    while (pq.size() > 1) {
        int min1 = pq.top(); pq.pop();
        int min2 = pq.top(); pq.pop();
        pq.push(min1 + min2);
        ret += min1 +min2;
    }
    return ret;
}

void testConcat() {
    VI s1 = {2,2,4};
    VI s2 = {3,1,3,4,1};
    VI s3 = {1,1,1,1,1,1,1,2};
    int ret;
    double time;

    startTimer();
    ret = concat(s1);
    time = stopTimerRet();
    std::cout << "concat(s1) = " << ret <<  " in " << time << " ms\n";
    assert(ret == 12);
    HR;
    
    startTimer();
    ret = concat(s2);
    time = stopTimerRet();
    std::cout << "concat(s2) = " << ret <<  " in " << time << " ms\n";
    assert(ret == 26);
    HR;

    startTimer();
    ret = concat(s3);
    time = stopTimerRet();
    std::cout << "concat(s3) = " << ret <<  " in " << time << " ms\n";
    assert(ret == 27);
    HR;

    std::cout << "CONCAT TEST PASS!\n";
}

