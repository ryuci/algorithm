//
//  combinatorics.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 31/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "combinatorics.hpp"

void nFactorial(int n, std::vector<int>& pick, std::vector<std::vector<int>>& pickList);
void nPr(int n, int r, std::vector<int>& pick, std::vector<std::vector<int>>& pickList);
void nCr(int n, int r, std::vector<int>& pick,  std::vector<std::vector<int>>& pickList);

// nFactorial
//
void nFactorial(int n, std::vector<int>& pick, std::vector<std::vector<int>>& pickList) {
    nPr(n, n, pick, pickList);
}

// nPr
//
void nPr(int n, int r, std::vector<int>& pick, std::vector<std::vector<int>>& pickList) {
    // Base case
    if (r == 0) {
        pickList.push_back(pick);
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (std::find(pick.begin(), pick.end(), i) != pick.end()) {
            // We already picked i, so skip it.
            continue;
        }
        pick.push_back(i);
        // We pass n. Not n-1!
        nPr(n, r-1, pick, pickList);
        pick.pop_back();
    }
}

// nCr
//
void nCr(int n, int r, std::vector<int>& pick, std::vector<std::vector<int>>& pickList) {
    // Base case
    if (r == 0) {
        pickList.push_back(pick);
        return;
    }
    int smallest = pick.empty() ? 0 : pick.back() + 1;
    for (int i = smallest; i < n; ++i) {
        pick.push_back(i);
        // We pass n. Not n-1!
        nCr(n, r-1, pick, pickList);
        pick.pop_back();
    }
}

class SetCover {
private:
    std::vector<int> _pick;
    std::vector<std::vector<int>> _pickList;
    std::vector<std::vector<int>> _rule;
    std::vector<int> _setCount;
    int _coverSize;
    int _minSize;
    const int INF = 987654321;
    
    bool isCovered() {
        // Check if there is an element not covered.
        if (std::find(_setCount.begin(), _setCount.end(), 0) == _setCount.end()) {
            // All covered.
            int size = (int)_pick.size();
            if (_minSize == size) {
                _pickList.push_back(_pick);
            }
            else if (_minSize > size) {
                _pickList.clear();
                _pickList.push_back(_pick);
                _minSize = size;
            }
            return true;
        }
        return false;
    }
    
    int selectCover(int index) {
        if (index == _coverSize) {
            // Searched all indexes. Store the pick if it's one of the answers.
            if (isCovered()) return (int)_pick.size();
            else return INF;
        }
        // Calculate without adding next index.
        int ret = selectCover(index + 1);
        // Calculate after adding next index.
        _pick.push_back(index + 1);
        ret = std::min(ret, selectCover(index + 1));
        _pick.pop_back();
        return ret;
    }
    
public:
    SetCover(int coverSize, std::vector<std::vector<int>> rule)  {
        _coverSize = coverSize;
        _rule = rule;
        _minSize = INF;
        _setCount.assign(_rule.size(), 0);
    }
    
    std::vector<std::vector<int>> getCover() {
        _pick.clear();
        _pickList.clear();
        _setCount.clear();
        _minSize = INF;
        _setCount.assign(_rule.size(), 0);
        if (selectCover(0) == INF)
            std::cout << "Cover not found!\n";
        return _pickList;
    }
};


// Test Codes
//
void testPickList_n_factorial() {
    std::vector<int> pick;
    std::vector<std::vector<int>> pickList;

    pick.clear();
    pickList.clear();
    startTimer();
    nFactorial(3, pick, pickList);
    stopTimer();
    std::cout << "TEST PICK LIST 3!\n";
    for (int i = 0; i < pickList.size(); ++i)
        print(pickList[i]);
    std::cout << "---\n";
    
    pick.clear();
    pickList.clear();
    startTimer();
    nFactorial(5, pick, pickList);
    stopTimer();
    std::cout << "TEST PICK LIST 8!\n";
    for (int i = 0; i < pickList.size(); ++i)
        print(pickList[i]);
    std::cout << "---\n";
}

void testPickList_nPr() {
    std::vector<int> pick;
    std::vector<std::vector<int>> pickList;

    pick.clear();
    pickList.clear();
    startTimer();
    nPr(3, 2, pick, pickList);
    stopTimer();
    std::cout << "TEST PICK LIST 3P2\n";
    for (int i = 0; i < pickList.size(); ++i)
        print(pickList[i]);
    std::cout << "---\n";
    
    pick.clear();
    pickList.clear();
    startTimer();
    nPr(5, 3, pick, pickList);
    stopTimer();
    std::cout << "TEST PICK LIST 8P3\n";
    for (int i = 0; i < pickList.size(); ++i)
        print(pickList[i]);
    std::cout << "---\n";
}

void testPickList_nCr() {
    std::vector<int> pick;
    std::vector<std::vector<int>> pickList;
    
    pick.clear();
    pickList.clear();
    startTimer();
    nCr(3, 2, pick, pickList);
    stopTimer();
    std::cout << "TEST PICK LIST 3C2\n";
    for (int i = 0; i < pickList.size(); ++i)
        print(pickList[i]);
    std::cout << "---\n";

    pick.clear();
    pickList.clear();
    startTimer();
    nCr(8, 3, pick, pickList);
    stopTimer();
    std::cout << "TEST PICK LIST 8C3\n";
    for (int i = 0; i < pickList.size(); ++i)
        print(pickList[i]);
    std::cout << "---\n";
}

void testSetCover2()
{
    std::vector<std::vector<int>> rule = {
        {1, 2},
        {0, 3},
        {0, 2},
        {0},
        {1, 2},
        {1, 3}
    };
    std::vector<std::vector<int>> ret;
    SetCover sc(4, rule);
    startTimer();
    ret = sc.getCover();
    stopTimer();
    for (int i = 0; i < ret.size(); ++i)
        print(ret[i]);
    assert(ret[0].size() == 2);
    
    rule = {{0, 2, 3, 7, 8},
            {0, 3, 8},
            {0, 2, 5, 6, 7, 8, 9},
            {1, 3, 6},
            {1, 2, 5, 7, 8},
            {1, 4, 6, 9},
            {1, 2, 6, 7, 8}};
    SetCover sc2(10, rule);
    startTimer();
    ret = sc.getCover();
    stopTimer();
    for (int i = 0; i < ret.size(); ++i)
        print(ret[i]);
    assert(ret[0].size() == 3);
}
