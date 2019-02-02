//
//  tsp.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"
#include <fstream>
#include <sstream>
#if __cplusplus > 201402L // 199711L, 201703L
#include <filesystem>
#else
#include <unistd.h>
#endif


class TSP {
protected:
    int _numCities;
    VVD _dist;
    VI _path;
    VB _visited;
    bool _logOn = false;
    double _INF = std::numeric_limits<double>::infinity();

    // Read TSP file format defined by
    // https://people.sc.fsu.edu/~jburkardt/datasets/cities/cities.html
    //
    VVD readTSPFile(std::string fname, int numCities) {
        // This is how to init 2D std::vector.
        VVD ret(numCities,VD(numCities));
        std::string line;
        std::ifstream file(fname.data());
        if (file.is_open()) {
            int from = 0, to = 0;
            while (getline(file, line)) {
                // Ignore comment lines.
                if (line[0] == '#') continue;
                //std::cout << line << std::endl;
                std::istringstream iss(line);
                int distance;
                while(iss >> distance)
                {
                    ret[from][to] = distance;
                    if (++to == numCities) {
                        ++from;
                        to = 0;
                    }
                }
            }
            file.close();
        }
        else {
            std::cout << "Unable to open " << fname << std::endl;
#if __cplusplus > 201402L
            // This function is available only from C++14.
            std::cout << "cwd = " << std::filesystem::current_path() << std::endl;
#else
            char cwd[256];
            getcwd(cwd, 256);
            std::cout << "cwd = " << cwd << std::endl;
#endif
        }
        return ret;
    }

    // Brute force TSP
    // path: City visit history in order.
    // visited: Visitation flags of the cities. Duplicated info but makes coding easier.
    // length: Path length up to now.
    //
    double shortestPath(double length) {
        if (_logOn) {
            std::cout << "shortestPath(" << length << ")\n";
            std::cout << "Path: ";
            print(_path);
        }
        if (_path.size() == _numCities) {
            std::cout << "return(" << length + _dist[_path.back()][_path[0]] << ")\n";
            // We visied all. Add the distance from the last city to city 0.
            return length + _dist[_path.back()][_path[0]];
        }
        else if (_path.size() == 0) {
            // path[0] must be city 0. No empty city allowed.
            std::cout << "No city # in initial path." << std::endl;
            std::cout << "return(0)\n";
            return 0;
        }
        double ret = _INF;
        for (int there = 0; there < _numCities; there++) {
            if (_visited[there]) {
                continue;
            }
            int here = _path.back();
            _path.push_back(there);
            _visited[there] = true;

            // Compare current minimum and new path length.
            double tmp = shortestPath(length + _dist[here][there]);
            if (tmp < ret) {
                if (_logOn)
                    std::cout << "new minimum " << tmp << " < " << ret <<"\n";
                ret = tmp;
            }
            // Completed a path. Now step back to make new combinatorial path.
            _path.pop_back();
            _visited[there] = false;
        }
        if (_logOn)
            std::cout << "return(" << ret << ")\n";
        return ret;
    }
    
public:
    TSP(int numCities, const VVD& dist, bool logOn) {
        _numCities = numCities;
        _dist = dist;
        _visited.assign(_numCities, false);
        _logOn = logOn;
        // Assume we start from city 0.
        _path.push_back(0);
        _visited[0] = true;
    }

    TSP(int numCities, std::string fname, bool logOn) {
        TSP(numCities, readTSPFile(fname, numCities), logOn);
    }
    
    double shortestPath() {
        return shortestPath(0);
    }
    
    void logOn(bool on) { _logOn = on; }
};


//
// TEST CASES
//
void testTSP() {
    
    VVD dist1 = {
        {0, 10, 30},
        {10, 0, 20},
        {30, 20, 0},
    };
    VVD dist2 = {
        {0, 20, 30, 10, 11},
        {15, 0, 16, 4, 2},
        {3, 5, 0, 2, 4},
        {19, 6, 18, 0, 3},
        {16, 4, 7, 16, 0},
    };
    VVD dist3 = {
        {0.0000000000,  326.0008994586,  503.1066076077,  290.0250922998},
        {326.0008994586,  0.0000000000,  225.1785728436,  395.4019367384},
        {503.1066076077,  225.1785728436,  0.0000000000,  620.3945520632},
        {290.0250922998,  395.4019367384,  620.3945520632,  0.0000000000},
    };
    startTimer();
    TSP tsp1(3, dist1, true);
    double ret = tsp1.shortestPath();
    double time = stopTimerRet();
    std::cout << "tsp1.shortestPath() = " << ret << " - " << time << " ms\n";;
    assert(ret == 60);
    std::cout << "---\n";;

    startTimer();
    TSP tsp2(5, dist2, true);
    ret = tsp2.shortestPath();
    time = stopTimerRet();
    std::cout << "tsp2.shortestPath() = " << ret << " - " << time << " ms\n";;
    assert(ret == 28);
    std::cout << "---\n";;
#if 0
    startTimer();
    TSP tsp3(30, "/Users/ryuci/Dropbox/workspace/cpp/Algorithm/Algorithm/asset/ha30_dist.txt", false);
    ret = tsp3.shortestPath();
    time = stopTimerRet();
    std::cout << "tsp3.shortestPath() = " << ret << " - " << time << " ms\n";;
    assert(ret == 28);
    std::cout << "---\n";;
#endif
    std::cout << "TSP TEST PASS! - BF ms\n";
}
