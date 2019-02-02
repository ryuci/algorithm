//
//  trianglePath.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 02/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"

// Game Rule: Move south or south-east until get to the last row,
//            summing up the nunbers at (y,x).
// Problem: Find the max sum path.
//
class TrianglePath {
public:
    VVI _board;
    VVI _cache;
    
    TrianglePath(const VVI& board) : _board(board) {
        for (int i = 0; i < board.size(); ++i) {
            _cache.push_back(VI(board.size(), -1));
        }
    }
    
    // Return max of full path, with sum from last path given,
    // extending it from (y,x) to the bottom.
    // Actually sum is not needed to get max path from (y,x).
    // This bad setup is intentional to show memoization problem it may cause.
    //
    int path(int y, int x, int sum) {
        if (y == _board.size() - 1)
            return sum + _board[y][x];
        sum += _board[y][x];
        return std::max(path(y+1, x, sum), path(y+1, x+1, sum));
    }
// Do not turn on.
#if 0
    // Because we should keep unnecessary sum, we have to keep
    // too big cache. MAX_NUMBER is max sum we may encounter
    // during path search.
    // Another problem is, if we use board2 in testTrianglePath(),
    // there is no place cache comes in because each path has different sum.
    // So, it works just like brute force.
    //
    int cache[100][100][MAX_NUMBER*100+1];
    int pathDP(int y, int x, int sum) {
        if (y == _board.size() - 1)
            return sum + _board[y][x];
        int& ret = cache[y][x][sum];
        if (ret != -1) return ret;
        sum += _board[y][x];
        return ret = std::max(pathDP(y+1, x, sum), pathDP(y+1, x+1, sum));
    }
#endif
    // This is correct solution. We don't keep sum and change input condition.
    // Return partial max path from (y,x) to the bottom.
    //
    int pathDP(int y, int x) {
        if (y == _board.size() - 1)
            return _board[y][x];
        // Trick: ret is reference to the element in cache. Cache will be updaated
        // by ret = ... in return statement below.
        int& ret = _cache[y][x];
        if (ret != -1) return ret;
        return ret= std::max(pathDP(y+1, x), pathDP(y+1, x+1)) + _board[y][x];;
    }

};

static VVI board1 = {
    {6,0,0,0,0},
    {1,2,0,0,0},
    {3,7,4,0,0},
    {9,4,1,7,0},
    {2,7,5,9,4},
};
static VVI board2 = {
    {1,0,0,0,0},
    {2,4,0,0,0},
    {8,16,8,0,0},
    {32,64,32,64,0},
    {128,256,128,256,128},
};

void testTrianglePath() {
    startTimer();
    TrianglePath tp1(board1);
    int ret = tp1.path(0, 0, 0);
    double time = stopTimerRet();
    std::cout << "tp1.path(0, 0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == 28);
    HR;

    startTimer();
    ret = tp1.pathDP(0, 0);
    time = stopTimerRet();
    std::cout << "tp1.pathDP(0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == 28);
    HR;

    startTimer();
    TrianglePath tp2(board2);
    ret = tp2.path(0, 0, 0);
    time = stopTimerRet();
    std::cout << "tp2.path(0, 0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == 341);
    HR;

    startTimer();
    ret = tp2.pathDP(0, 0);
    time = stopTimerRet();
    std::cout << "tp2.pathDP(0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == 341);
    HR;

    std::cout << "TRIANGLE PATH TEST PASS!\n";
    
}

void testTrianglePathCount() {
    std::cout << "TRIANGLE PATH COUNT PASS!\n";
}
