//
//  multiplication.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

// Big integer multiplication
//
VI multiply(const VI& a, const VI& b) {
    VI c(a.size() + b.size() + 1, 0);
    for (int i = 0 ; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            c[i+j] += a[i] * b[j];
        }
    }
    // Process carries.
    c.push_back(0);
    for (int i = 0 ; i < c.size(); ++i) {
        if (c[i] < 0) {
            int borrow = (abs(c[i]) + 9) / 10;
            c[i+1] -= borrow * 10;
            c[i] += borrow * 10;
        }
        else {
            c[i+1] += c[i] / 10;
            c[i] %= 10;
        }
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

// Karatusba's big integer fast multiplication
//
static void add(VI& a, const VI& b, int k) {
    for (int i = 0; i < b.size(); ++i) {
        for (int i = 0; i < b.size(); ++i) {
            a[i] += b[i]; //??????
        }
    }
}

static void sub(VI& a, const VI& b) {
    
}

VI karatsuba(const VI& a, const VI& b) {
    if (a.size() < b.size())
        // Put longer number first.
        return karatsuba(b, a);
    if (a.size() == 0 || b.size() == 0)
        return std::vector<int>();
    // Karatsuba is efficient for big numbers.
    if (a.size() <= 50) return multiply(a, b);
    int half = a.size() / 2;
    // Split the number.
    VI a0(a.begin(), a.begin() + half);
    VI a1(a.begin() + 1, a.end());
    VI b0(b.begin(), b.begin() + std::min((int)b.size(), half));
    VI b1(a.begin() + std::min((int)b.size(), half), b.end());
    // z2 = a1 * b1
    VI z2 = karatsuba(a1, b1);
    // z0 = a0 * b0
    VI z0 = karatsuba(a0, b0);
    //  a0 = a0 + a1
    add(a0, a1, 0);
    //  b0 = b0 + b1
    add(b0, b1, 0);
    // z1 = (a0 * b0) - z0 -z3;
    VI z1 = karatsuba(a0, b0);
    sub(z1, z0);
    sub(z1, z2);
    // ret = z0 + z1 * 10^half + z2 * 10^(half*2)
    VI ret;
    add(ret, z0, 0);
    add(ret, z1, half);
    add(ret, z2, half + half);
    return ret;    return ret;
}

// Matrix multiplication using recursion.
//
matrix<double> pow(matrix<double> m, int n) {
    matrix<double> ret = m;
    if (n == 0)
        return identity_matrix<double>(m.size1());
    return prod(pow(m, n-1), m);
}

// Matrix multiplication using divide & conquer.
//
matrix<double> powDC(matrix<double> m, int n) {
    matrix<double> ret = m;
    if (n == 0)
        return identity_matrix<double>(m.size1());
    if (n % 2 == 1)
        return prod(powDC(m, n-1), m);
    return prod(powDC(m, n/2), powDC(m, n/2));
}

// Strassen's fast matrix multiplication
//
matrix<double> strassen(matrix<double> m, int n) {
    matrix<double> ret;
    return ret;
}



//
// TEST CASES
//

// Strange. When using boost, DC is slower than recursive.
// Result on iMac 3.5 GHz Intel Core i5, 8 GB 1600 MHz DDR3
//          Case 1      Case 2
// pow():   0.751 ms    0.754 ms
// powDC(): 1.315 ms    1.279 ms
//

void testMultiply() {
    // Prepara matrix using boost libs.
    matrix<double> m(5, 5);
    for (unsigned i = 0; i < m.size1(); ++ i)
        for (unsigned j = 0; j < m.size2(); ++ j)
            m(i, j) = 3 * i + j;
    std::cout << m << std::endl;
    startTimer();
    matrix<double> ret = pow(m, 100);
    double time = stopTimerRet();
    std::cout << "pow(m, 100) = " << ret << " in " << time << " ms\n";;
    //assert(ret == 50005000);
    std::cout << "--\n";

    startTimer();
    ret = powDC(m, 100);
    time = stopTimerRet();
    std::cout << "powDC(m, 100) = " << ret << " in " << time << " ms\n";;
    //assert(ret == 50005000);
    std::cout << "--\n";
    
    m = identity_matrix<double>(5);
    std::cout << m << std::endl;
        startTimer();
    ret = pow(m, 100);
    time = stopTimerRet();
    std::cout << "pow(i, 100) = " << ret << " in " << time << " ms\n";;
    //assert(ret == 50005000);
    std::cout << "--\n";

    startTimer();
    ret = powDC(m, 100);
    time = stopTimerRet();
    std::cout << "powDC(m, 100) = " << ret << " in " << time << " ms\n";;
    //assert(ret == 50005000);
    std::cout << "--\n";

    std::cout << "MULTIPLY TEST PASS!\n";
}


#include <boost/range/adaptor/adjacent_filtered.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <iterator>
#include <functional>
#include <iostream>
#include <vector>

void testBoost() {
    using namespace boost::assign;
    using namespace boost::adaptors;
    
    std::vector<int> input;
    input += 1,1,2,2,2,3,4,5,6;
    
    boost::copy(
                input | adjacent_filtered(std::not_equal_to<int>()),
                std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;
}
