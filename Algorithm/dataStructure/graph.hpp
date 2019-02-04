//
//  graph.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include "helper.hpp"

class Graph {
private:
    // Adjacency List. Size of vector<> = _size = # of vertices.
    std::vector<std::vector<int>> _adj;
    //std::vector<std::vector<std::pair<int, int>>> _adj;
    // Info stored in vertices. Size of vector = _size = # of vertices.
    std::vector<bool> _visited;
    // Another version of _visited. Record visit order.
    std::vector<int> _discovered;
    // Tell if DFS completed.
    std::vector<bool> _finished;
    // Store sorting order.
    std::vector<int> _order;
    // Store # of edges connected to the vertex. Used in Eulerian Circuit.
    std::vector<int> _degree;
    std::vector<std::string> _label;
    // # of vertices
    int _size;
    // vertices count
    int _count;
public:
    Graph(int size);
    void clearVisit();
    void clearLabel();
    void connect(int here, int there);
    void connect(int here, int there, int weight);
    void print(bool infoToo);
    void printOrder();
    void dfs(int here, std::function<void(int)> callback);
    void dfs2(int here, std::function<void(int)> callback);
    bool dfs3(int here, std::function<void(int)> callback);
    void dfs(std::function<void(int)> callback);
    std::vector<int> sort();
    void sortCallback(int x);
    bool isSplit();
    bool isCyclic(int here);
    bool exist(int from, int to);
};

void testGraphConnect();
void testGraphSearch();
void testGraphDfs();
void testGraphDfsEdgeType();
void testGraphDfsCyclic();
void testGraphSort();

#endif /* graph_hpp */
