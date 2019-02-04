//
//  geometry.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 20/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "geometry.hpp"
#include <iostream>
#include <memory>
#include <Python/Python.h>
// gcc -shared -o sample.so sample.c -framework Python

// Check if other is located in counterclock wise direction.
// Positive -> counterclock.
double ccw(Vector2 a, Vector2 b) {
    return a.outer(b);
}

// When p is the origin, check if A is located in counterclock wise direction from B.
// Positive -> counterclock.
bool ccw(Vector2 p, Vector2 a, Vector2 b) {
    return ccw(a-p, b-p);
}


// Get interection x of two L1 and L2 where a+pb in L1 and c+qd in L2.
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x) {
    if (b.outer(d) < 1e-7)
        // denominator == 0, b and d are in parallel.
        return false;
    x = a + (c-a); //.outer(d) / b.outer(d);
    return true;
}

// Just check if there is a intersection.
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        if (b < a) std::swap(a, b);
        if (d < c) std::swap(c, d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

// Get interection x from parallel segment.
bool parallelSegment(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x) {
    // Note we assume b < a -> b.x < a.x || b.x >= a.x && b.y < a.y
    // Also assume a < b in ab.
    if (b < a) std::swap(a, b);
    if (d < c) std::swap(c, d);
    // ab and cb should be overlapped.
    if (ccw(a,b,c) != 0) return false;
    // Disconneted.
    if (b < c || d < a) return false;
    // Find one intersection.
    if (a < c) x = c;
    else x = a;
    return true;
}

bool inBoundingRectangle(Vector2 p, Vector2 a, Vector2 b) {
    if (b < a) std::swap(a, b);
    return p == a || p == b || (a < p && p < b);
}

bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x) {
    if (!lineIntersection(a, b, c, d, x))
        return parallelSegment(a, b, c, d, x);
    return inBoundingRectangle(x, a, b) && inBoundingRectangle(x, c, d);
}


// Check if two rectangles are overlapped.
// Do not confused with coordinate system.
// Here x grows as we move to right and y to up.
// Rectangle will represented by two points, top-left and bottom-right.
template <typename T>
bool isOverlap(Rectangle<T> rect1, Rectangle<T> rect2) {
#if 1
    std::cout << "First: "; rect1.print(); std::cout << std::endl;
    std::cout << "Second: "; rect2.print(); std::cout << std::endl;
#endif
    if (rect1.br.x < rect2.tl.x || rect2.br.x < rect1.tl.x)
        return false;
    if (rect1.tl.y < rect2.br.y || rect2.tl.y < rect1.br.y)
        return false;
    return true;
}

// Get overlapped rectangle area.
//
template <typename T>
std::unique_ptr<Rectangle<int>> overlapArea(Rectangle<T> rect1, Rectangle<T> rect2) {
    if (!isOverlap(rect1, rect2))
        return std::unique_ptr<Rectangle<int>>(new Rectangle<int>()); //  Rectangle<int>();
    Point<int> tl = {
        std::max(rect1.tl.x, rect2.tl.x),
        std::min(rect1.tl.y, rect2.tl.y)
    };
    Point<int> br = {
        std::min(rect1.br.x, rect2.br.x),
        std::max(rect1.br.y, rect2.br.y)
    };
    return std::unique_ptr<Rectangle<int>>(new Rectangle<int>(tl,br));
}

void testRectOverlap() {
    bool ret;

    Rectangle<int> A({0, 10}, 10, 10);
    Rectangle<int> B({5, 10}, 10, 10);
    ret = isOverlap(A, B);
    std::cout << "isOverlap(A, B) = " << std::boolalpha << ret << std::endl;
    assert(ret == true);
    ret = isOverlap(B, A);
    std::cout << "isOverlap(B, A) = " << std::boolalpha << ret << "\n\n";
    assert(ret == true);

    A = Rectangle<int>({0, 10}, 10, 10);
    B = Rectangle<int>({10, 10}, 10, 10);
    ret = isOverlap(A, B);
    std::cout << "isOverlap(A, B) = " << std::boolalpha << ret << std::endl;
    assert(ret == true);
    ret = isOverlap(B, A);
    std::cout << "isOverlap(B, A) = " << std::boolalpha << ret << "\n\n";
    assert(ret == true);

    A = Rectangle<int>({0, 10}, 10, 10);
    B = Rectangle<int>({20, 10}, 10, 10);
    ret = isOverlap(A, B);
    std::cout << "isOverlap(A, B) = " << std::boolalpha << ret << std::endl;
    assert(ret == false);
    ret = isOverlap(B, A);
    std::cout << "isOverlap(B, A) = " << std::boolalpha << ret << "\n\n";
    assert(ret == false);

    A = Rectangle<int>({0, 10}, 10, 10);
    B = Rectangle<int>({0, 15}, 10, 10);
    ret = isOverlap(A, B);
    std::cout << "isOverlap(A, B) = " << std::boolalpha << ret << std::endl;
    assert(ret == true);
    ret = isOverlap(B, A);
    std::cout << "isOverlap(B, A) = " << std::boolalpha << ret << "\n\n";
    assert(ret == true);

    A = Rectangle<int>({0, 10}, 10, 10);
    B = Rectangle<int>({0, 20}, 10, 10);
    ret = isOverlap(A, B);
    std::cout << "isOverlap(A, B) = " << std::boolalpha << ret << std::endl;
    assert(ret == true);
    ret = isOverlap(B, A);
    std::cout << "isOverlap(B, A) = " << std::boolalpha << ret << "\n\n";
    assert(ret == true);

    A = Rectangle<int>({0, 10}, 10, 10);
    B = Rectangle<int>({0, 30}, 10, 10);
    ret = isOverlap(A, B);
    std::cout << "isOverlap(A, B) = " << std::boolalpha << ret << std::endl;
    assert(ret == false);
    ret = isOverlap(B, A);
    std::cout << "isOverlap(B, A) = " << std::boolalpha << ret << "\n\n";
    assert(ret == false);

    std::unique_ptr<Rectangle<int>> ret2;
    A = Rectangle<int>({0, 10}, 10, 10);
    B = Rectangle<int>({0, 15}, 10, 10);
    ret2 = overlapArea(A, B);
    std::cout << "overlapArea(A, B) = "; ret2->print(); std::cout << std::endl;
    assert(*ret2 == Rectangle<int>({0, 10}, 10, 5));
    ret2 = overlapArea(B, A);
    std::cout << "overlapArea(B, A) = "; ret2->print(); std::cout << std::endl;
    assert(*ret2 == Rectangle<int>({0, 10}, 10, 5));

    A = Rectangle<int>({0, 10}, 15, 10);
    B = Rectangle<int>({5, 15}, 5, 10);
    ret2 = overlapArea(A, B);
    std::cout << "overlapArea(A, B) = "; ret2->print(); std::cout << std::endl;
    assert(*ret2 == Rectangle<int>({5, 10}, 5, 5));
    ret2 = overlapArea(B, A);
    std::cout << "overlapArea(B, A) = "; ret2->print(); std::cout << std::endl;
    assert(*ret2 == Rectangle<int>({5, 10}, 5, 5));
}

void testIntersection() {
    
    Vector2 ans;
    //if (lineIntersection(Vector2(1.0, 2.0), Vector2(2.5, 2.0), Vector2(3.0, -1.0), Vector2(7.0, 9.0), ans))
    if (lineIntersection({1.0, 2.0}, {2.5, 2.0}, {3.0, -1.0}, {7.0, 9.0}, ans))
        std::cout << "lineIntersection = (" << ans.x << "," << ans.y << ")\n";
    else
        std::cout << "lineIntersection = None\n";

    if (lineIntersection({1.0, 2.0}, {2.5, 2.0}, {3.0, -1.0}, {7.0, 9.0}))
        std::cout << "lineIntersection = True\n";
    else
        std::cout << "lineIntersection = None\n";

    if (segmentIntersection({1.0f, 2.0f}, {2.5f, 2.0f}, {1.0f, 2.0f}, {5.0f, 4.0f}, ans))
        std::cout << "segmentIntersection = (" << ans.x << "," << ans.y << ")\n";
    else
    std::cout << "segmentIntersection = None\n";

}

