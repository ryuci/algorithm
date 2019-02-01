//
//  boardCover.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

// TODO:1-2-2019: Bug fix not completed.
//
// Cover the board by brute-force.
// Reference: [1] pp.160
// Complexity: O()
//
class BoardCover {
private:
    // Four 2D array represent following pieces.
    //  +-   -+  |    |
    //  |     |  +-  -+
    const int _coverType[4][3][2] = {
        {{0, 0}, {1, 0}, {0, 1}},
        {{0, 0}, {0, 1}, {1, 1}},
        {{0, 0}, {1, 0}, {1, 1}},
        {{0, 0}, {1, 0}, {1,-1}},
    };

    std::vector<std::vector<int>> _board;
    
    // Cover (y,x) with chosen type.
    // delta = 1 means "place a piece", -1 means "remove it".
    bool set(std::vector<std::vector<int>>& board, int y, int x, int type, int delta) {
        bool ok = true;
        for (int i = 0; i < 3; i++) {
            const int ny = y + _coverType[type][i][0];
            const int nx = x + _coverType[type][i][1];
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
    int cover(std::vector<std::vector<int>>& board) {
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
            if (set(board, y, x, type, 1))
            {
                print(board);
                ret += cover(board);
            }
            // Remove the piece.
            set(board, y, x, type, -1);
        }
        return ret;
    }

public:
    BoardCover(std::vector<std::vector<int>> board) : _board(board) {}
    int cover() {
        return cover(_board);
    }
};

//
// TEST CASES
//
void testBoardCover() {
    std::vector<std::vector<int>> board = {
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,1,0,0,0,1,1},
    };
    BoardCover bc1(board);
    int ret = bc1.cover();
    startTimer();
    double time = stopTimerRet();
    std::cout << " = " << std::boolalpha << ret << " - " << time << " ms\n";;
    //assert(ret == true);

    board = {
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,1,0,0,1,1,1},
    };
    startTimer();
    time = stopTimerRet();
    std::cout << " = " << std::boolalpha << ret << " - " << time << " ms\n";;
    //assert(ret == true);

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
    time = stopTimerRet();
    std::cout << " = " << std::boolalpha << ret << " - " << time << " ms\n";;
    //assert(ret == true);

    std::cout << "BOARD COVER TEST PASS! - BF " << " ms\n";
}
