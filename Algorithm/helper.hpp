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
#include <cmath>

//
// STL VECTORS
//

typedef std::vector<bool> VB;
typedef std::vector<int> VI;
typedef std::vector<double> VD;
typedef std::vector<std::vector<bool>> VVB;
typedef std::vector<std::vector<int>> VVI;
typedef std::vector<std::vector<double>> VVD;

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

// Make my own PI instead of using cmath's M_PI.
//const double PI = 2.0 * acos(0);
const double PI = 4.0 * acos(1);

struct vector2 {
    double x, y;
    
    // Prohibit automatic type conversion.
    explicit vector2(double x = 0, double y = 0) : x(x), y(y) {
    }
    
    bool operator==(const vector2& other) const {
        return x == other.x && y == other.y;
    }
    
    // Deliberate definition of comparison. Will pay later.
    bool operator<(const vector2& other) const {
        return x != other.x ? x < other.x : y < other.y;
    }
    
    vector2 operator+(const vector2& other) const {
        return vector2(x + other.x, y + other.y);
    }
    
    vector2 operator-(const vector2& other) const {
        return vector2(x - other.x, y - other.y);
    }
    
    vector2 operator*(double other) const {
        return vector2(x * other, y * other);
    }
    
    double norm() const {
        // hypotenuse
        return hypot(x, y);
    }
    
    vector2 normalize() const {
        return vector2(x / norm(), y/ norm());
    }
    
    // Angle, a.k.a polar angle or azimuth, measured counterclockwise from the positive x axis, or polar axis.
    double polar() const {
        // Note atan2(y, x) -> [-PI..PI).
        // Make result between [0..2PI) instaed of [-PI..PI).
        return fmod(atan2(y, x) + 2 * PI, 2 * PI);
    }
    
    // Inner product = |a||b|cos(theta)
    // Usage: Find angle, orthogonality, projection.
    double inner(const vector2& other) const {
        return x * other.x + y * other.y;
    }
    
    // Outer product = = |a||b|sin(theta)
    // Usage: Area of parallelogram, especially area of triangle by diving the parallelogram.
    //        Find direction of theta or sign of theta. i.e. outer is negative, theta is negative.
    double outer(const vector2& other) const {
        return x * other.y - other.x * y;
    }
    
    // Project this to other.
    vector2 project(const vector2& other) const {
        vector2 r = other.normalize();
        return r * r.inner(*this);
    }
    // Find the nearest point from me between A and B. Return the nearest one in vector2 form.
    // TODO:1-30-2019: sqrt() will be involoved. Complexity of sqrt()?
    //       Isn't it possible just using + or - instead of sqrt()?
    //       Let's find out sqrt() algorithm. -->
    vector2 nearest(vector2 a, vector2 b) {
        if ((*this - a).norm() > (*this - b).norm()) return a;
        else return b;
    }
    
    // Angle between two vectors.
    double angle(vector2 other) {
        return acos(inner(other) / (norm() * other.norm()));
    }
    
    // Check if othogonal to each other.
    bool orthogonal(vector2 other) {
        if (norm() != 0 && other.norm() != 0)
            return inner(other) == 0 ? true : false;
        return false;
    }
    
    // Check if other is located in counterclock wise direction.
    // Positive -> counterclock.
    bool ccw(vector2 other) {
        if (outer(other) > 0) return true;
        else return false;
    }
    
    // When *this is the origin, check if A is located in counterclock wise direction from B.
    // Positive -> counterclock.
    bool ccw(vector2 a, vector2 b) {
        return (a - *this).outer(b - *this);
    }
};


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
