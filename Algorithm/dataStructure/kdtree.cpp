//
//  kdtree.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include <string>
#include <queue>
#include <list>
#include "kdtree.hpp"


// References: http://andrewd.ces.clemson.edu/courses/cpsc805/references/nearest_search.pdf (kNN using KDTree)

// Constructor
KDTree::KDTree(int dim) : _dim(dim) {};

// External APIs, hiding reference to _tree.
void KDTree::insert(std::vector<int> key) {
    _tree = insert(_tree, key, 0);
}
void KDTree::search(std::vector<int> key) {
    _tree = search(_tree, key, 0);
    
}
void KDTree::remove(std::vector<int> key) {
    _tree = remove(_tree, key, 0);
    
}
bool KDTree::exist(std::vector<int> key) {
    Node* tmp = search(_tree, key, 0); return (tmp && (tmp->key == key));
}

// Override Tree's insert method
Node* KDTree::insert(Node* here, std::vector<int> key, int depth) {
    if (here == nullptr) {
        here = makeNode(key);
        return here;
    }
    // Decide index of key vector to compare with.
    int i = depth % _dim;
    if (key[i] < here->key[i])
        here->children[0] = insert(here->children[0], key, ++depth);
    else
        here->children[1] = insert(here->children[1], key, ++depth);
    return here;
}

// Search from root node and return the node with the key.
Node* KDTree::search(Node* here, std::vector<int> key, int depth)
{
    if (here == nullptr || here->key == key)
        return here;
    // Decide index of key vector to compare with
    int i = depth % _dim;
    if (key[i] < here->key[i])
        return search(here->children[0], key, ++depth);
    else
        return search(here->children[1], key,++depth);
}

// Override Tree's remove method
Node* KDTree::remove(Node* here, std::vector<int> key, int depth) {
    assert("Not implemented yet");
    return _tree;
}

KDTree* testKDTreePrepare() {
    std::vector<std::vector<int>> keyset = {
        {50,50}, {30, 55}, {55,70}, {40, 85}, {65,20}, {60,85}, {61,60}, {70,60}, {65,80}, {75,55}, {70,75},
        {68,72}, {76,78}
    };
    KDTree* tree = new KDTree(2);
    for (int i = 0; i < keyset.size(); i++)
    {
        tree->insert(keyset[i]);
        std::cout << "height: " << tree->height() << std::endl;
    }
    tree->print();
    return tree;
}

void testKDTreeInsert() {
    KDTree* tree = testKDTreePrepare();
    delete tree;
}

void testKDTreeSearch() {
    KDTree* tree = testKDTreePrepare();

    if (tree->exist({60,85})) std::cout << "Key {60,85} found." << std::endl;
    else std::cout << "Key {60,85} not found." << std::endl;

    if (tree->exist({76,78})) std::cout << "Key {76,78} found." << std::endl;
    else std::cout << "Key {76,78} not found." << std::endl;

    if (tree->exist({40, 85})) std::cout << "Key {40, 85} found." << std::endl;
    else std::cout << "Key {40, 85} not found." << std::endl;
#if 0
    tree->remove({40, 85});
    std::cout << "Now key {40, 85} removed." << std::endl;
    tree->print();

    if (tree->exist({40, 85})) std::cout << "Key {40, 85} found." << std::endl;
    else std::cout << "Key {40, 85} not found." << std::endl;
#endif
    delete tree;
}

void testKDTreeRemove() {
    KDTree* tree = testKDTreePrepare();
    std::cout << "Removing {50,50}" << std::endl;
    tree->remove({50,50});
    tree->print();
    std::cout << "Removing {61,60}" << std::endl;
    tree->remove({61,60});
    tree->print();
    delete tree;
}

void testKDTreeBfs() {
    KDTree* tree = testKDTreePrepare();
    std::cout << "Printing tree as above is a typical example of BFS." << std::endl;
    delete tree;
}

void testKDTreeDfs() {
    KDTree* tree = testKDTreePrepare();
    std::cout << "Searching binary tree is a typical example of DFS." << std::endl;
    if (tree->exist({61,60})) std::cout << "Key {61,60} found." << std::endl;
    else std::cout << "Key {61,60} not found." << std::endl;
    delete tree;
}

void testKDTreeNN() {
    KDTree* tree = testKDTreePrepare();
    delete tree;
}
