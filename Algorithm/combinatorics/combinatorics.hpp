//
//  combinatorics.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 31/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef combinatorics_hpp
#define combinatorics_hpp

// Callback Functor
// Will be called by combinatoric fuctions.
//
class Callback {
public:
    virtual bool operator()(const std::vector<int>& pick) const = 0;

};

// Functor for selectCover
//
class Cover {
private:
    std::vector<std::vector<int>> _table;
    
public:
    Cover(std::vector<std::vector<int>> table) : _table(table) {
    }
    bool operator()(std::vector<int> pick) {
       
        std::cout << "dummy\n";
        return true;
    }
};



void testPickList_n_factorial();
void testPickList_nPr();
void testPickList_nCr();
void testSetCover2();

#endif /* combinatorics_hpp */
