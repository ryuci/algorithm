//
//  fightOrder.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 03/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "greedyMethod.hpp"
#include <set>

static int fightOrder(const VI& russian, const VI& korean) {
    int wins = 0;
    std::multiset<int> ratings(korean.begin(), korean.end());
    for (int i = 0; i < russian.size(); ++i) {
        if (*ratings.rbegin() < russian[i])
            ratings.erase(ratings.begin());
        else {
            ratings.erase(ratings.lower_bound(russian[i]));
            ++wins;
        }
    }
    return wins;
}

void testFightOrder() {
    
    startTimer();
    int ret = fightOrder(VI({3000, 2700, 2800, 2200, 2500, 2900}),
                    VI({2800, 2750, 2995, 1800, 2600, 2000}));
    double time = stopTimerRet();
    std::cout << "order() = " << ret <<  " in " << time << " ms\n";
    HR;
    std::cout << "FIGHT ORDER TEST PASS!\n";
}


