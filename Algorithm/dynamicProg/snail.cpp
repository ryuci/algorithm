//
//  snail.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 03/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"
#include <numeric>

// Objective:
//
class Snail {
private:
    VVI     _pickList;
    VI      _pick;
    bool    _logOn;

public:
    Snail(bool logOn) : _logOn(logOn) {}
    
    // Pick 1 or 2 for num selections.
    //
    void pick(int num) {
        if (num == 0) {
            _pickList.push_back(_pick);
            return;
        }
        _pick.push_back(1);
        pick(num - 1);
        _pick.pop_back();
        _pick.push_back(2);
        pick(num - 1);
        _pick.pop_back();
    }
    
    // Probability that sum of elements in m picks is >= n.
    //
    double probability(int n, int m)
    {
        _pick.clear();
        _pickList.clear();
        pick(m);
        int count = 0;
        // Count the case that total is >= n.
        for (int i = 0; i < _pickList.size(); ++i) {
            int tmp = std::accumulate(_pickList[i].begin(), _pickList[i].end(), 0);
            if (tmp >= n) ++count;
            if (_logOn) std::cout << "sum = " << tmp << ", count = " << count << "\n";
        }
        return (double)count/pow(2,m);
    }

    // Print pickList.
    void print() {
        for (int i = 0; i < _pickList.size(); ++i)
            ::print(_pickList[i]);
    }
        void logOn(bool on) { _logOn = on; }
};

class SnailDP {
private:
    const int _MAX_N = 100;
    int _n, _m;
    VVI _cache;
    // Number of cases that sum of elements is >= n,
    // given passed days and achived climbs.
    //
    int climb(int days, int climbed) {
        if (days == _m) return climbed >= _n ? 1 : 0;
        int& ret = _cache[days][climbed];
        if (ret != -1) return ret;
        return ret = climb(days + 1, climbed + 1) + climb(days + 1, climbed + 2);
    }

    // We could calculate probablity instead of count.
    // e.g.
    //    return ret = 0.75 * climb(days + 1, climbed + 1) + 0.25 * climb(days + 1, climbed + 2);
    
    // Clear cache.
    //
    void clearCache() {
        _cache.clear();
        for (int i = 0; i < _MAX_N; ++i) {
            _cache.push_back(VI(2*_MAX_N+1, -1));
        }
    }
    
public:
    SnailDP() {
        for (int i = 0; i < _MAX_N; ++i) {
            _cache.push_back(VI(2*_MAX_N+1, -1));
        }

    }
    
    double probability(int n, int m)
    {
        clearCache();
        _n = n;
        _m = m;
        int count = climb(0, 0);
        return (double)count/pow(2,_m);
    }
};

void testSnail() {
    Snail s(true);
    
    // Test pick.
    s.pick(4);
    s.print();
    
    startTimer();
    // Probabilty to clime 6 in 4 days.
    double ret = s.probability(6, 4);
    double time = stopTimerRet();
    std::cout << "s.probability(6, 4) = " << ret <<  " in " << time << " ms\n";
    HR;
    
    s.logOn(false);
    startTimer();
    // Probabilty to clime 100 in 20 days.
    ret = s.probability(100, 20);
    time = stopTimerRet();
    std::cout << "s.probability(100, 20) = " << ret <<  " in " << time << " ms\n";
    HR;

    // Takes too long if i > 25.
    for (int i = 0; i <= 22; ++i) {
        startTimer();
        // Probabilty to clime 30 in i days.
        ret = s.probability(30, i);
        time = stopTimerRet();
        std::cout << "s.probability(30, " << i << ") = " << ret <<  " in " << time << " ms\n";
        HR;
    }

    // See how fast it is using DP.
    SnailDP sdp;
    for (int i = 0; i <= 23; ++i) {
        startTimer();
        // Probabilty to clime 30 in i days.
        ret = s.probability(30, i);
        time = stopTimerRet();
        std::cout << "s.probability(30, " << i << ") = " << ret <<  " in " << time << " ms\n";
        startTimer();
        // Probabilty to clime 30 in i days.
        ret = sdp.probability(30, i);
        time = stopTimerRet();
        std::cout << "sdp.probability(30, " << i << ") = " << ret <<  " in " << time << " ms\n";
        HR;
    }

    std::cout << "SNAIL TEST PASS!\n";
}
