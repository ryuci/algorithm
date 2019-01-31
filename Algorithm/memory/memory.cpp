//
//  memory.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 19/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "memory.hpp"
#include <vector>

void testEratosthenes() {
    
}

static const int MAX_SIZE = 20;
static char picture[MAX_SIZE][MAX_SIZE];

// Print Picture
//
static void print() {
    
}

// Decompress code tree.
//
static void decompressQuadTree(std::string::iterator& it, int y, int x, int size) {
    char head = *(it++);
    if (head == 'b' || head == 'w') {
        // Fill in.
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                picture[y + i][x + j] = head;
    }
    else {
        int half = size / 2;
        decompressQuadTree(it, y, x, half);
        decompressQuadTree(it, y, x + half, half);
        decompressQuadTree(it, y + half, x, half);
        decompressQuadTree(it, y + half, x + half, half);
    }
}

// Reverse Quad Tree
// Problem: If we take decompress, reverse, compress approach, it takes huge memory.
//          So, we need to find out how to reverse without full decompression.
// Complexity: 
static std::string reverseQuadTree(std::string::iterator& it) {
    char head = *(it++);
    if (head == 'b' || head == 'w')
        return std::string(1, head);
    std::string tl = reverseQuadTree(it);
    std::string tr = reverseQuadTree(it);
    std::string bl = reverseQuadTree(it);
    std::string br = reverseQuadTree(it);
    // Merge by exchanging top and bottom.
    return "x" + bl + br + tl + tr;
}

void testReverseQuadTree() {
    std::vector<std::string> problems = {
        "w",
        "xbwwb",
        "xbwxwbbwb",
        "xxwwwbxwxwbbbwwxxxwwbbbwwwwbb",
    };
    std::vector<std::string> solutions = {
        "w",
        "xwbbw",
        "xxbwwbbbw",
        "xxwbxwwxbbwwbwbxwbwwxwwwxbbwb",
    };
    for (int i = 0; i < problems.size(); i++) {
#if 1
        std::string::iterator it = problems[i].begin();
        std::cout << reverseQuadTree(it) << std::endl;
        // Reset iterator.
        it = problems[i].begin();
        assert(reverseQuadTree(it) == solutions[i]);
        it = problems[i].begin();
        decompressQuadTree(it, 0, 0, MAX_SIZE);
        print();
        it = solutions[i].begin();
        decompressQuadTree(it, 0, 0, MAX_SIZE);
        print();
#else
        // TODO:1-22-2019: Find out why we can't pass iteration string.begin() as
        //                 a reference. It doesn't look like const.
        std::cout << reverseQuadTree(problems[i].begin()) << std::endl;
        assert(reverseQuadTree(problems[i].begin()) == solutions[i]);
#endif
    }
}
