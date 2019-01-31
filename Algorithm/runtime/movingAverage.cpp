//
//  movingAverage.cpp
//  Algorithm 
//
//  Created by Choong-il Ryu on 31/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"

std::vector<double> movingAverage(const std::vector<double>& data, int windowSize) {
    std::vector<double> ret;
    double partialSum = 0;
    for (int i = 0; i < windowSize - 1; ++i) {
        partialSum += data[i];
    }
    for (int i = windowSize - 1; i < data.size(); ++i) {
        partialSum += data[i];
        ret.push_back(partialSum / windowSize);
        partialSum -= data[i - windowSize + 1];
    }
    return ret;
}

void testMovingAverage() {
    std::vector<double> data;
    for (int i = 0; i < 20; ++i) {
        data.push_back(rand() % 10);
    }
    std::cout << "Data:\n"; print(data);
    std::cout << "MA3:\n"; print(movingAverage(data, 3));
}
