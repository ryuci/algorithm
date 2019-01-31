//
//  misc.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 18/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//
//  References:
//    [1] Alogorithmic Problem Solving Strategy
//    [2] 쉽게 배우는 알고리듬
//    [3] TSP CITIES - https://people.sc.fsu.edu/~jburkardt/datasets/cities/cities.html
//    [4] https://stackoverflow.com/questions/31120402/complexity-when-generating-all-combinations

#include "helper.hpp"
#include "misc.hpp"
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
#include <random>

//
void testRandom() {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    // distribution in range [0, 10]
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,10);
    
    for (int i = 0; i < 10; i++)
        std::cout << dist(rng) << " ";
    std::cout << std::endl;
}

//
void testRandomShuffle() {
    std::vector<int> data = {0,1,2,3,4,5,6,7,8,9};
    std::mt19937 rng;
    rng.seed(std::random_device()());
    
    for (int i = 0; i < 5; i++) {
        std::shuffle(data.begin(), data.end(), rng);
        print(data);
    }
}

//
void testMax() {
    std::cout << "std::numeric_limits<int>::max() = " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "std::numeric_limits<long>::max() = " << std::numeric_limits<long>::max() << std::endl;
    std::cout << "std::numeric_limits<unsigned int>::max() = " << std::numeric_limits<unsigned int>::max() << std::endl;
    std::cout << "std::numeric_limits<float>::max() = " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "std::numeric_limits<double>::max() = " << std::numeric_limits<double>::max() << std::endl;
}



// Pick r out of n
// O(n^r)
void pick_r_out_of_n(int r, int n) {
    // r is ignored. Will pick 4 out of n.
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                for (int l = k + 1; l < n; l++)
                    std::cout << i << " " << j << " " << k << " " << l << std::endl;
}


// Pick r out of n using bitmask
// Reference: https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
//
void bm_pick_r_out_of_n(int r, int n)
{
    std::string bitmask(r, 1); // K leading 1's
    bitmask.resize(n, 0); // N-K trailing 0's
    
    // print integers and permute bitmask
    do {
        for (int i = 0; i < n; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) std::cout << " " << i;
        }
        std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

void testCombination() {
    startTimer();
    pick_r_out_of_n(4, 7);
    stopTimer();
    
    
    startTimer();
    bm_pick_r_out_of_n(7, 4);
    stopTimer();
}

// Prime Factorization 1
// Reference: [1] pp.105
// Complexity: Loop [2,n]. O(n).
//             If we think each digit as input size, runtime is O(10^n).
//             It's exponential, not polynomial!
//             e.g. 1 digit = 10 loops, 2 digits = 10*10 loops, n digits = 10^n loops.
std::vector<long> primeFactor1(long n) {
    if (n == 1) return std::vector<long>(1, 1);
    std::vector<long> ret;
    for (long i = 2; n > 1; i++) {
        while (n % i == 0) {
            n /= i;
            ret.push_back(i);
        }
    }
    return ret;
}

// Prime Factorization 2
// Reference: [1] pp.497
// Complexity: For composite number n, n = p*q -> p <= sqrt(n), p >= sqrt(n).
//             So we may loop [2,sqrt(n)] instead of [3,n]. O(sqrt[n]).
std::vector<long> primeFactor2(long n) {
    std::vector<long> ret;
    long sqrtn = long(sqrt(n));
    for (long i = 2; i <= sqrtn; ++i) {
        while (n % i == 0) {
            n /= i;
            ret.push_back(i);
        }
    }
    if (n > 1) ret.push_back(n);
    return ret;
}

void testPrimeFactor() {
    std::vector<long> ret;
    std::cout << "primeFactor1(3547)" << ":\n";
    startTimer();
    ret = primeFactor1(3547);
    stopTimer();
    print(ret);

    std::cout << "primeFactor2(3547)" << ":\n";
    startTimer();
    ret = primeFactor2(3547);
    stopTimer();
    print(ret);

    std::cout << "primeFactor1(1000000000000000000)" << ":\n";
    startTimer();
    ret = primeFactor1(1000000000000000000);
    stopTimer();
    print(ret);

    std::cout << "primeFactor2(1000000000000000000)" << ":\n";
    startTimer();
    ret = primeFactor2(1000000000000000000);
    stopTimer();
    print(ret);

    std::cout << "primeFactor1(std::numeric_limits<long>::max())" << ":\n";
    startTimer();
    ret = primeFactor1(std::numeric_limits<long>::max());
    stopTimer();
    print(ret);
    
    std::cout << "primeFactor2(std::numeric_limits<long>::max())" << ":\n";
    startTimer();
    ret = primeFactor2(std::numeric_limits<long>::max());
    stopTimer();
    print(ret);
}

// Check if n is a prime number.
// Reference:
// Complexity: O(n).
bool isPrime1(long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long i = 3; i < n; i++)
        if (n % i == 0) return false;
    return true;
}

// Check if n is a prime number.
// Reference: [1] pp.496
// Complexity: O(sqrt[n]).
bool isPrime2(long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    long sqrtn = long(sqrt(n));
    for (long i = 3; i <= sqrtn; i++)
        if (n % i == 0) return false;
    return true;
}

void testIsPrime() {
    bool ret;
    std::cout << "isPrime1(3547)" << ":\n";
    startTimer();
    ret = isPrime1(3547);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;

    std::cout << "isPrime2(3547)" << ":\n";
    startTimer();
    ret = isPrime2(3547);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;

    std::cout << "isPrime1(10000000000000000)" << ":\n";
    startTimer();
    ret = isPrime1(10000000000000000);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;

    std::cout << "isPrime2(10000000000000000)" << ":\n";
    startTimer();
    ret = isPrime2(10000000000000000);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;
}




// Cover the board by brute-force.
// Reference: [1] pp.160
// Complexity: O()

// Four 2D array represent following pieces.
//  +-   -+  |    |
//  |     |  +-  -+
const int coverType[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1,-1}},
};

// Cover (y,x) with chosen type.
// delta = 1 means "place a piece", -1 means "remove it".
bool boardSet(std::vector<std::vector<int>>& board, int y, int x, int type, int delta) {
    bool ok = true;
    for (int i = 0; i < 3; i++) {
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
            // Out of range
            ok = false;
        else if((board[ny][nx] += delta) > 1)
            // Overlap, but will keep placing. Will remove the whole at a time later.
            ok = false;
    }
    std::cout << "boardSet(" << y << "," << x << "," << type << "," << delta << "): "
              << std::boolalpha << ok << std::endl;
    return ok;
}

// Return # of cases that fill the board.
int boardCover(std::vector<std::vector<int>>& board) {
    int y = -1, x = -1;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            //std::cout << "(i,j)=" << i << "," << j << std::endl;
            if (board[i][j] == 0) {
                // Found empty cell.
                y = i;
                x = j;
                break;
            }
        }
        if (y != -1)
            // Found empty cell.
            break;
    }
    std::cout << "Trying fill from (y,x)=" << y << "," << x << std::endl;
    if (y == -1)
        // No cell to fill.
        return 1;
    int ret = 0;
    for (int type = 0; type < 4; type++) {
        if (boardSet(board, y, x, type, 1))
        {
            print(board);
            ret += boardCover(board);
        }
        // Remove the piece.
        boardSet(board, y, x, type, -1);
    }
    return ret;
}

// TODO:1-19-2019: Test failed! Find out why.
void testBoardCover() {
    std::vector<std::vector<int>> board = {
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,1,0,0,0,1,1},
    };
    startTimer();
    std::cout << boardCover(board) << " way(s) to cover.\n";
    stopTimer();

    board = {
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,1,0,0,1,1,1},
    };
    startTimer();
    std::cout << boardCover(board) << " way(s) to cover.\n";
    stopTimer();

    board = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1},
    };
    startTimer();
    std::cout << boardCover(board) << " way(s) to cover.\n";
    stopTimer();
}
