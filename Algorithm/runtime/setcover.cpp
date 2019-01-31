//
//  setcover.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 23/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

// Count of sources each device can connect.
// e.g. _srcCount[2] = 3 => Device 2 can connect 3 difference sources.
static std::vector<int> _srcCount;

static const int _MAX_SOURCES = 1000;
static std::vector<int> _table[_MAX_SOURCES];

static int _devicesNum, _sourcesNum, _min;

// Set Cover Problem
// We have N devices and M power sources.
// Each device may or may not connected to specific power source as follows.
//
// src0     dev2, dev4, devN-1
// src1     dev1, dev2
//  :
// srcM-1   dev5, dev3, devN-1
//
// Find minimum subset size of power sources to cover all devices.
// e.g. If both S1 = {src0, src7} and S2 = {src3, src6, src7} can cover all devices.
//      |S1| is minimum, and answer is |S1| = 2.
//
static void selectPowerSource(int source, std::vector<int>& srcCount, int selectedSrcCount) {
    // Base cases
    if (selectedSrcCount >= _min) {
        // Simple pruning. No more search.
        return;
    }
    if (source == _sourcesNum) {
        if (std::find(srcCount.begin(), srcCount.end(), 0) == srcCount.end()) {
            // _srcCount is full of non-zero. All covered.
            _min = selectedSrcCount;
        }
        return;
    }
    
    // Do not take srcToConsider.
    selectPowerSource(source + 1, srcCount, selectedSrcCount);

    // Take srcToConsider.
    for (int j = 0; j < _table[source].size(); ++j)
        srcCount[_table[source][j]]++;

    selectPowerSource(source + 1, srcCount, selectedSrcCount + 1);

    for (int j = 0; j < _table[source].size(); ++j)
        srcCount[_table[source][j]]--;
}

static void testCase1() {
    _devicesNum = 4;  // device
    _sourcesNum = 6;  // source
    _min = 987654321;
    _table[0] = {1, 2};
    _table[1] = {0, 3};
    _table[2] = {0, 2};
    _table[3] = {0};
    _table[4] = {1, 2};
    _table[5] = {1, 3};
    _devicesNum = 4;  // device
    _sourcesNum = 6;  // source
    _srcCount = std::vector<int>(_devicesNum);
}

static void testCase2() {
    _devicesNum = 10;  // device
    _sourcesNum = 7;  // source
    _min = 987654321;
    _table[0] = {0, 2, 3, 7, 8};
    _table[1] = {0, 3, 8};
    _table[2] = {0, 2, 5, 6, 7, 8, 9};
    _table[3] = {1, 3, 6};
    _table[4] = {1, 2, 5, 7, 8};
    _table[5] = {1, 4, 6, 9};
    _table[6] = {1, 2, 6, 7, 8};
    _srcCount = std::vector<int>(_devicesNum);
}

static void testCase3() {
    _devicesNum = 60;  // device
    _sourcesNum = 40;  // source
    _min = 987654321;
    if (_sourcesNum >= _MAX_SOURCES) _sourcesNum = _MAX_SOURCES;
    for (int i = 0; i < _sourcesNum; i++) {
        int devices = rand() % 20;
        for (int j = 0; j < devices; j++)
            //table[i][j] = rand() % DEVICES;
            _table[i].push_back(rand() % _devicesNum);
    }
    _srcCount = std::vector<int>(_devicesNum);
}

void testSetCover() {

    // Brute force
    std::cout << std::endl << "-----------" << std::endl << "BF SET COVER" << std::endl << "-----------" << std::endl;
    std::cout << std::endl << "Test Case 1" << std::endl << "-----------" << std::endl;
    testCase1();
    startTimer(); selectPowerSource(0, _srcCount, 0); stopTimer(); assert(_min == 2);
    std::cout << "Done. Best size: " << _min << std::endl;

    std::cout << std::endl << "Test Case 2" << std::endl << "-----------" << std::endl;
    testCase2();
    startTimer(); selectPowerSource(0, _srcCount, 0); stopTimer(); assert(_min == 3);
    std::cout << "Done. Best size: " << _min << std::endl;

    std::cout << std::endl << "Test Case 3" << std::endl << "-----------" << std::endl;
    testCase3();
    startTimer(); selectPowerSource(0, _srcCount, 0); stopTimer();
    std::cout << "Done. Best size: " << _min << std::endl;
}
