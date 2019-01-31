//
//  matrix.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 25/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "matrix.hpp"
#include <iostream>
#ifdef INCLUDE_VTK
#include <Eigen/Dense>
using namespace Eigen;
#endif
void testMatrix()
{
#ifdef INCLUDE_VTK
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << "Here is the matrix m:\n" << m << std::endl;
    VectorXd v(2);
    v(0) = 4;
    v(1) = v(0) - 1;
    std::cout << "Here is the vector v:\n" << v << std::endl;
#endif
    
}
