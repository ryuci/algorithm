//
//  main.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "main.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#ifdef INCLUDE_BOOST
#include <boost/math/common_factor.hpp>
#endif
#if __cplusplus > 201402L // 199711L, 201703L
#include <filesystem>
#else
#include <unistd.h>
#endif

static void showDataStructMenu();
static void showRuntimeMenu();
static void showMemoryMenu();
static void showCombinatoricsMenu();
static void showDynamicProgMenu();
static void showGeometryMenu();
static void showGreedyMethodMenu();
static void showOptByDecisionMenu();
static void showNumberTheoryMenu();
static void showNumericMenu();
static void showMatrixMenu();
#ifdef INCLUDE_OPENCV
static void showOpencvMenu();
#endif
#ifdef INCLUDE_VTK
static void showVtkMenu();
#endif
static void showMiscMenu();

#define AUTOMENU
#ifdef AUTOMENU
// Key inputs to go to the wanted menu. Append -1 twice if you want to exit after execution.
std::queue<int> autoInput = std::queue<int>({4, 6, -1, -1});
#else
std::queue<int> autoInput;
#endif

static std::vector<std::pair<std::string,void (*)()>> mainMenu = {
    {"Data Structure", showDataStructMenu},
    {"Runtime", showRuntimeMenu},
    {"Memory", showMemoryMenu},
    {"Combinatorics", showCombinatoricsMenu},
    {"Dynamic Programming", showDynamicProgMenu},
    {"Greedy Method", showGreedyMethodMenu},
    {"Opt by Decision", showOptByDecisionMenu},
    {"Number Theory", showNumberTheoryMenu},
    {"Geometry", showGeometryMenu},
    {"Numerical Analysis", showNumericMenu},
    {"Matrix", showMatrixMenu},
    {"Misc.", showMiscMenu},
#ifdef INCLUDE_OPENTV
    {"OpenCV", showOpencvMenu},
#endif
#ifdef INCLUDE_VTK
    {"Vtk", showVtkMenu},
#endif
};

static std::vector<std::pair<std::string,void (*)()>> dataStructMenu = {
    {"Hash", testHash},
    {"Resizable Hash Basic Operations", testRsHash},
    {"Resizable Hash O(1) Test", testRsHashO1},
    {"Binary Tree - Insert", testTreeInsert},
    {"Binary Tree - Search", testTreeSearch},
    {"Binary Tree - Remove", testTreeRemove},
    {"Binary Tree - DFS", testTreeDfs},
    {"Binary Tree - BFS", testTreeBfs},
    {"KDTree - Insert", testKDTreeInsert},
    {"KDTree - Search", testKDTreeSearch},
    {"KDTree - Remove", NA/*testKDTreeRemove*/},
    {"KDTree - DFS", testKDTreeDfs},
    {"KDTree - BFS", testKDTreeBfs},
    {"KDTree - Nearest Neighbor Search", NA/*testKDTreeNN*/},
    {"Graph - Connect", testGraphConnect},
    {"Graph - Search", NA/*testGraphSearch*/},
    {"Graph - DFS", testGraphDfs},
    {"Graph - DFS - Edge Type", testGraphDfsEdgeType},
    {"Graph - DFS - Detect Cycle", testGraphDfsCyclic},
    {"Graph - BFS", NA},
    {"Graph - Topological Sort", testGraphSort},
    {"Graph - Dijkstra", testGraphDijkstra},
    {"Graph - BellmanFord", testGraphBellmanFord},
    {"Graph - Eulerian Circuit", NA/*testGraphEulerianCircuit*/},
    {"Graph - Eulerian Trail", NA/*testGraphEulerianTrail*/},
    {"Graph - Cut Vertex", NA/*testGraphCutVertex*/},
    {"Minimum Spanning Tree - Prim", NA},
    {"Minimum Spanning Tree - Kruskal", NA},
    {"Graph - Shortest Path - Dijkstra", NA},
    {"Graph - Shortest Path - Bellman-Ford", NA},
    {"Graph - Shortest Path - Directed Acyclic Graph", NA},
    {"Graph - Stronglly Connected Component", NA},
    {"Graph - Backtracking - Maze", NA},
    {"Graph - Backtracking - Coloring", NA},
    {"Graph - Branch and Bound", NA},
    {"Graph - State Space Tree", NA},
};

static std::vector<std::pair<std::string,void (*)()>> runtimeMenu = {
    {"Sort - Merge Sort", testMergeSort},
    {"Sort - Quick Sort", testQuickSort},
    {"Sort - Heap Sort", testHeapSort},
    {"Sort - Count Sort", testCountingSort},
    {"Sort - Radix Sort", testRadixSort},
    {"Moving Average", testMovingAverage},
    {"Max Sum", testMaxSum},
    {"Cut Rod - Recursive vs DP", testCutRod},
    {"Boggle - Recursive vs ??", testBoggle},
    {"Picnic - Recursive vs ??", testPicnic},
    {"Board Cover - Recursive vs ??", testBoardCover},
    {"Sum - Recursive vs D&C", testSum},
    {"Multiply - D&C", testMultiply},
    {"Divide and Conquer - Fence", testFence},
    {"Linear Programming - Simplex", testLpSimplexByMosh},
    {"Dynamic Programming - Binomial", testBinomial},
    {"Dynamic Programming - Fobonacci", testDynamicProgFibonacci},
    {"Dynamic Programming - Matrix Path", testDynamicProgMatrixPath},
    {"Dynamic Programming - Pebbles", NA},
    {"Dynamic Programming - Matrix Multiplication", NA},
    {"Dynamic Programming - Longest Common Sequence", NA},
    {"TSP - BF vs. DP", testTSP }, // 11
    {"TSP - Simulated Annealing", testSaTSP },
    {"Set Cover - BF & ", testSetCover },
    {"A* - Best First Search", NA},
};

static std::vector<std::pair<std::string,void (*)()>> memoryMenu = {
    {"Eratosthenes - Prime Number", NA/*testEratosthenes*/},
    {"Quad Tree Reverse", testQuadTreeReverse},
};

static std::vector<std::pair<std::string,void (*)()>> numberTheoryMenu = {
    {"Prime Factorization", testPrimeFactor},
    {"Find Prime - Eratosthenes's Sieve", testEratosthenes},
};



static std::vector<std::pair<std::string,void (*)()>> combinatoricsMenu = {
    {"Pick List from n!", testPickList_n_factorial},
    {"Pick List from nPr", testPickList_nPr},
    {"Pick List from nCr", testPickList_nCr},
    {"Set Cover - Brute Force", testSetCover2},
};

static std::vector<std::pair<std::string,void (*)()>> dynamicProgMenu = {
    {"Jump Game", testJumpGame},
    {"Triangle Path", testTrianglePath},
    {"Triangle Path Count", testTrianglePathCount},
    {"Longest Increasing Subsequence(LIS)", testLIS},
    {"Tiling", testTiling},
    {"Snail", testSnail},
    {"Polyomino", testPolyomino},
    {"Numb3rs", testNumb3rs},

    
};

static std::vector<std::pair<std::string,void (*)()>> optByDecisionMenu = {
    {"DARPA", testDARPA},
    {"Artic", testArctic},
    {"CanadaTrip", testCanadaTrip},
    {"Withdrawal", testWithdrawal},
};


static std::vector<std::pair<std::string,void (*)()>> geometryMenu = {
    {"Rectangle Overlap", testRectOverlap},
    {"Line Intersection", testIntersection},

    
    {"Quad Tree Neighbor Search", testQuadTreeNeighborSearch},
};

static std::vector<std::pair<std::string,void (*)()>> greedyMethodMenu = {
    {"MeetingRoom", testMeetingRoom},
    {"Fight Order", testFightOrder},
    {"Heating Order", testHeatingOrder},
    {"Join String", testConcat},
    {"Minas Tirith", testMinasTirith},
};

static std::vector<std::pair<std::string,void (*)()>> numericMenu = {
    {"Floating Point Precision", testFloatingPointPrecision},
    {"Bisection", testBisect},
    {"Infinite Bisection", testBisectNeverStop},
    {"Floating Point Precision", testPrecision},

};

static std::vector<std::pair<std::string,void (*)()>> matrixMenu = {
    {"Matrix", testMatrix},
};

#ifdef INCLUDE_OPENTV
static std::vector<std::pair<std::string,void (*)()>> opencvMenu = {
    {"OpenCVWrapper", testOpencvWrapper},
};
#endif
#ifdef INCLUDE_VTK
static std::vector<std::pair<std::string,void (*)()>> vtkMenu = {
    {"VTK Cylinder", testVtkCylinder},
    {"VTK DistancePointToLine", testVtkDistancePointToLine},
    {"VTK XY Plot", testVtkXyPlot},
    {"VTK Line Draw", testVtkLineDraw},
};
#endif
static std::vector<std::pair<std::string,void (*)()>> cudaMenu = {
};


static std::vector<std::pair<std::string,void (*)()>> miscMenu = {
    {"Random Number Test", testRandom},
    {"Random Shuffle Test", testRandomShuffle},
    {"Max Numbers", testMax},
    {"Recurring Decimal - Pigeonhole Priciple", testRecurringDecimal},
};


static void showDataStructMenu() {
    displayMenu(dataStructMenu, "Data Structure");
}

static void showRuntimeMenu() {
    displayMenu(runtimeMenu, "Runtime");
}

static void showMemoryMenu() {
    displayMenu(memoryMenu, "Memory");
}

static void showCombinatoricsMenu() {
    displayMenu(combinatoricsMenu, "Combinatorics");
}

static void showDynamicProgMenu() {
    displayMenu(dynamicProgMenu, "Dynamic Programming");
}

static void showGeometryMenu() {
    displayMenu(geometryMenu, "Geometry");
}

static void showGreedyMethodMenu() {
    displayMenu(greedyMethodMenu, "Greedy Method");

}

static void showOptByDecisionMenu() {
    displayMenu(optByDecisionMenu, "Opt by Decision");
    
}


static void showNumberTheoryMenu() {
    displayMenu(numberTheoryMenu, "Number Theory");
    
}

static void showNumericMenu() {
    displayMenu(numericMenu, "Numerical Analysis");
}

#ifdef INCLUDE_OPENCV
static void showOpencvMenu() {
    displayMenu(opencvMenu, "OpenCV");
}
#endif
#ifdef INCLUDE_VTK
static void showVtkMenu() {
    displayMenu(vtkMenu, "Vtk");
}
#endif
static void showMatrixMenu() {
    displayMenu(matrixMenu, "Matrix");
}

static void showMiscMenu() {
    displayMenu(miscMenu, "Miscellaneous");
}

int main(int argc, const char * argv[]) {
    
    // IEEE754 test
    std::cout << "-------------------------\n";
    std::cout << "MIND OVERFLOW & PRECISION\n";
    std::cout << "-------------------------\n";
    std::cout << "int max = " << std::numeric_limits<int>::max() << " = about 2 billion" << std::endl;
    std::cout << "int overflow = " << std::numeric_limits<int>::max() + 1 << std::endl;
    std::cout << "long max = " << std::numeric_limits<long>::max() << std::endl;
    std::cout << "long overflow = " << std::numeric_limits<long>::max() + 1 << std::endl;
    std::cout << "double max & significant digits = " << std::numeric_limits<double>::max() << std::endl;
    std::cout << "double max * 10 = " << std::numeric_limits<double>::max() * 10 << std::endl;
#define INCLUDE_BOOST
#ifdef INCLUDE_BOOST
    // Boost test
    testBoost();
    std::cout << "Boost tested.\n";
#endif
    
    displayMenu(mainMenu, "Algorithm Test");
    return 0;
}

