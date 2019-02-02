//
//  jumpGame.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 02/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "dynamicProg.hpp"

// Game Objective: Jump right or down in the number of steps determined by _board[y][x].
// Problem: Can we finish game starting from position (y,x)?
//
class JumpGame {
public:
    VVI _board;
    JumpGame(const VVI& board) : _board(board) {}
    bool canFinish(int y, int x) {
        if (y >= _board.size() || x >= _board[0].size())
            return false;
        if (y == _board.size() - 1 && x == _board[0].size() - 1)
            return true;
        int steps = _board[y][x];
        return canFinish(y + steps, x) || canFinish(y, x  + steps);
    }
};

class JumpGameDP : public JumpGame {
public:
    VVI _cache;
    JumpGameDP(const VVI& board) : JumpGame(board) {
        for (int i = 0; i < board.size(); ++i) {
            _cache.push_back(VI(board.size(), -1));
        }
    }
    bool canFinish(int y, int x) {
        // Read cache and return promptly without recusive call if possible.
        if (y >= _board.size() || x >= _board[0].size())
            return false;
        if (y == _board.size() - 1 && x == _board[0].size() - 1)
            return true;
        if (_cache[y][x] != -1)
            return _cache[y][x] != 0;
        int steps = _board[y][x];
        _cache[y][x] = canFinish(y + steps, x) || canFinish(y, x  + steps);
        return _cache[y][x];
    }
};

void testJumpGame() {
    VVI board1 = {
        {2,5,1,6,1,4,1},
        {6,1,1,2,2,9,3},
        {7,2,3,2,1,3,1},
        {1,1,3,1,7,1,2},
        {4,1,2,3,4,1,2},
        {3,3,1,2,3,4,1},
        {1,5,2,9,4,7,0},
    };
    VVI board2 = {
        {2,5,1,6,1,4,1},
        {6,1,1,2,2,9,3},
        {7,2,3,2,1,3,1},
        {1,1,3,1,7,1,2},
        {4,1,2,3,4,1,3},
        {3,3,1,2,3,4,1},
        {1,5,2,9,4,7,0},
    };
    VVI board3 = {
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,2},
        {1,1,1,1,1,2,0},
    };
    VVI board4;
    
    startTimer();
    JumpGame jg1(board1);
    bool ret = jg1.canFinish(0, 0);
    double time = stopTimerRet();
    std::cout << "jg1.canFinish(0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == true);
    HR;

    startTimer();
    JumpGame jg2(board2);
    ret = jg2.canFinish(4, 6);
    time = stopTimerRet();
    std::cout << "jg2.canFinish(4, 6) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == false);
    HR;

    startTimer();
    JumpGame jg3(board3);
    ret = jg3.canFinish(0, 0);
    time = stopTimerRet();
    std::cout << "jg3.canFinish(0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == false );
    HR;

    startTimer();
    JumpGameDP jgDP3(board3);
    ret = jgDP3.canFinish(0, 0);
    time = stopTimerRet();
    std::cout << "jgDP3.canFinish(0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == false );
    HR;

    // Make nasty problem.
    for (int i = 0; i < 30; ++i) {
        board4.push_back(VI(30,1));
    }
    board4[28][29] = board4[29][28] = 2;

    startTimer();
    JumpGameDP jgDP4(board4);
    ret = jgDP4.canFinish(0, 0);
    time = stopTimerRet();
    std::cout << "jgDP4.canFinish(0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == false );
    HR;

    std::cout << "jg4.canFinish(0, 0) is running. Will take infinte time!! Press ^C.\n";
    startTimer();
    JumpGame jg4(board4);
    ret = jg4.canFinish(0, 0);
    time = stopTimerRet();
    std::cout << "jg4.canFinish(0, 0) = " << std::boolalpha << ret <<  " in " << time << " ms\n";
    assert(ret == false );
    HR;

    std::cout << "JUMP GANE TEST PASS!\n";

}
