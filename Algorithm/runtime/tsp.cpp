//
//  tsp.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 23/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//
//  References:
//    [1] Alogorithmic Problem Solving Strategy
//    [2] 쉽게 배우는 알고리듬
//    [3] TSP CITIES - https://people.sc.fsu.edu/~jburkardt/datasets/cities/cities.html
//    [4] https://stackoverflow.com/questions/31120402/complexity-when-generating-all-combinations


#include "helper.hpp"
#include "runtime.hpp"
#if __cplusplus > 201402L // 199711L, 201703L
#include <filesystem>
#else
#include <unistd.h>
#endif
#include <sstream>
#include <fstream>

// Read TSP file format defined by [3].
//
static std::vector<std::vector<int>> readTSPFile(std::string fname, int numCities) {
    // This is how to init 2D std::vector.
    std::vector<std::vector<int>> ret(numCities,std::vector<int>(numCities));
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

static int numCities;
static std::vector<std::vector<int>> dist;
static const double INF = std::numeric_limits<double>::infinity();

// Brute force TSP
// path: City visit history in order.
// visited: Visitation flags of the cities. Duplicated info but makes coding easier.
// length: Path length up to now.
//
double bfShortestPath(std::vector<int>& path, std::vector<bool>& visited, double length) {
    if (path.size() == numCities)
        // We visied all. Add the distance from the last city to city 0.
        return length + dist[path[0]][path.back()];
    else if (path.size() == 0) {
        // path[0] must be city 0. No empty city allowed.
        std::cout << "No city # in initial path." << std::endl;
        return 0;
    }
    double ret = INF;
    for (int next = 0; next < numCities; next++) {
        if (visited[next]) {
            if (numCities <= 5)
                std::cout << "Skip visited city #" << next << std::endl;
            continue;
        }
        int here = path.back();
        path.push_back(next);
        visited[next] = true;
        if (numCities <= 5) { std::cout << "Trying path: "; print(path); }
        
        // Compare current minimum and new path length.
        ret = std::min(ret, bfShortestPath(path, visited, length + dist[here][next]));
        if (numCities <= 5)
            std::cout << "Shortest length in this trial: " << ret << std::endl;

        // Completed a path. Now step back to make new combinatorial path.
        path.pop_back();
        visited[next] = false;
        if (numCities <= 5) { std::cout << "Step back in path: "; print(path); }
    }
    return ret;
}

static const int MAX = 32;
static double cache[MAX][MAX];

// TODO:1-23-2019: Test is not finished.
// Dynamic Programming TSP
// here: Current city.
// visited: Visitation flags of the cities.
// Returns minimum length of paths starting from here.
// i.e. Focus on left path not on past path.
//
static double dpShortestPath(int here, int visited) {
    if (numCities > 32) {
        std::cout << "Max # of cities to hadnle is 32." << std::endl;
        return 0;
    }
    else if (visited == 0) {
        // Bit 0 of visited must be city 0. No empty city allowed.
        std::cout << "No city # in visited variable." << std::endl;
        return 0;
    }
    else if (visited == (1 << numCities) - 1)
        // We visied all. Return the distance from the last city to city 0.
        return dist[here][0];
    // Empty cache cell = -1
    double& ret = cache[here][visited];
    if (ret >= 0) return 0;
    ret = INF;
    for (int next = 0; next < numCities; next++) {
        if (visited & (1 << next)) continue;
        ret = std::min(ret, dist[here][next] + dpShortestPath(next, visited + (1 << next)));
    }
    return ret;
}

//  Init cache. No visit = -1.
//
static void initCache() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            cache[i][j] = -1;
}

// Test case prepares for both bfShortestPath() and dpShortestPath().
// Not efficient but for convenience's sake.
//
static void testCase1(std::vector<int>& path, std::vector<bool>& visited) {
    numCities = 3;
    dist = {
        {0, 10, 30},
        {10, 0, 20},
        {30, 20, 0},
    };
    path.clear();
    path.push_back(0);
    visited = std::vector<bool>(numCities, false);
    visited[0] = true;
    initCache();
}

static void testCase2(std::vector<int>& path, std::vector<bool>& visited) {
    numCities = 5;
    dist = {
        {0, 10, 10, 30, 25},
        {10, 0, 14, 21, 10},
        {10, 18, 0, 7, 9},
        {8, 11, 7, 0, 3},
        {14, 10, 10, 3, 0},
    };
    path.clear();
    path.push_back(0);
    visited = std::vector<bool>(numCities, false);
    visited[0] = true;
    initCache();
}

static void testCase3(std::vector<int>& path, std::vector<bool>& visited) {
//    numCities = 312;
//    dist = readTSPFile("/Users/ryuci/Dropbox/workspace/cpp/Algorithm/Algorithm/usca312_dist.txt", 312);
    numCities = 30;
    dist = readTSPFile("/Users/ryuci/Dropbox/workspace/cpp/Algorithm/Algorithm/ha30_dist.txt", 312);
    path.clear();
    path.push_back(0);
    visited = std::vector<bool>(numCities, false);
    visited[0] = true;
    initCache();
}

// Result on iMac 3.5 GHz Intel Core i5, 8 GB 1600 MHz DDR3
//                          Case 1      Case 2      Case 3
// N:                       3           5           312
// bfShortestPath():        0.125 ms    1.872 ms    ms
// dp():                    ms          ms          ms
// sa():                    ms          ms          ms
//
void testTSP() {
    std::vector<int> path;
    std::vector<bool> visited;
    double ret;
    
    // Brute force
    std::cout << std::endl << "-----------" << std::endl << "BF TSP" << std::endl << "-----------" << std::endl;
    testCase1(path, visited);
    std::cout << std::endl << "Test Case 1" << std::endl << "-----------" << std::endl;
    startTimer();
    ret = bfShortestPath(path, visited, 0);
    stopTimer();
    std::cout << "Done. Minimum length: " << ret << std::endl;
    
    testCase2(path, visited);
    std::cout << std::endl << "Test Case 2" << std::endl << "-----------" << std::endl;
    startTimer();
    ret = bfShortestPath(path, visited, 0);
    stopTimer();
    std::cout << "Done. Minimum length: " << ret << std::endl;

#if 0
    testCase3(path, visited);
    std::cout << std::endl << "Test Case 3" << std::endl << "-----------" << std::endl;
    startTimer();
    ret = bfShortestPath(path, visited, 0);
    stopTimer();
    std::cout << "Done. Minimum length: " << ret << std::endl;
#endif

    // Dynamic programming
    std::cout << std::endl << "-----------" << std::endl << "DP TSP" << std::endl << "-----------" << std::endl;
    testCase1(path, visited);
    std::cout << std::endl << "Test Case 1" << std::endl << "-----------" << std::endl;
    startTimer();
    ret = dpShortestPath(0, 1);
    stopTimer();
    std::cout << "Done. Minimum length: " << ret << std::endl;

    testCase2(path, visited);
    std::cout << std::endl << "Test Case 2" << std::endl << "-----------" << std::endl;
    startTimer();
    ret = dpShortestPath(0, 1);
    stopTimer();
    std::cout << "Done. Minimum length: " << ret << std::endl;

}
