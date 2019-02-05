//
//  numb3rs.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 05/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"

class Numb3rs {
protected:
    VVB _map;
    VVD _cache;
    VI _targets;
    int _prison, _days;
    bool _logOn;
    
public:
    Numb3rs(VVB& map, VI& targets, int prison, int days, bool logOn)
    : _map(map), _targets(targets), _prison(prison), _days(days), _logOn(logOn) {
    }
    VD sniff() {
        VD prob;
        return prob;
    }
};

void testNumb3rs() {
    VD ret;
    double time;
    VVB map1 = {{0,1,1,1,0},
                {1,0,0,0,1},
                {1,0,0,0,0},
                {1,0,0,0,0},
                {0,1,0,0,0}};
    VI targets1 = {0,2,4};
    VVB map2 = {{0,1,1,1,0,0,0,0},
                {1,0,0,1,0,0,0,0},
                {1,0,0,1,0,0,0,0},
                {1,1,1,0,1,1,0,0},
                {0,0,0,1,0,0,1,1},
                {0,0,0,1,0,0,0,1},
                {0,0,0,0,1,0,0,0},
                {0,0,0,0,1,1,0,0}};
    VI targets2 = {3,1,2,6};

    startTimer();
    // TODO:2-5-2019: Why do I have compile error in "Numb3rs n1(map1, {0,2,4}, true);"?
    //      Is it illegal to make a reference to temp object?
    Numb3rs n1(map1, targets1, 2, 0, true);
    time = stopTimerRet();
    ret = n1.sniff();
    //std::cout << "p1.poly()(when n = 2) = " <<  ret <<  " in " << time << " ms\n";
    //assert(ret == 2);
    HR;

    startTimer();
    Numb3rs n2(map2, targets2, 2, 3, true);
    time = stopTimerRet();
    ret = n1.sniff();
    //std::cout << "p1.poly()(when n = 2) = " <<  ret <<  " in " << time << " ms\n";
    //assert(ret == 2);
    HR;

    std::cout << "NUMB3RS TEST PASS!\n";
}
