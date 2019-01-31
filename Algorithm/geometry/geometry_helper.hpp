//
//  geometry_helper.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 20/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef geometry_helper_hpp
#define geometry_helper_hpp

#include "helper.hpp"
#include <iostream>

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

#endif /* geometry_helper_hpp */
