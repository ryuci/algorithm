//
//  tree.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <iostream>

typedef struct _Node {
    std::vector<int> key;
    // For binary tree children vector will have only two elements:
    //  children[0] for left, [1] for right
    std::vector<struct _Node*> children;
} Node;

class Tree {
protected:
    Node* _tree;
    // TODO:15Jan2019: Keep track of _depth
    int _depth;
    
    Node* makeNode(std::vector<int> key);
    Node* insert(Node* here, std::vector<int> key);
    Node* search(Node* here, std::vector<int> key);
    Node* remove(Node* here, std::vector<int> key);
    void print(Node* here);
    void printKey(std::vector<int> key);
    int height(Node* here);
public:
    Tree();
    void bfs(Node* here, void (*callback)());
    void dfs(Node* here, void (*callback)());
    void insert(std::vector<int> key);
    void search(std::vector<int> key);
    void remove(std::vector<int> key);
    bool exist(std::vector<int> key);
    void print();
    int height();
};

void testTreeInsert();
void testTreeSearch();
void testTreeRemove();
void testTreeBfs();
void testTreeDfs();

#endif /* tree_hpp */
