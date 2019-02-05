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
#include <string>
#include <memory>
#include <cmath>

//
// TYPO-PRONE NUMBERS
//
#define MILLION  (1000*1000)
#define BILLION  (1000*MILLION)
#define TRILLION (1000*BILLION)
#define QUADRILLION (1000*TRILLION)

//
//
//

#define HR (std::cout << "---" << std::endl)


//
// GEOMETRY
//

template <typename T>
struct Point {
    T x, y;
    Point() {};
    Point(T x, T y) : x(x), y(y) {};
    bool operator==(Point other) {
        return x == other.x && y == other.y;
    }
};

typedef Point<double> PD;
typedef Point<int> PI;


// Do not confused with coordinate system.
// Here x grows as we move to right and y to up.
//  y ^
//    |
//    +--->x
// Rectangle will represented by two points, top-left and bottom-right.
template <typename T>
class Rectangle {
public:
    Point<T> tl, br;
    Rectangle() {
    }
    Rectangle(Point<T> tl, Point<T> br) : tl(tl), br(br) {
    }
    Rectangle(Point<T> tl, T width, T height) : tl(tl) {
        br = {tl.x + width, tl.y - height};
    }
    void print() {
        std::cout << "(" << tl.x << "," << tl.y << ")"
        << "(" << br.x << "," << br.y << ")";
    }
    bool operator==(Rectangle<T> other) {
        return (other.tl.x == this->tl.x) &&
        (other.tl.y == this->tl.y) &&
        (other.br.x == this->br.x) &&
        (other.br.y == this->br.y);
    }
};

template <typename T>
class Triangle {
public:
    Point<T> a, b, c;
    Triangle() {
    }
    Triangle(Point<T> a, Point<T> b, Point<T> c) : a(a), b(b), c(c) {
    }
    float area() {
        // |x1 x2 x3|
        // |y1 y2 y3| * (1/2)
        return (a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y)/2.;
    }
    void print() {
        std::cout << "(" << a.x << "," << a.y << ")"
        << "(" << b.x << "," << b.y << ")"
        << "(" << c.x << "," << c.y << ")";
    }
    bool operator==(Triangle<T> other) {
        return (other.a.x == this->a.x) &&
        (other.a.y == this->a.y) &&
        (other.b.x == this->b.x) &&
        (other.b.y == this->b.y) &&
        (other.c.x == this->c.x) &&
        (other.c.y == this->c.y);
    }
};


//
// STL VECTORS
//

typedef std::vector<bool> VB;
typedef std::vector<int> VI;
typedef std::vector<long> VL;
typedef std::vector<double> VD;
typedef std::vector<std::string> VS;
typedef std::vector<std::vector<bool>> VVB;
typedef std::vector<std::vector<int>> VVI;
typedef std::vector<std::vector<long>> VVL;
typedef std::vector<std::vector<double>> VVD;
typedef std::vector<Point<int>> VPI;
typedef std::vector<Point<long>> VPL;
typedef std::vector<Point<double>> VPD;


//
// PRINT STL CONTAINERS
//

std::ostream& operator<<(std::ostream& os, const Point<int>& pt);
std::ostream& operator<<(std::ostream& os, const std::vector<Point<int>>& v);

template <typename T>
void print(std::vector<T> const &v)
{
    for (int i = 0; i < v.size(); i++) {
        std::cout << v.at(i);
        if (i != v.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
void print(std::deque<T> const &d)
{
    for (int i = 0; i < d.size(); i++) {
        std::cout << d.at(i);
        if (i != d.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
void print(std::vector< std::vector<T> > const &v)
{
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            std::cout << v[i].at(j);
            if (j != v.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

//
// GEOMETRY
//

void startTimer();
void stopTimer();
double stopTimerRet();
int writeCSV(std::string fname, std::vector< Point<int> >& data);
void displayMenu(std::vector< std::pair<std::string,void (*)()> > menu, std::string title);
void NA();


#endif /* helper_hpp */
