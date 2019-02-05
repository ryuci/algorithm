//
//  polyomino.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 05/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"

class Polyomino {
private:
    VVL _cache;
    long _n;
    bool _logOn;

    // Return # of cases that 'n - first' blocks can make monotone polyominos,
    // when total # of block is 'n' and the first line uses 'first' blocks.
    // O(n^2)
    long poly(long n, long first) {
        if (n == first) return 1;
        long& ret = _cache[n][first];
        if (ret != -1) return ret;
        ret = 0;
        // O(n)
        for (long second = 1; second <= n - first; ++second) {
            // # of cases to add remaining blocks to the first line.
            // It depends on # of blocks in the first line and that in the second line.
            long add = second + first - 1;
            // O(n)
            add *= poly(n - first, second);
            assert(add > 0);
            ret += add;
            assert(ret > 0);
        }
        return ret;
    }

public:
    Polyomino(long n, bool logOn) : _n(n), _logOn(logOn) {
        for (int i = 0; i < n + 1; ++i)
            _cache.push_back(VL(n + 1, -1));
    }
    
    // O(n^3)
    long poly() {
        long ret = 0;
        // O(n)
        for (int first = 1; first <= _n; ++first) {
            // O(n^2)
            ret += poly(_n, first);
            assert(ret > 0);
        }
        return ret;
    }
};

void testPolyomino() {
    long ret;
    double time;
    
    startTimer();
    Polyomino p1(2, true);
    ret = p1.poly();
    time = stopTimerRet();
    std::cout << "p1.poly()(when n = 2) = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 2);
    HR;

    startTimer();
    Polyomino p2(3, true);
    ret = p2.poly();
    time = stopTimerRet();
    std::cout << "p2.poly()(when n = 3) = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 6);
    HR;

    startTimer();
    Polyomino p3(4, true);
    ret = p3.poly();
    time = stopTimerRet();
    std::cout << "p3.poly()(when n = 4) = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 19);
    HR;

    Polyomino p5(10, true);
    ret = p5.poly();
    time = stopTimerRet();
    std::cout << "p5.poly()(when n = 10) = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 20727);
    HR;

    startTimer();
    Polyomino p6(30, true);
    ret = p6.poly();
    time = stopTimerRet();
    std::cout << "p6.poly(20, 1)(when n = 30) = " <<  ret <<  " in " << time << " ms\n";
    assert(ret == 272039154528772);
    HR;

    std::cout << "POLYOMINO TEST PASS!\n";
}
