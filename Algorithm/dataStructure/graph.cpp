//
//  graph.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "graph.hpp"
#include <string>
#include <vector>

// Constructor
Graph::Graph(int size) : _size(size), _count(0) {
    _adj.assign(size, std::vector<int>());
    _visited.assign(size, false);
    _discovered.assign(size, -1);
    _finished.assign(size, false);
    _label.assign(size, "");
}

void Graph::clearVisit() {
    for (int i = 0; i < _size; i++)
        _visited[i] = false;
}

void Graph::clearLabel() {
    for (int i = 0; i < _size; i++)
        _label[i] = nullptr;
}

// Add an edge
void Graph::connect(int me, int to) {
    _adj[me].push_back(to);
}

// Print the graph
// Vertex number starts from 0, not 1
void Graph::print(bool infoToo=false) {
    for (int i = 0; i < _size; i++) {
        std::cout << i;
        if (infoToo)
            std::cout << "(" << (_visited[i] ? "true": "false") << "," << _label[i] << ")";
        std::cout << ": ";
        for (int j = 0; j < _adj[i].size(); j++) {
            std::cout << _adj[i][j];
            if (infoToo)
                std::cout << "(" << (_visited[i] ? "true": "false") << "," << _label[i] << ")";
            if (j != _adj[i].size()-1) std::cout << ",";
        }
        std::cout << std::endl;
    }
}

// Depth First Search
// Visit recursively all vertices connected from here.
// [1] If graph is split to multiple components, this method can't visit other components.
// [2] Type of edges found by DFS spanning:
//      [1] Tree edge - Edge of spanning tree.
//      [2] Forward edge - No tree edge but connected from the ancestor in spanning tree.
//      [3] Back edge - No tree edge but connected to the ancestor in spanning tree.
//      [4] Cross edge - Otherwise. i.e. edge of no ancestor-descendent relation.

void Graph::dfs(int here, std::function<void(int)> callback=nullptr) {
    std::cout << "dfs() visiting " << here << std::endl;
    _visited[here] = true;
        
    // Iteratively visit adjacent vertex
    for (int i = 0; i < _adj[here].size(); i++) {
        int there = _adj[here][i];
        if (!_visited[there])
            // Tree edge
            dfs(there, callback);
    }
    // Just in case we want to something here
    if (callback != nullptr) callback(here);
}

// Depth First Search 2
// Shows edge type.
// TODO:1-19-2019: Will be merged with dfs().
//
void Graph::dfs2(int here, std::function<void(int)> callback=nullptr) {
    // Vertex discovered earlier will have smaller value.
    _discovered[here] = _count++;
    
    // Iteratively visit adjacent vertex
    for (int i = 0; i < _adj[here].size(); i++) {
        int there = _adj[here][i];
        std::cout << "(" << here << "," << there << ")" << "is a ";
        // -1: no visit, >=0: visit order
        if (_discovered[there] == -1) {
            std::cout << "tree edge." << std::endl;
            dfs2(there, callback);
        }
        else if (_discovered[here] < _discovered[there])
            std::cout << "forward edge." << std::endl;
        else if (_finished[there] == 0)
            std::cout << "back edge." << std::endl;
        else
            std::cout << "cross edge." << std::endl;
    }
    // BST(here) completes.
    _finished[here] = 1;
    // Just in case we want to something here
    if (callback != nullptr) callback(here);
}

// Depth First Search 3
// Detect cycle.
// TODO:1-19-2019: Will be merged with dfs().
//
bool Graph::dfs3(int here, std::function<void(int)> callback=nullptr) {
    // Vertex discovered earlier will have smaller value.
    _discovered[here] = _count++;
    
    // Iteratively visit adjacent vertex
    for (int i = 0; i < _adj[here].size(); i++) {
        int there = _adj[here][i];
        // -1: no visit, >=0: visit order
        if (_discovered[there] == -1) {
            // tree edge.
            if (dfs3(there, callback))
                return true;
        }
        else if (_discovered[here] < _discovered[there])
            // forward edge
            ;
        else if (_finished[there] == 0) {
            // back edge
            std::cout << "(" << here << "," << there << ")!!!" << std::endl;
            return true;
        }
        else
            // cross edge
            ;
    }
    // BST(here) completes.
    _finished[here] = 1;
    // Just in case we want to something here
    if (callback != nullptr) callback(here);
    return false;
}

// Visit all vertices even though they are splitted
//void Graph::dfs(void(*callback)(int)=nullptr) {
void Graph::dfs(std::function<void(int)> callback=nullptr) {
    clearVisit();
    //print(true);
    for (int i = 0; i < _size; i++) {
        if (!_visited[i])
            dfs(i, callback);
    }
};

// Print the order which is stored by sort().
void Graph::printOrder() {
    for (int i = 0; i < _order.size(); i++) {
        std::cout << _order[i];
        if (i != _order.size() - 1)
            std::cout << ",";
    }
    std::cout << std::endl;
}

void Graph::sortCallback(int x) {
    std::cout << "sortCallback()" << std::endl;
    _order.push_back(x);
};

// Topological Sort
std::vector<int> Graph::sort() {
    // Topological sort is not available in cyclic graph.
    if (isCyclic(0))
        // Return empty order vector.
        return std::vector<int>();
    clearVisit();
    _order.clear();
    for (int i = 0; i < _size; i++)
        if (!_visited[i])
#if 1
            // Member function callback.
            // Reference: http://plming.tistory.com/59
            //            http://tedfelix.com/software/c++-callbacks.html
            dfs(i, std::bind(&Graph::sortCallback, this, std::placeholders::_1));
#else
            // Looks not a good place to use lambda function.
            // TODO:1-17-2019: Try to use function object.
            dfs(here, [](int here){_order.push_back(here);});
            // TODO:1-17-2019: Find out workaround.
            // Callback does not bind in following case:
            // 1) void Graph::dfs(void(*callback)(int)=nullptr) {};
            // 2) dfs(here, &Graph::sortCallback);
            // Error: No matching member function for call to 'dfs'
            //         No known conversion from 'void (Graph::*)(int)' to 'void (*)(int)' for 2nd argument
#endif
    reverse(_order.begin(), _order.end());
#if 1
    // Check if there's reverse edge. There shouldn't.
    for (int i = 0; i < _size; i++) {
        for (int j = i + 1; j < _size; j++) {
# if 0 // For adjacency matrix
            // TODO:1-17-2019: Get used to it.
            std::cout << "_adj[" << _order[j] << "][" << _order[i] << "]=" << _adj[_order[j]][_order[i]] << std::endl;
            if (_adj[_order[j]][_order[i]]) {
# else // For adjacency list
            std::cout << "Check _adj[" << _order[j] << "][" << _order[i] << "] ";
            // TODO:1-17-2019: Faster way?
            if (exist(_order[j], _order[i])) {
#endif
                std::cout << "Reverse order!" << std::endl;
                print();
                return std::vector<int>();
            }
            std::cout << "false" << std::endl;
        }
    }
#endif
    return _order;
}

// Test if it's split graph.
// Idea: 1) Do DFS from a random vertice.
//       2) If there's no visitted vertex, it means the graph is split.
// TODO:17Jan2019: Do unit test again.
bool Graph::isSplit() {
    clearVisit();
    int randV = rand() % _size;
    std::cout << "DFS from random vertex #" << randV << std::endl;
    dfs(randV);
    for (int i = 0; i < _size; i++) {
        if (!_visited[i])
            return true;
    }
    return false;
};

// Test if it's cyclic graph.
bool Graph::isCyclic(int here) {
    _discovered.assign(_size, -1);
    _finished.assign(_size, false);
    _count = 0;
    return dfs3(here);
}

// Test if edge exists.
bool Graph::exist(int from, int to) {
    for (int i = 0; i < _adj[from].size(); i++)
        if (_adj[from][i] == to)
            return true;
    return false;
}

    

Graph* testGraphPrepare() {
    // Make a dependency graph, which is a Directed Acyclic Graph.
    // In this example, we have 10 vertices and 11 edges.
    // Graph g(V) = V vertices
    Graph* g = new Graph(10);
    // E connect() calls = E edges. e.g. 11 calls = 11 edges.
    g->connect(5,6); g->connect(5,7); g->connect(5,8); g->connect(6,0); g->connect(7,1);
    g->connect(8,3); g->connect(0,1); g->connect(9,2); g->connect(1,2); g->connect(2,3);
    g->connect(3,4);
    g->print();
    return g;
}

Graph* testGraphPrepareCyclic() {
    // Make a Directed Cyclic Graph.
    // In this example, we have 7 vertices and 10 edges.
    // Graph g(V) = V vertices
    Graph* g = new Graph(7);
    // E connect() calls = E edges. e.g. 11 calls = 11 edges.
    g->connect(0,1); g->connect(0,4); g->connect(0,5); g->connect(0,6); g->connect(5,3);
    g->connect(5,6); g->connect(6,3); g->connect(1,2); g->connect(4,2); g->connect(2,0);
    g->print();
    return g;
}

void testGraphConnect() {
    Graph* g = testGraphPrepare();
    delete g;
}

void testGraphSearch() {
    Graph* g = testGraphPrepare();
    delete g;
}

void testGraphSort() {
    Graph* g = testGraphPrepare();
    std::vector<int> order = g->sort();
    std::cout << "Sort Result: " << std::endl;
    g->printOrder();
    delete g;
}

void testGraphDfs() {
    Graph* g = testGraphPrepare();
    std::cout << "DFS from vertex 7" << std::endl;
    g->dfs(7);
    g->print(true);
    delete g;
}

void testGraphDfsEdgeType() {
    Graph* g = testGraphPrepareCyclic();
    std::cout << "DFS from vertex 0" << std::endl;
    g->dfs2(0);
    delete g;
}
    
void testGraphDfsCyclic() {
    Graph* g = testGraphPrepareCyclic();
    std::cout << "DFS from vertex 0" << std::endl;
    if (g->dfs3(0))
        std::cout << "Cyclic!!!" << std::endl;
    else
        std::cout << "Acyclic!!!" << std::endl;

    g = testGraphPrepare();
    std::cout << "DFS from vertex 0" << std::endl;
    if (g->dfs3(0))
        std::cout << "Cyclic!!!" << std::endl;
    else
        std::cout << "Acyclic!!!" << std::endl;
    delete g;
}

void testGraphSplit() {
    // Should test using undirection graph??? My brain is tired now, let me think tomorrow.
    Graph* g = testGraphPrepare();
    std::cout << "DFS from vertex 5" << std::endl;
    g->dfs(5);
    g->print(true);
    bool split = g->isSplit();
    std::cout << "Is splitted to components? " << (split ? "true":"false") << std::endl;
    std::cout << "DFS from all vertexes" << std::endl;
    g->dfs();
    g->print(true);
    delete g;
}
