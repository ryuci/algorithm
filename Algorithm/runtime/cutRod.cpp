//
//  cut_road.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

class CutRod {
private:
    std::vector<int> _price;
    std::vector<int> _revenue;
    int _length;
    const int _EMPTY = -1;
    // Find the max revenue of the road of length.
    // Idea: r(n) = max(p(i) + r(n-i) for i=[1..n]
    //       n = rod length
    //       r(n): max revenue from cutting the rod
    //       p(n): price of the rod
    //
    int optRevenueBF(int length) {
        if (length == 0)
            return 0;
        int max = std::numeric_limits<int>::min();
        for (int i = 0; i < length; ++i)
            max = std::max(max, _price[i] + optRevenueBF(length - i - 1));
        return max;
    }

    int optRevenueDP(int length) {
        if (length == 0)
            return 0;
        else if (_revenue[length - 1] != _EMPTY)
            // Use memoized value.
            return _revenue[length - 1];
        
        int max = std::numeric_limits<int>::min();
        for (int i = 0; i < length; ++i)
            max = std::max(max, _price[i] + optRevenueBF(length - i - 1));
        // Momoize.
        _revenue[length - 1] = max;
        return max;
    }

public:

    CutRod(std::vector<int> price) : _price(price), _length((int)price.size()) {
        _revenue.assign(_length, _EMPTY);
    }

    int getOptRevenueBF() {
        return optRevenueBF(_length);
    }

    int getOptRevenueDP() {
        return optRevenueDP(_length);
    }

};


//
// TEST CASES
//
void testCutRod() {
    std::vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    CutRod cr(price);

    startTimer();
    int revenue = cr.getOptRevenueBF();
    double ret = stopTimerRet();
    std::cout << "revenue = " << revenue << "\n";
    assert(revenue == 30);
    std::cout << "CUT ROD TEST PASS! - BF " << ret << " ms\n";

    startTimer();
    revenue = cr.getOptRevenueDP();
    ret = stopTimerRet();
    std::cout << "revenue = " << revenue << "\n";
    assert(revenue == 30);
    std::cout << "CUT ROD TEST PASS! - DP " << ret << " ms\n";

}
