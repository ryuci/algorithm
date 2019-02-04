//
//  heatingOrder.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 03/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "greedyMethod.hpp"
#include <set>

static int heatingOrder(int m[], int e[], int n) {
    std::vector<std::pair<int,int>> order;
    for (int i = 0; i < n; ++i) {
        order.push_back({-e[i], i});
    }
    // Longer eating time first.
    sort(order.begin(), order.end());
    int ret = 0, beginEat = 0;
    for (int i = 0; i < n; ++i) {
        // 
        int box = order[i].second;
        beginEat += m[box];
        ret = std::max(ret, beginEat + e[box]);
    }
    return ret;
}

void testHeatingOrder() {
    int m1[] = {2,2,2};
    int e1[] = {2,2,2};
    int m2[] = {1,2,3};
    int e2[] = {1,2,1};

    startTimer();
    int ret = heatingOrder(m1, e1, 3);
    double time = stopTimerRet();
    std::cout << "heatingOrder(m1, e1, 3) = " << ret <<  " in " << time << " ms\n";
    assert(ret == 8);
    HR;
    
    startTimer();
    ret = heatingOrder(m2, e2, 3);
    time = stopTimerRet();
    std::cout << "heatingOrder(m2, e2, 3) = " << ret <<  " in " << time << " ms\n";
    assert(ret == 7);
    HR;

    std::cout << "HEATING ORDER TEST PASS!\n";
}

