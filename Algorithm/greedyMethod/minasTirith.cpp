//
//  minasTirith.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 03/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "greedyMethod.hpp"

void testMinasTirith() {
    VI s1 = {2,2,4};
    VI s2 = {3,1,3,4,1};
    VI s3 = {1,1,1,1,1,1,1,2};
    double time;
    
    startTimer();
    //int ret = concat(s1);
    time = stopTimerRet();
    //std::cout << "concat(s1) = " << ret <<  " in " << time << " ms\n";
    //assert(ret == 12);
    HR;

    std::cout << "MINAS TIRITH TEST PASS!\n";
}

