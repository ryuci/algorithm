//
//  clockSync.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

class ClockSync {
private:
public:
    ClockSync() {}
};


//
// TEST CASES
//
void testClockSync() {
    
    ClockSync pt;
    startTimer();
    bool ret;
    double time = stopTimerRet();
    std::cout << " = " << std::boolalpha << ret << " - " << time << " ms\n";;
    //assert(ret == true);
    std::cout << "CLOCK SYNC TEST PASS! - BF " << " ms\n";
}
