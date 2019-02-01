//
//  boggle.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

class Boggle {
private:
    std::vector<std::string> _table;
    // Search directions
    const int dx[8] = {-1,-1,-1, 1, 1, 1, 0, 0};
    const int dy[8] = {-1, 0, 1,-1, 0, 1,-1, 1};
public:
    Boggle(std::vector<std::string> table) : _table(table) {}
    
    // Search 8 directions for next character.
    // O(8^n) where n = string length
    //
    bool hasWord(int y, int x, std::string word) {
        if (y < 0 || x < 0 || y >= _table.size() || x >= _table[0].size())
            // Out of range
            return false;
        else if (_table[y][x] != word[0])
            // First char mismatch
            return false;
        else if (word.size() == 1)
            // Match and just length 1 word
            return true;
        // Search all directions.
        for (int i = 0 ; i < 8; ++i) {
            if (hasWord(y + dy[i], x + dx[i], word.substr(1)))
                return true;
        }
        return false;
    }
};


//
// TEST CASES
//
void testBoggle() {
    std::vector<std::string> table = {
        "URLPM",
        "XPRET",
        "GIAET",
        "XTNZY",
        "XOQRS",
    };
    Boggle bg(table);
    
    startTimer();
    bool ret = bg.hasWord(1, 1, "PRETTY");
    double time = stopTimerRet();
    std::cout << "bg.hasWord(1, 1. \"PRETTY\") = " << std::boolalpha << ret << " - " << time << " ms\n";;
    assert(ret == true);
    std::cout << "BOGGLE TEST PASS! - BF " << " ms\n";
}
