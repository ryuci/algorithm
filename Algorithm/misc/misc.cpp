//
//  misc.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 18/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//
//  References:
//    [1] Alogorithmic Problem Solving Strategy
//    [2] 쉽게 배우는 알고리듬
//    [3] TSP CITIES - https://people.sc.fsu.edu/~jburkardt/datasets/cities/cities.html
//    [4] https://stackoverflow.com/questions/31120402/complexity-when-generating-all-combinations

#include "helper.hpp"
#include "misc.hpp"
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
#include <random>

//
void testRandom() {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    // distribution in range [0, 10]
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,10);
    
    for (int i = 0; i < 10; i++)
        std::cout << dist(rng) << " ";
    std::cout << std::endl;
}

//
void testRandomShuffle() {
    std::vector<int> data = {0,1,2,3,4,5,6,7,8,9};
    std::mt19937 rng;
    rng.seed(std::random_device()());
    
    for (int i = 0; i < 5; i++) {
        std::shuffle(data.begin(), data.end(), rng);
        print(data);
    }
}

//
void testMax() {
    std::cout << "std::numeric_limits<int>::max() = " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "std::numeric_limits<long>::max() = " << std::numeric_limits<long>::max() << std::endl;
    std::cout << "std::numeric_limits<unsigned int>::max() = " << std::numeric_limits<unsigned int>::max() << std::endl;
    std::cout << "std::numeric_limits<float>::max() = " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "std::numeric_limits<double>::max() = " << std::numeric_limits<double>::max() << std::endl;
}

// Prime Factorization 1
// Reference: [1] pp.105
// Complexity: Loop [2,n]. O(n).
//             If we think each digit as input size, runtime is O(10^n).
//             It's exponential, not polynomial!
//             e.g. 1 digit = 10 loops, 2 digits = 10*10 loops, n digits = 10^n loops.
std::vector<long> primeFactor1(long n) {
    if (n == 1) return std::vector<long>(1, 1);
    std::vector<long> ret;
    for (long i = 2; n > 1; i++) {
        while (n % i == 0) {
            n /= i;
            ret.push_back(i);
        }
    }
    return ret;
}

// Prime Factorization 2
// Reference: [1] pp.497
// Complexity: For composite number n, n = p*q -> p <= sqrt(n), p >= sqrt(n).
//             So we may loop [2,sqrt(n)] instead of [3,n]. O(sqrt[n]).
std::vector<long> primeFactor2(long n) {
    std::vector<long> ret;
    long sqrtn = long(sqrt(n));
    for (long i = 2; i <= sqrtn; ++i) {
        while (n % i == 0) {
            n /= i;
            ret.push_back(i);
        }
    }
    if (n > 1) ret.push_back(n);
    return ret;
}

void testPrimeFactor() {
    std::vector<long> ret;
    std::cout << "primeFactor1(3547)" << ":\n";
    startTimer();
    ret = primeFactor1(3547);
    stopTimer();
    print(ret);

    std::cout << "primeFactor2(3547)" << ":\n";
    startTimer();
    ret = primeFactor2(3547);
    stopTimer();
    print(ret);

    std::cout << "primeFactor1(1000000000000000000)" << ":\n";
    startTimer();
    ret = primeFactor1(1000000000000000000);
    stopTimer();
    print(ret);

    std::cout << "primeFactor2(1000000000000000000)" << ":\n";
    startTimer();
    ret = primeFactor2(1000000000000000000);
    stopTimer();
    print(ret);

    std::cout << "primeFactor1(std::numeric_limits<long>::max())" << ":\n";
    startTimer();
    ret = primeFactor1(std::numeric_limits<long>::max());
    stopTimer();
    print(ret);
    
    std::cout << "primeFactor2(std::numeric_limits<long>::max())" << ":\n";
    startTimer();
    ret = primeFactor2(std::numeric_limits<long>::max());
    stopTimer();
    print(ret);
}

// Check if n is a prime number.
// Reference:
// Complexity: O(n).
bool isPrime1(long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long i = 3; i < n; i++)
        if (n % i == 0) return false;
    return true;
}

// Check if n is a prime number.
// Reference: [1] pp.496
// Complexity: O(sqrt[n]).
bool isPrime2(long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    long sqrtn = long(sqrt(n));
    for (long i = 3; i <= sqrtn; i++)
        if (n % i == 0) return false;
    return true;
}

void testIsPrime() {
    bool ret;
    std::cout << "isPrime1(3547)" << ":\n";
    startTimer();
    ret = isPrime1(3547);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;

    std::cout << "isPrime2(3547)" << ":\n";
    startTimer();
    ret = isPrime2(3547);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;

    std::cout << "isPrime1(10000000000000000)" << ":\n";
    startTimer();
    ret = isPrime1(10000000000000000);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;

    std::cout << "isPrime2(10000000000000000)" << ":\n";
    startTimer();
    ret = isPrime2(10000000000000000);
    stopTimer();
    std::cout << std::boolalpha << ret << std::endl;
}



