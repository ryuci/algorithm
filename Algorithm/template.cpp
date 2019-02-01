//
//  template.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

class Problem {
private:
public:
    Problem() {}
};


//
// TEST CASES
//
void testProblem() {
    
    Problem pt;
    startTimer();
    bool ret;
    double time = stopTimerRet();
    std::cout << " = " << std::boolalpha << ret << " - " << time << " ms\n";;
    //assert(ret == true);
    std::cout << "PROBLEM TEST PASS! - BF " << " ms\n";
}
