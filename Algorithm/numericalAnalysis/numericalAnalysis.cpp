//
//  numericalAnalysis.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 22/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "numericalAnalysis.hpp"
#include <iostream>
#include <cmath>
#include <limits>

// Absolute error. Works well with small numbers but not with big ones.
static bool equal(double a, double b) {
    return fabs(a - b) < 1e-7;
}

// Relative error. Works well with big numbers but not with small ones.
static bool rEqual(double a, double b) {
    return fabs(a - b) < 1e-8 * std::max(fabs(a), fabs(b));
}

// Mix absolute error and relative error.
static bool mEqual(double a, double b) {
    double diff = fabs(a - b);
    if (diff < 1e-8) return true;
    return diff < 1e-8 * std::max(fabs(a), fabs(b));
}

static void divideMultiply(int n) {
    for (int x = 1; x <= n; x++) {
        double y = 1.0 / x;
        std::cout << "1.0 / " << x << " = " << y << std::endl;
        std::cout << "1.0 / " << x << " * " << x << " = " << y * x << std::endl;
        //assert(y * x == 1.0);
        assert(equal(y * x, 1.0));
    }
}

// Bisection
//
double f(double x) { return x * x - 1.0; }

// We place restriction that f(lo) < 0 and f(hi) > 0, which has
// no impact on the solution. 
double bisect(double lo, double hi) {
    // Loop invariant
    if (f(lo) > 0) std::swap(lo, hi);
    int count = 0;
    while (!equal(hi, lo)) {
        ++count;
        double mid = (lo + hi) / 2;
        if (f(mid) <= 0) lo = mid;
        else hi = mid;
        std::cout << "#" << count << ": lo = " << lo << ", hi = " << hi << std::endl;
    }
    return (lo + hi) / 2; 
}

double bisectNeverStop() {
    double lo = 123456123456.1234588623046875;
    double hi = 123456123456.1234741210937500;
    int count = 0;

    std::cout << "#" << count << ": lo = " << lo << ", hi = " << hi << std::endl;
    std::cout << "Initial hi - lo: " << (hi - lo) << "(Under 1e-5 is garbage.)" << std::endl;
    std::cout << "Press enter.\n";
    std::string tmp;
    std::cin >> tmp;
    while (!equal(hi, lo)) {
        if (++count == 500000) {
            std::cout << "Aborted. Did you see why is this code in infinite loop?\n";
            break;
        };
        hi = (lo + hi) / 2;
        std::cout << "#" << count << ": lo = " << lo << ", hi = " << hi << std::endl;
    }
    return (lo + hi) / 2; 
}



void testFloatingPointPrecision() {
#if 0
    for (int i = 10; i < 60; i++)
        divideMultiply(i);
#else
    divideMultiply(60);
#endif
}

void testBisect() {
    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << "Result:\n" << bisect(0.0, 3.0) << std::endl;
}

void testBisectNeverStop() {
    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << "Result:\n" << bisectNeverStop() << std::endl;
}

void testPrecision() {
    std::cout.precision(std::numeric_limits<double>::max_digits10);
    for (int j = 2; j <= 10; ++j) {
        double sum = 0.0;
        for (int i = 1; i <= j; ++i) {
            if (i != j) std::cout << "1/" << j << " + ";
            else std::cout << "1/" << j;
            sum += 1.0 / j;                 
        }
        std::cout << " = " << sum << std::endl;                 
    }
}
