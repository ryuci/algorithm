//
//  picnic.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

class Picnic {
private:
    std::vector<std::vector<bool>> _besty;
    std::vector<bool> _assigned;
    int _classSize;

    int countBesties(std::vector<bool> assigned) {
        // Place restiction to remove multiple counting of same pairs.
        // Paring first avaialble student first.
        int firstFree = -1;
        for (int i = 0; i < _classSize; ++i) {
            if (!assigned[i]) {
                firstFree = i;
                break;
            }
        }
        // Base case
        if (firstFree == -1) return 1;
        int ret = 0;
        
        // Decide a student to pair woth firstFree.
        for (int i = firstFree + 1; i < _classSize; ++i) {
            if (!assigned[i] && _besty[firstFree][i]) {
                assigned[firstFree] = true;
                assigned[i] = true;
                ret += countBesties(assigned);
                assigned[firstFree] = false;
                assigned[i] = false;
            }
        }
        return ret;
    };

public:
    Picnic(std::vector<std::vector<int>> bestyList, int classSize) : _classSize(classSize) {
        _assigned.assign(classSize, false);
        for (int i = 0; i < classSize; ++i) {
            std::vector<bool> tmp;
            tmp.assign(classSize, false);
            _besty.push_back(tmp);
        }
        for (int i = 0; i < bestyList.size(); ++i) {
            _besty[bestyList[i][0]][bestyList[i][1]] = true;
            _besty[bestyList[i][1]][bestyList[i][0]] = true;
        }
    }

    int countBesties() {
        return countBesties(_assigned);
    };
};


//
// TEST CASES
//
void testPicnic() {
    std::vector<std::vector<int>> bestyList = {{0,1}};
    startTimer();
    Picnic pc1(bestyList, 2);
    int ret = pc1.countBesties();
    double time = stopTimerRet();
    std::cout << "pc1.countBesties() = " << ret << " - " << time << " ms\n";;
    assert(ret == 1);

    bestyList = {{0,1}, {1,2}, {2,3}, {3,0}, {0,2}, {1,3}};
    startTimer();
    Picnic pc2(bestyList, 4);
    ret = pc2.countBesties();
    time = stopTimerRet();
    std::cout << "pc2.countBesties() = " << std::boolalpha << ret << " - " << time << " ms\n";;
    assert(ret == 3);

    bestyList = {{0,1}, {0,2}, {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4}, {3,5}, {4,5},};
    startTimer();
    Picnic pc3(bestyList, 6);
    ret = pc3.countBesties();
    time = stopTimerRet();
    std::cout << "pc3.countBesties() = " << std::boolalpha << ret << " - " << time << " ms\n";;
    assert(ret == 4);

    std::cout << "PICNIC TEST PASS! - BF " << " ms\n";
}
