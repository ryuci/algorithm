//
//  helper.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 18/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef helper_hpp
#define helper_hpp

#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <algorithm>

template <typename T>
struct Point {
    T x, y;
    Point() {};
    Point(T x, T y) : x(x), y(y) {};
};

template <typename T>
void print(std::vector<T> const &v)
{
    for (T i = 0; i < v.size(); i++) {
        std::cout << v.at(i);
        if (i != v.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
void print(std::deque<T> const &d)
{
    for (T i = 0; i < d.size(); i++) {
        std::cout << d.at(i);
        if (i != d.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
void print(std::vector< std::vector<T> > const &v)
{
    for (T i = 0; i < v.size(); i++) {
        for (T j = 0; j < v[i].size(); j++) {
            std::cout << v[i].at(j);
            if (j != v.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

void startTimer();
void stopTimer();
double stopTimerRet();
int writeCSV(std::string fname, std::vector< Point<int> >& data);
void displayMenu(std::vector< std::pair<std::string,void (*)()> > menu, std::string title);
void NA();


#endif /* helper_hpp */
