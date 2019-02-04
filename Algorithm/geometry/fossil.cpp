//
//  fossil.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 04/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "geometry.hpp"


VPD hull1, hull2;

std::vector<std::pair<PD,PD>> upper, lower;

void decompose(const VPD& hull) {
    int n = (int)hull.size();
    for (int i = 0; i < n; ++i) {
        if (hull[i].x < hull[(i+1)%n].x)
            lower.push_back({hull[i], hull[(i+1)%n]});
        else if (hull[i].x > hull[(i+1)%n].x)
            upper.push_back({hull[i], hull[(i+1)%n]});
    }
}
