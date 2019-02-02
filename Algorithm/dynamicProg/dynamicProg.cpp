//
//  dynamicProg.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 16/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"
#include <ctime>


//
//
// Fibonnacci Problem
//
//

// Fibonnacci using recursion
// Count how many fibonacci(2) is used to show repetitive calls.
//
int count = 0;
unsigned long rFibonacci(int n) {
    //std::cout << n << std::endl;
    if (n == 2) count++;
    if (n == 1 || n == 2)
        return 1;
    else
        return (rFibonacci(n-1) + rFibonacci(n-2));
}

// Fibonnacci using memoization
//
unsigned long dFibonacci(int n) {
    unsigned int f[n-1];
    f[0] = f[1] = 1;
    for (int i = 3; i <= n; i++)
        f[i-1] = f[i-2] + f[i-3];
    return f[n-1];
}

//
//
// Matrix Path Problem
//
//
const int MATRIX_SIZE = 5;
// m: Problem Matrix
int m[MATRIX_SIZE][MATRIX_SIZE];
// c: c[i][j] means the maximum path value to reach m[i][j]
int c[MATRIX_SIZE][MATRIX_SIZE];
Point<int> bestPath[MATRIX_SIZE*2];
// Used in recursion
int c2[MATRIX_SIZE][MATRIX_SIZE];

void prepareMatrix() {
    // Change the seed.
    srand((unsigned int)time(0));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m[i][j] = rand() % 10 + 1;
        }
    }
}

// Goal: Find c[i][j] which is max path from m[0][0] to m[i][j].
// Idea: 1) c[i][j] = m[0][0], if i = j = 0
//       2) c[i][j] = m[0][j] + c[0][j], if i = 0, j > 0
//       3) c[i][j] = m[i][0] + c[i][0], if i > 0, j = 0
//       4) c[i][j] = m[i][j] + max(c[i-1][j], c[i][j-1]), if i > 0, j > 0
//
void dMatrixPath() {
    // 1) c[i][j] = m[0][0], if i = j = 0
    c[0][0] = m[0][0];
    
    // 2) c[i][j] = m[0][j] + c[0][j], if i = 0, j > 0
    for (int j = 1; j < MATRIX_SIZE; j++) {
        c[0][j] = m[0][j] + c[0][j-1];
    }

    // 3) c[i][j] = m[i][0] + c[i][0], if i > 0, j = 0
    for (int i = 1; i < MATRIX_SIZE; i++) {
        c[i][0] = m[i][0] + c[i-1][0];
    }

    // 4) c[i][j] = m[i][j] + max(c[i-1][j], c[i][j-1]), if i > 0, j > 0
    int count = 0;
    for (int i = 1; i < MATRIX_SIZE; i++) {
        for (int j = 1; j < MATRIX_SIZE; j++) {
#if 0
            c[i][j] = m[i][j] + std::max(c[i-1][j], c[i][j-1]);
#else
            if (c[i-1][j] > c[i][j-1]) {
                bestPath[count].x = i - 1;
                bestPath[count++].y = j;
                c[i][j] = m[i][j] + c[i-1][j];
            }
            else {
                bestPath[count].x = i;
                bestPath[count++].y = j - 1;
                c[i][j] = m[i][j] + c[i][j-1];
            }
#endif
        }
    }
}

// Solve the same problem using recursion.
int rMatrixPath(int i, int j) {
    if (i == 0 && j == 0) c2[i][j] = m[i][j];
    else if (i == 0) c2[i][j] = m[0][j] + rMatrixPath(0, j - 1);
    else if (j == 0) c2[i][j] = m[i][0] + rMatrixPath(i - 1, 0);
    else c2[i][j] = m[i][j] + std::max(rMatrixPath(i - 1, j), rMatrixPath(i, j - 1));
    return c2[i][j];
}


void printMatrix(std::string tag, int ar[MATRIX_SIZE][MATRIX_SIZE]) {
    std::cout << tag;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            std::cout << ar[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void printMatrixPathSolution() {
    printMatrix("Matrix Path Solution:\n", c);
    for (int i = 0; i < MATRIX_SIZE * 2; i++) {
        std::cout << '(' << bestPath[i].x << ',' << bestPath[i].y << ')';
    }
    std::cout << std::endl << "Max sum of path values = " << c[MATRIX_SIZE-1][MATRIX_SIZE-1] << std::endl;
}

void testDynamicProgFibonacci() {
    // Shows how many repetitive function calls in recursion.
    std::cout << "rFibonacci(7) = " << rFibonacci(7) << std::endl;
    std::cout << "rFibonacci(2) called " << count << " times" << std::endl;
    std::cout << "dFibonacci(7) = " << dFibonacci(7) << std::endl;
    // Shows how fast dynamic programming, or memoization is doing compared with recursion.
    //clock_t c0 = clock();
    startTimer();
    std::cout << "dFibonacci(40) = " << dFibonacci(44) << std::endl;
    stopTimer();
    startTimer();
    std::cout << "rFibonacci(40) = " << rFibonacci(44) << std::endl;
    stopTimer();
}

void testDynamicProgMatrixPath() {
    // Matrix path problem
    // Rules: 1) Start from top-left cell.
    //        2) Move right or down.
    //        3) Can't move up, left, diagonally.
    //        4) Find the maximum path.
    //
    prepareMatrix();
    printMatrix("Matrix Path Problem:\n", m);
    dMatrixPath();
    printMatrixPathSolution();
    rMatrixPath(MATRIX_SIZE - 1, MATRIX_SIZE - 1);
    printMatrix("Another Matrix Path Solution:\n", c2);
}

void testDynamicProg() {
    


}
