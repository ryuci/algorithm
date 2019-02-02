//
//  tiling.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 02/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"

// Objective: Get # of tiling method for 2xN area filled with 1x2 tiles.
//
class Tiling {
public:
    const int _MAX = 100;
    VI _cache;
    
    Tiling() {
        _cache = VI(_MAX, -1);
    }
    
    int tiling(int width) {
        if (width <= 1) return 1;
        // Trick: ret is reference to the element in cache. Cache will be updaated
        // by ret = ... in return statement below.
        int& ret = _cache[width];
        if (ret != -1)
            return _cache[width];
        return ret = tiling(width - 2) + tiling(width - 1);
    }
};

void testTiling() {
    startTimer();
    Tiling t;
    int ret = t.tiling(5);
    double time = stopTimerRet();
    std::cout << "t.tiling(5) = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 8);
    HR;
    
    startTimer();
    ret = t.tiling(10);
    time = stopTimerRet();
    std::cout << "t.tiling(10) = " <<  ret <<  " in " << time << " ms\n";
    //assert(ret == 8);
    HR;

    startTimer();
    ret = t.tiling(20);
    time = stopTimerRet();
    std::cout << "t.tiling(20) = " <<  ret <<  " in " << time << " ms\n";
    //assert(ret == 8);
    HR;

    // See how easily overflow can happen.
    for (int i = 21; i < 100; ++i) {
        startTimer();
        ret = t.tiling(i);
        time = stopTimerRet();
        std::cout << "t.tiling(" << i << ") = " <<  ret <<  " in " << time << " ms\n";
        assert(ret > 0);
        HR;
    }
    std::cout << "TILING TEST PASS!\n";
    
}
