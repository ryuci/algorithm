//
//  runtime.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 19/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef runtime_hpp
#define runtime_hpp

//#define M 20
//#define N 20

typedef struct {
    int m, n; // m=rows, n=columns, mat[m x n]
    double mat[20][20];
} Tableau;

void testBinomial();
void testTSP();
void testSaTSP();

void testFence();

void testMergeSort();
void testQuickSort();
void testHeapSort();
void testCountingSort();
void testRadixSort();

void testSetCover();


void testLinearProgrammingSimplex();
void testLpSimplexByMosh();

void testDynamicProgFibonacci();
void testDynamicProgMatrixPath();
void testDynamicProg();

void testMovingAverage();

void testMaxSum();
void testMultiply();


void print_tableau(Tableau *tab, const char* mes);
void simplex(Tableau *tab);

void testCutRod();

void testBoggle();
void testPicnic();
void testBoardCover();

void testSum();
void testMultiply();
void testBoost();


#endif /* runtime_hpp */
