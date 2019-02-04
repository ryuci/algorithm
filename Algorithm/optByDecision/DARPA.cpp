//
//  DARPA.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 03/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "optByDecision.hpp"

class DARPA {
private:
    bool _logOn;

    // Try all locations to place camera with distance of gap.
    //
    bool decision(const VD& location, int cameras, double gap) {
        double limit = -1;
        int installed = 0;
        if (_logOn) std::cout << "gap: " << gap << std::endl;
        for (int i = 0; i < location.size(); ++i) {
            if (limit <= location[i]) {
                if (_logOn)
                    std::cout << "limit = " << limit << " <= " <<
                    "location[" << i << "] = " << location[i] <<std::endl;
                ++installed;
                if (_logOn) std::cout << "installed = " << installed << std::endl;
                limit = location[i] + gap;
                if (_logOn) std::cout << "limit = " << limit << std::endl;
            }
        }
        if (_logOn) {
            std::cout << "installed >= cameras = " << std::boolalpha << (installed >= cameras) << std::endl;
            HR;
        }
        return installed >= cameras;
    }

public:
    DARPA(bool logOn) : _logOn(logOn) {}
    
    // Halve the distance and try to locate camera with given distance apart.
    // Case 1) Can't locate with half distance. -> Halve [lo..mid] and try, reducing distance.
    // Case 2) Can locate with half distance. -> Halve [mid..hi] and try, increasing distance.
    //
    double optimize(const VD& location, int cameras) {
        double lo = 0, hi = 241;
        for (int i = 0; i < 100; ++i) {
            double mid = (lo + hi) / 2.0;
            if (decision(location, cameras, mid))
                // Case 2
                lo = mid;
            else
                // Case 1
                hi = mid;
        }
        return lo;
    }
};

void testDARPA() {
    DARPA dp(false);
    VD loc = {0., 70., 80., 120., 200., 210., 220., 240.};
    double ret;
    double time;

    std::cout.precision(std::numeric_limits<double>::max_digits10);
    
    startTimer();
    ret = dp.optimize(loc, 4);
    time = stopTimerRet();
    std::cout << "dp.optimize(loc, 4) = " << ret <<  " in " << time << " ms\n";
    // Mind precision error.
    assert(std::abs(ret - 50) < 1e-7);
    HR;

    startTimer();
    ret = dp.optimize(loc, 5);
    time = stopTimerRet();
    std::cout << "dp.optimize(loc, 5) = " << ret <<  " in " << time << " ms\n";
    // Mind precision error.
    assert(std::abs(ret - 40) < 1e-7);
    HR;
    std::cout << "DARPA TEST PASS!\n";
    
}
