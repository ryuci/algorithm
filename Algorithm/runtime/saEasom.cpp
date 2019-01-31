//
//  saEasom.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 30/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"
#include <cmath>

static double f(double x1, double x2) {
    return -cos(x1)*cos(x2)*exp(-(x1-M_PI)*(x1-M_PI)-(x2-M_PI)*(x2-M_PI));
}
