//
//  Tree.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include <string>
#include <queue>
#include <list>
#include <type_traits>
#include "tree.hpp"

// Constructor
Tree::Tree() : _tree(nullptr), _depth(0) {}

// External APIs, hiding reference to _tree.
void Tree::print(Node* here) { bfs(here, nullptr); }
void Tree::insert(std::vector<int> key) { _tree = insert(_tree, key); }
void Tree::search(std::vector<int> key) { _tree = search(_tree, key); }
void Tree::remove(std::vector<int> key) { _tree = remove(_tree, key); }
bool Tree::exist(std::vector<int> key) { Node* tmp = search(_tree, key); return (tmp && (tmp->key == key)); }
int Tree::height() { return height(_tree); }
void Tree::print() { print(_tree); std::cout << "height: " << height() << std::endl; }

// Make new node.
Node* Tree::makeNode(std::vector<int> key) {
    Node* tmp = new Node();
    tmp->key = key;
    // TODO:15Jan2019: Binary tree is assumed!
    Node* left = nullptr;
    Node* right = nullptr;
    tmp->children.push_back(left);
    tmp->children.push_back(right);
    return tmp;
}

// Insert new node and return the updated root node or tree.
Node* Tree::insert(Node* here, std::vector<int> key) {
    if (here == nullptr) {
        here = makeNode(key);
        print(here);
    }
    // TODO:15Jan2019: Binary tree is assumed!
    else if (key < here->key)
        here->children[0] = insert(here->children[0], key);
    else
        here->children[1] = insert(here->children[1], key);
    return here;
}

// Search from root node and return the node with the key.
Node* Tree::search(Node* here, std::vector<int> key)
{
    if (here == nullptr || here->key == key)
        return here;
    if (key < here->key)
        return search(here->children[0], key);
    else
        return search(here->children[1], key);
}

// Search from root node and find/remove the node with the key.
// Return the updated root node or tree.
Node* Tree::remove(Node* here, std::vector<int> key)
{
    if (here == nullptr)
        return here;
    
    if (key < here->key)
        here->children[0] = remove(here->children[0], key);
    else if (key > here->key)
        here->children[1] = remove(here->children[1], key);
    else {
        Node* tmp;
        // Found the node to delete
        // Case 1: 'here' has no child -> Delete 'here' and return null
        // Case 2: 'here' has a single child -> Delete 'here' and return the single child
        // Case 3: 'here' has two children -> Find tmp which is max key from left child tree or min key from right child tree
        //                                 -> Change 'here''s key to tmp's key, and remove tmp's key from the right child tree of 'here'
        //                                 -> Note that tmp should have only one child.
        //                                 -> Here we will use min key from right child tree, to find which, we just go left until we can't
        if (here->children[0] == nullptr)
        {
            // Case 1 + Case 2
            tmp = here->children[1];
            delete here;
            return tmp;
        }
        else if (here->children[1] == nullptr)
        {
            // Case 2
            tmp = here->children[0];
            delete here;
            return tmp;
        }
        // Case 3:
        tmp = here->children[1];
        while (tmp->children[0] != nullptr) {
            tmp = tmp->children[0];
        }
        here->key = tmp->key;
        here->children[1] = remove(here->children[1], tmp->key);
    }
    return here;
}

// Calculate tree height by finding max heights of children trees, then plus 1.
int Tree::height(Node* here) {
    int h = 0;
    if (here == nullptr)
        return 0;
    for (int i = 0; i < here->children.size(); i++) {
        h = std::max(h, 1 + height(here->children[i]));
    }
    return h;
}

// Breadth-First search
void Tree::bfs(Node* here, void (*callback)()=nullptr) {
    // Queue is made of list, where list contains nodes
    std::queue<Node*, std::list<Node*>> q;
    
    if (here == nullptr) {
        std::cout << "Tree is empty.";
        return;
    }
    q.push(here);
    std::cout << "bfs() visiting " << here << std::endl;
    if (callback != nullptr) callback();
    while (!q.empty()) {
        Node* tmp = q.front();
        q.pop();
#if 1
        printKey(tmp->key);
#endif
        // TODO:15Jan2019: Binary tree is assumed!
        if (tmp->children[0] != nullptr) q.push(tmp->children[0]);
        if (tmp->children[1] != nullptr) q.push(tmp->children[1]);
    }
    std::cout << std::endl;
}

// TODO:15Jan2019 Implement dfs()
// Depth-First search
void Tree::dfs(Node* here, void (*callback)()=nullptr) {
    std::cout << "dfs() visiting ";
    for (int i = 0; i < here->key.size(); i++)
        std::cout << here->key[i] << ",";
    std::cout << std::endl;
    
    if (callback != nullptr) callback();
    
    for (int i = 0; i < here->children.size(); i++) {
        dfs(here->children[i], callback);
    }
}

// Print key
void Tree::printKey(std::vector<int> key) {
    for (int i = 0; i < key.size(); i++) {
        std::cout << key[i];
        if (i != (key.size() - 1)) std::cout << ",";
    }
    std::cout << "|";
}

Tree* testTreePrepare() {
    std::vector<std::vector<int>> keyset = {{30}, {20}, {25}, {40}, {35}, {100}, {1000}, {234}, {18}, {34}, {56}, {77}};
    Tree* tree = new Tree;
    for (int i = 0; i < keyset.size(); i++)
    {
        tree->insert(keyset[i]);
        std::cout << "height: " << tree->height() << std::endl;
    }
    tree->print();
    return tree;
}

void testTreeInsert() {
    Tree* tree = testTreePrepare();
    delete tree;
}

void testTreeSearch() {
    Tree* tree = testTreePrepare();
    if (tree->exist({40})) std::cout << "Key 40 found." << std::endl;
    else std::cout << "Key 40 not found." << std::endl;
    if (tree->exist({234})) std::cout << "Key 234 found." << std::endl;
    else std::cout << "Key 234 not found." << std::endl;
    if (tree->exist({70})) std::cout << "Key 70 found." << std::endl;
    else std::cout << "Key 70 not found." << std::endl;
    if (tree->exist({30})) std::cout << "Key 30 found." << std::endl;
    else std::cout << "Key 30 not found." << std::endl;
    tree->remove({30});
    std::cout << "Now key 30 removed." << std::endl;
    tree->print();
    if (tree->exist({30})) std::cout << "Key 30 found." << std::endl;
    else std::cout << "Key 30 not found." << std::endl;
    delete tree;
}

void testTreeRemove() {
    Tree* tree = testTreePrepare();
    std::cout << "Removing 40" << std::endl;
    tree->remove({40});
    tree->print();
    std::cout << "Removing 234" << std::endl;
    tree->remove({234});
    tree->print();
    std::cout << "Removing 30" << std::endl;
    tree->remove({30});
    tree->print();
    std::cout << "Inserting 40" << std::endl;
    tree->insert({30});
    tree->print();
    delete tree;
}

void testTreeBfs() {
    Tree* tree = testTreePrepare();
    std::cout << "Printing tree as above is a typical example of BFS." << std::endl;
    delete tree;
}

void testTreeDfs() {
    Tree* tree = testTreePrepare();
    std::cout << "Searching binary tree is a typical example of DFS." << std::endl;
    if (tree->exist({40})) std::cout << "Key 40 found." << std::endl;
    else std::cout << "Key 40 not found." << std::endl;
    delete tree;
}

