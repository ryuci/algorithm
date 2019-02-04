//
//  misc.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 18/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef misc_hpp
#define misc_hpp

#include <iostream>

void nCr(int n);
void recursive_pick_r_out_of_n(int n, std::vector<int>& picked, int toPick);
std::vector<long> primeFactor1(long n);
std::vector<long> primeFactor2(long n);
bool isPrime1();
bool isPrime2();

double shortestPath(std::vector<int>& path, std::vector<bool>& visited, double length);
bool boardCoverable(std::vector<std::vector<int>>& board, int y, int x, int type, int delta);
int boardCover(std::vector<std::vector<int>>& board);

void testRandom();
void testRandomShuffle();

void testPrimeFactor();
void testIsPrime();

void testMax();
void testRecurringDecimal();

#endif /* misc_hpp */
