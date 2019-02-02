//
//  tspDp.cpp
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
#include "tsp.hpp"

// TSP using Dynamic Programming
//
class TSP_DP : public TSP {
protected:
    VVD _cache;

    // TODO:1-23-2019: Coding is not finished.
    // Dynamic TSP
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
    TSP_DP(int numCities, const VVD& dist, bool logOn) : TSP(numCities, dist, logOn) {
        // Init cache.
        for (int i = 0; i < numCities; ++i) {
            VD tmp;
            tmp.assign(numCities, -1);
            _cache.push_back(tmp);
        }

    }
    
    TSP_DP(int numCities, std::string fname, bool logOn) : TSP(numCities, readTSPFile(fname, numCities), logOn) {
        
    }
    
    double shortestPath() {
        return shortestPath(0);
    }
    
    void logOn(bool on) { _logOn = on; }
};
