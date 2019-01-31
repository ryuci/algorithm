//
//  kdtree.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef kdtree_hpp
#define kdtree_hpp

#include <iostream>
#include "tree.hpp"

class KDTree : public Tree {
private:
    int _dim;

protected:
    Node* insert(Node* here, std::vector<int> key, int depth);
    Node* search(Node* here, std::vector<int> key, int depth);
    Node* remove(Node* here, std::vector<int> key, int depth);

public:
    KDTree(int dim);
    void insert(std::vector<int> key);
    void search(std::vector<int> key);
    bool exist(std::vector<int> key);
    void remove(std::vector<int> key);
};

void testKDTreeInsert();
void testKDTreeSearch();
void testKDTreeRemove();
void testKDTreeDfs();
void testKDTreeBfs();
void testKDTreeNN();

#endif /* kdtree_hpp */
