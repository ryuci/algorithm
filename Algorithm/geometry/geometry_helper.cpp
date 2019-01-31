//
//  geometry_helper.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 20/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "geometry_helper.hpp"
#include <cmath>

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


