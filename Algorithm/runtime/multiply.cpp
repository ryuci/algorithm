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

// Karatusba's big integer fast multiplication
//
VI karatusba(const VI& a, const VI& b) {
    VI ret;
    return ret;
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
