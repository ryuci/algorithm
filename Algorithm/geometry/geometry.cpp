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
