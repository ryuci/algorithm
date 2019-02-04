//
//  graph.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "graph.hpp"

// Constructor
Graph::Graph(int size) : _size(size), _count(0) {
    _adj.assign(size, std::vector<std::pair<int, double>>());
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
void Graph::connect(int here, int there, double weight) {
    _adj[here].push_back({there, weight});
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
            std::cout << _adj[i][j].first;
            if (infoToo)
                std::cout << "(" << (_visited[i] ? "true": "false") << "," << _label[i] << ")";
            if (j != _adj[i].size()-1) std::cout << ",";
        }
        std::cout << std::endl;
    }
}

// Dijkstra Algorithm
//
VD Graph::dijkstra(int here) {
    // Will Store <updated distance, there> info as a pair, shortest distance first .
    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        std::greater<std::pair<double, int>>> pq;
    // Make all distances infinity except here.
    VD distance(_adj.size(), std::numeric_limits<double>::infinity());
    distance[here] = 0.;
    pq.push({0., here});
    while (!pq.empty()) {
        int cost = pq.top().first;
        int here = pq.top().second;
        pq.pop();
        // Ignore the distance from queue if we already know shorter distance.
        if (distance[here] < cost) continue;
        // Browse connecting vertices to update distance and put in the queue.
        for (int i = 0; i < _adj[here].size(); ++i) {
            int there = _adj[here][i].first;
            int tmp = cost + _adj[here][i].second;
            if (distance[there] > tmp) {
                distance[there] = tmp;
                pq.push({tmp, there});
            }
        }
    }
    return distance;
}

// Dijkstra2 Algorithm
// When |V|<<|E|, it could be much faster without using priority queue.
//
VD Graph::dijkstra2(int here) {
    // Make all distances infinity except here.
    VD distance(_adj.size(), std::numeric_limits<double>::infinity());
    
    // TODO:
    
    return distance;
}

VD Graph::bellmanFord(int here) {
    // Make all distances infinity except here.
    VD upper(_adj.size(), std::numeric_limits<double>::infinity());
    upper[here] = 0.;
    bool updated;
    for (int i = 0; i < _adj.size(); ++i) {
        updated = false;
        for (int here = 0; here < _adj.size(); ++here) {
            for (int j = 0; j < _adj[here].size(); ++j) {
                int there = _adj[here][j].first;
                int cost = _adj[here][j].second;
                if (upper[there] > upper[here] + cost) {
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    if (updated) upper.clear();
    return upper;
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
        int there = _adj[here][i].first;
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
        int there = _adj[here][i].first;
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
        int there = _adj[here][i].first;
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
}

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
        if (_adj[from][i].first == to)
            return true;
    return false;
}

    

static std::unique_ptr<Graph> prepareGraph() {
    // Make a dependency graph, which is a Directed Acyclic Graph.
    // In this example, we have 10 vertices and 11 edges.
    // Graph g(V) = V vertices
    std::unique_ptr<Graph> g = std::make_unique<Graph>(Graph(10));
    // E connect() calls = E edges. e.g. 11 calls = 11 edges.
    g->connect(5,6); g->connect(5,7); g->connect(5,8); g->connect(6,0); g->connect(7,1);
    g->connect(8,3); g->connect(0,1); g->connect(9,2); g->connect(1,2); g->connect(2,3);
    g->connect(3,4);
    g->print();
    return g;
}

static std::unique_ptr<Graph> prepareCyclicGraph() {
    // Make a Directed Cyclic Graph.
    // In this example, we have 7 vertices and 10 edges.
    // Graph g(V) = V vertices
    std::unique_ptr<Graph> g = std::make_unique<Graph>(Graph(7));
    // E connect() calls = E edges. e.g. 11 calls = 11 edges.
    g->connect(0,1); g->connect(0,4); g->connect(0,5); g->connect(0,6); g->connect(5,3);
    g->connect(5,6); g->connect(6,3); g->connect(1,2); g->connect(4,2); g->connect(2,0);
    g->print();
    return g;
}

static std::unique_ptr<Graph> prepareWeightedGraph() {
    // Make a Directed Weighted Graph.
    std::unique_ptr<Graph> g = std::make_unique<Graph>(Graph(8));
    // E connect() calls = E edges. e.g. 11 calls = 11 edges.
    g->connect(0,1,11); g->connect(0,2,9); g->connect(0,3,8);
    g->connect(1,4,8); g->connect(1,5,8);
    g->connect(2,1,3); g->connect(2,3,6); g->connect(2,6,1);
    g->connect(3,6,10);
    g->connect(4,5,7);
    g->connect(5,2,12); g->connect(5,7,5);
    g->connect(6,7,2);
    g->connect(7,4,4);
    return g;
}

static std::unique_ptr<Graph> prepareWeightedGraph2() {
    // Make a Directed (positive & negative) Weighted Graph.
    std::unique_ptr<Graph> g = std::make_unique<Graph>(Graph(8));
    // E connect() calls = E edges. e.g. 11 calls = 11 edges.
    g->connect(0,1,11); g->connect(0,2,9); g->connect(0,3,8);
    g->connect(1,4,8); g->connect(1,5,8);
    g->connect(2,1,3); g->connect(2,3,-15); g->connect(2,6,1);
    g->connect(3,6,10);
    g->connect(4,5,-7);
    g->connect(5,2,12); g->connect(5,7,5);
    g->connect(6,7,2);
    g->connect(7,4,4);
    return g;
}


void testGraphConnect() {
    std::unique_ptr<Graph> g = prepareGraph();
}

void testGraphSearch() {
    std::unique_ptr<Graph> g = prepareGraph();
}

void testGraphSort() {
    std::unique_ptr<Graph> g = prepareGraph();
    std::vector<int> order = g->sort();
    std::cout << "Sort Result: " << std::endl;
    g->printOrder();
}

void testGraphDfs() {
    std::unique_ptr<Graph> g = prepareGraph();
    std::cout << "DFS from vertex 7" << std::endl;
    g->dfs(7);
    g->print(true);
}

void testGraphDfsEdgeType() {
    std::unique_ptr<Graph> g = prepareCyclicGraph();
    std::cout << "DFS from vertex 0" << std::endl;
    g->dfs2(0);
}
    
void testGraphDfsCyclic() {
    std::unique_ptr<Graph> g = prepareCyclicGraph();
    std::cout << "DFS from vertex 0" << std::endl;
    if (g->dfs3(0))
        std::cout << "Cyclic!!!" << std::endl;
    else
        std::cout << "Acyclic!!!" << std::endl;

    g = prepareGraph();
    std::cout << "DFS from vertex 0" << std::endl;
    if (g->dfs3(0))
        std::cout << "Cyclic!!!" << std::endl;
    else
        std::cout << "Acyclic!!!" << std::endl;
}

void testGraphSplit() {
    // Should test using undirection graph??? My brain is tired now, let me think tomorrow.
    std::unique_ptr<Graph> g = prepareGraph();
    std::cout << "DFS from vertex 5" << std::endl;
    g->dfs(5);
    g->print(true);
    bool split = g->isSplit();
    std::cout << "Is splitted to components? " << (split ? "true":"false") << std::endl;
    std::cout << "DFS from all vertexes" << std::endl;
    g->dfs();
    g->print(true);
}

void testGraphDijkstra() {
    std::unique_ptr<Graph> g = prepareWeightedGraph();
    VD distance = g->dijkstra(0);
    std::cout << "Dijkstra - Distance from 0 to each vertex:" << std::endl;
    for (int i = 0; i < distance.size(); ++i) {
        std::cout << i << ": " << distance[i] << std::endl;
    }
}

void testGraphBellmanFord() {
    std::unique_ptr<Graph> g = prepareWeightedGraph2();
    VD distance = g->bellmanFord(0);
    std::cout << "BellmanFord - Distance from 0 to each vertex:" << std::endl;
    for (int i = 0; i < distance.size(); ++i) {
        std::cout << i << ": " << distance[i] << std::endl;
    }
}
