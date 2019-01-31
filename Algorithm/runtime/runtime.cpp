//
//  runtime.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 19/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"


// Simplex algorithm for linear programming.
// Reference: 1. https://www.youtube.com/watch?v=gRgsT9BB5-8&list=PLX5GtK5FIH593kHztmFLxUnkOOpvubN-6
//            2. http://jean-pierre.moreau.pagesperso-orange.fr/c_linear.html
//            3. https://www.technical-recipes.com/2015/implementation-of-the-simplex-algorithm-in-visual-c/
//            4. https://code.google.com/archive/p/cpplex/ (source link broken)
//            5. https://github.com/chashikajw/simplex-algorithm (not good)
//            6. https://stackoverflow.com/questions/3956950/c-c-implementation-of-simplex-method
//

Tableau tab  = { 4, 5, {                     // Size of tableau [4 rows x 5 columns ]
    {  0.0 , -0.5 , -3.0 ,-1.0 , -4.0,   },  // Max: z = 0.5*x + 3*y + z + 4*w,
    { 40.0 ,  1.0 ,  1.0 , 1.0 ,  1.0,   },  //    x + y + z + w <= 40 .. b1
    { 10.0 , -2.0 , -1.0 , 1.0 ,  1.0,   },  //  -2x - y + z + w <= 10 .. b2
    { 10.0 ,  0.0 ,  1.0 , 0.0 , -1.0,   },  //        y     - w <= 10 .. b3
}
};

void testLpSimplexByMosh() {
    print_tableau(&tab,"Initial");
    simplex(&tab);
}

#if 0
void testLinearProgrammingSimplex() {
    // Variable matrix
    std::vector<std::vector<double>> V = {
        { 2, 1, 1, 1, 0, 0},
        { 1, 3, 2, 0, 1, 0},
        { 2, 1, 2, 0, 0, 1}
    };
    // Objective vector
    std::vector<double> O = {-6, -5, -4, 0, 0, 0};
    // Constraint vector
    std::vector<double> C = {180, 300, 240};

    Simplex simplex(V, C, O);
    simplex.calc();
}
#endif
