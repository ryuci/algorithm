//
//  geometry.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 20/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#ifndef geometry_hpp
#define geometry_hpp

void testRectOverlap();
void testIntersection();




namespace geometry {
    class QuadTree;
}

// Make my own PI instead of using cmath's M_PI.
//const double PI = 2.0 * acos(0);
const double MY_PI = 4.0 * acos(1);

struct Vector2 {
    double x, y;
    
    // Prohibit automatic type conversion.
    /*explicit*/ Vector2(double x = 0, double y = 0) : x(x), y(y) {
    }
    
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
    
    // Deliberate definition of comparison. Will pay later.
    bool operator<(const Vector2& other) const {
        return x != other.x ? x < other.x : y < other.y;
    }
    
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    
    Vector2 operator*(double other) const {
        return Vector2(x * other, y * other);
    }

    Vector2 operator/(double other) const {
        return Vector2(x / other, y / other);
    }

    double norm() const {
        // hypotenuse
        return hypot(x, y);
    }
    
    Vector2 normalize() const {
        return Vector2(x / norm(), y/ norm());
    }
    
    // Angle, a.k.a polar angle or azimuth, measured counterclockwise from the positive x axis, or polar axis.
    double polar() const {
        // Note atan2(y, x) -> [-PI..PI).
        // Make result between [0..2PI) instaed of [-PI..PI).
        return fmod(atan2(y, x) + 2 * MY_PI, 2 * MY_PI);
    }
    
    // Inner product = |a||b|cos(theta)
    // Usage: Find angle, orthogonality, projection.
    double inner(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
    
    // Outer product = = |a||b|sin(theta)
    // Usage: Area of parallelogram, especially area of triangle by diving the parallelogram.
    //        Find direction of theta or sign of theta. i.e. outer is negative, theta is negative.
    double outer(const Vector2& other) const {
        return x * other.y - other.x * y;
    }
    
    // Project this to other.
    Vector2 project(const Vector2& other) const {
        Vector2 r = other.normalize();
        return r * r.inner(*this);
    }
    // Find the nearest point from me among A and B. Return the nearest one in vector2 form.
    // TODO:1-30-2019: sqrt() will be involoved. Complexity of sqrt()?
    //       Isn't it possible just using + or - instead of sqrt()?
    //       Let's find out sqrt() algorithm. -->
    Vector2 nearest(Vector2 a, Vector2 b) {
        if ((*this - a).norm() > (*this - b).norm()) return a;
        else return b;
    }
    
    // Angle between two vectors.
    double angle(Vector2 other) {
        return acos(inner(other) / (norm() * other.norm()));
    }
    
    // Check if othogonal to each other.
    bool orthogonal(Vector2 other) {
        if (norm() != 0 && other.norm() != 0)
            return inner(other) == 0 ? true : false;
        return false;
    }
    
};

double ccw(Vector2 a, Vector2 b);
bool ccw(Vector2 p, Vector2 a, Vector2 b);
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x);
bool parallelSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x);


#endif /* geometry_hpp */
