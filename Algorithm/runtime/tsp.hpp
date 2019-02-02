//
//  tsp.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef tsp_hpp
#define tsp_hpp

#include "helper.hpp"
#include "runtime.hpp"

class TSP {
protected:
    int _numCities;
    VVD _dist;
    VI _path;
    VB _visited;
    bool _logOn;
    double _INF;
    
    // Read TSP file format defined by
    // https://people.sc.fsu.edu/~jburkardt/datasets/cities/cities.html
    //
    VVD readTSPFile(std::string fname, int numCities);
    double shortestPath(double length);
    
public:
    TSP(int numCities, const VVD& dist, bool logOn);
    TSP(int numCities, std::string fname, bool logOn);
    double shortestPath();
    void logOn(bool on);
};
#endif /* tsp_hpp */
