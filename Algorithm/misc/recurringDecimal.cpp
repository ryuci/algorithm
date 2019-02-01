//
//  recurringDecimal.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "misc.hpp"
#include <sstream>

std::string printDecimal(int a, int b) {
    int iter = 0;
    std::ostringstream s;
    int occurence[10] = {0};
    
    while (a > 0) {
        if (iter++ == 1) {
            //std::cout << '.';
            s << '.';
        }
        //std::cout << a/b;
        // Get quotient by divide.
        s << a/b;
        // Get remainder and multiply 10 to divide again.
        if (iter > 0 && a % b != 0) {
            if (occurence[a % b] != 0) break;
            occurence[a % b] = 1;
        }
        a = (a % b) * 10;
        // Until remainder is not 0.
    }
    return s.str();
}

//
// TEST CASES
//
void testRecurringDecimal() {
    std::string ret;
    ret = printDecimal(3, 8);
    assert(ret == "0.375");
    std::cout << "printDecimal(3, 8): " << ret << std::endl;

    ret = printDecimal(4712, 400);
    assert(ret == "11.78");
    std::cout << "printDecimal(4712, 400): " << ret << std::endl;

    ret = printDecimal(1, 11);
    assert(ret == "0.09");
    std::cout << "printDecimal(1, 11): " << ret << std::endl;

    std::cout << "RECURRING DECIMAL TEST PASS! - DP \n";
}
