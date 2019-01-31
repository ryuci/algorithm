//
//  sorting.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 21/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "runtime.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Selection Sort
//
void selectionSort(std::vector<int>::iterator b, std::vector<int>::iterator  e) {
    
}

// Bubble Sort
//
void bubbleSort(std::vector<int>::iterator b, std::vector<int>::iterator  e) {
    
}

// Insersion Sort
//
void insersionSort(std::vector<int>::iterator b, std::vector<int>::iterator  e) {
    
}

// Merge Sort
// T(n) = 2T(n/2) + cn -> O(nlogn)
//
void mergeSort(std::vector<int>::iterator b, std::vector<int>::iterator  e)
{
    static int mcount = 1, ccount = 1;
    if (b < e - 1)
    {
#if 1
        std::cout << "merge_sort() call #" << ccount++ << ": ";
        for (std::vector<int>::iterator i = b; i < e; i++) std::cout << *i << " ";
        std::cout << std::endl;
#endif
        // 2 * T(n/2)
        std::vector<int>::iterator m = b + floor((e - b) / 2);
        mergeSort(b, m);
        mergeSort(m, e);
        
        std::cout << "Merging ";
        for (std::vector<int>::iterator i = b; i < m; i++) std::cout << *i << " ";
        std::cout << "and ";
        for (std::vector<int>::iterator i = m; i < e; i++) std::cout << *i << " ";
        std::cout << std::endl;
        
        // n readings and n-1 comparisons -> O(n) or loosely cn.
        std::inplace_merge(b, m, e);
        
        std::cout << "Merged #" << mcount++ << ": ";
        for (std::vector<int>::iterator i = b; i < e; i++) std::cout << *i << " ";
        std::cout << std::endl;
    }
}

// Quick Sort Partition
// Goal: Pick last one as ref. Then, put smaller numbers than ref in the left side
//       and bigger ones in the right side of ref.
//
std::vector<int>::iterator partition(std::vector<int>::iterator b, std::vector<int>::iterator e)
{
    // Use last one as a refernce.
    int ref = *(e - 1);
    std::vector<int>::iterator smaller = b - 1;
    // Read from begin to end - 1.
    for (std::vector<int>::iterator read = b; read < e - 1; read++) {
        // Swap if current read is smaller than ref.
        if (*read <= ref) std::swap(*(++smaller), *read);
    }
    std::swap(*(smaller + 1), *(e - 1));
    return smaller + 1;
}

// Quick Sort
//
void quickSort(std::vector<int>::iterator b, std::vector<int>::iterator  e)
{
    static int pcount = 1, ccount = 1, rcount = 1;
    if (b < e - 1) {
#if 1
        std::cout << "quick_sort() call #" << ccount++ << ": ";
        for (std::vector<int>::iterator i = b; i < e; i++) std::cout << *i << " ";
        std::cout << std::endl;
#endif
        std::vector<int>::iterator q = partition(b ,e);
#if 1
        std::cout << "partition(" << *q << ") #" << pcount++ << ": ";
        for (std::vector<int>::iterator i = b; i < e; i++) std::cout << *i << " ";
        std::cout << std::endl;
#endif
        quickSort(b, q);
        quickSort(q + 1, e);
#if 1
        std::cout << "result #" << rcount++ << ": ";
        for (std::vector<int>::iterator i = b; i < e; i++) std::cout << *i << " ";
        std::cout << std::endl;
#endif
    }
}

// Heapify
// n: Size of heap [0..n-1]
// root: Node index.
//
void heapify(std::vector<int>& data, int root, int n)
{
    int left = 2 * root + 1, right = 2 * root + 2;
    int smallerChild;
    
    std::cout << "heapify(" << std::to_string(data[root]) << ") begin\n";
    print(data);
    
    // Find smaller one between two children.
    if (right < n) {
        // k has two children.
        if (data[left] < data[right])
            smallerChild = left;
        else
            smallerChild = right;
    }
    else if (left < n)
        // k has left child only.
        smallerChild = left;
    else
        // k hss no child, i.e. k is a leaf.
        return;
    
    // If child is smaller than root, child should be the root.
    // Min heap is assumed.
    if (data[smallerChild] < data[root]) {
        std::swap(data[root], data[smallerChild]);
        // Recursively heapify the affected sub-tree.
        heapify(data, smallerChild, n);
    }
    std::cout << "heapify() end\n";
    print(data);
}

// Build Initial Heap
//
void buildHeap(std::vector<int>& data)
{
    std::cout << "build_heap() start\n";
    print(data);
    
    // In heap, # of root node is (int)n/2.
    // Heapify starting from the last root node.
    for (int root = (int)data.size() / 2 - 1; root >= 0; --root)
        heapify(data, root, (int)data.size());
    
    std::cout << "build_heap() end\n";
    print(data);
}

// Heap Sort
// All comparison based sorting has O(nlogn) as lower bould.
// So is heap sort.
//
void heapSort(std::vector<int>& data)
{
    buildHeap(data);
    
    // Extract from top root one by one
    // by moving top root to the end of heap.
    for (int i = (int)data.size() - 1; i >= 0; i--) {
        // Move current root to end.
        std::swap(data[0], data[i]);
        // Heapify the reduced heap from new root.
        heapify(data, 0, i);
    }
    // Heap is sorted in reverse order.
    // i.e. Min-heap: descending, Max-heap: ascending
}

// Counting Sort
// Useful whan there are n numbers whose max << n.
// It is assumed n >= 0 for covenience' sake.
// O(n) + O(n) = O(n)
//
void countingSort(std::vector<int>& data, int maxNum)
{
    int n = (int)data.size();
    std::vector<int> outputArray(n);
    std::vector<int> countingArray(maxNum + 1, 0);

    // Count occurrence of each data.
    // O(n)
    for (int i = 0; i < n; ++i)
        ++countingArray[data[i]];
    
    // TODO:1-30-2019: Books and internet codes are saying we need to get
    //                 accumulated occurrence. Is it necessary?
    //                 Am I missing something?
    
    // Get accumulated occurrence of each data.
    // Will be used in finding the proper position in outputArray.
    //for (int i = 1; i <= maxNum; i++)
     //   countingArray[i] += countingArray[i - 1];
    
    // Build the output array.
    // O(n)
    for (int i = 0, write = 0; i <= maxNum; i++) {
        for (int j = 0; j < countingArray[i]; j++)
            outputArray[write++] = i;
    }
    data = outputArray;
    print(data);
}

// Counting Sort 2
// Modified to be used by radix sort.
// Assumed data is in natural numbers.
// O(n) + O(10) + O(n) = O(n)
//
void countingSort2(std::vector<int>& data, int digitPlace)
{
    int n = (int)data.size();
    std::vector<int> outputArray(n);
    std::vector<int> countingArray(10, 0);

    // Count occurrence of given digit.
    // O(n)
    for (int i = 0; i < n; ++i)
        ++countingArray[(data[i] / (int)pow(10, digitPlace - 1)) % 10];

    // Get accumulated occurrence of each data.
    // Will be used in finding the proper position in outputArray.
    // O(10)
    for (int i = 1; i < 10; i++)
       countingArray[i] += countingArray[i - 1];

    // Build the output array.
    // O(n)
    for (int i = n - 1; i >= 0; --i)
    {
        outputArray[countingArray[(data[i] / (int)pow(10, digitPlace - 1)) % 10] - 1] = data[i];
        countingArray[(data[i] / (int)pow(10, digitPlace - 1)) % 10]--;
    }
    data = outputArray;
}

// Radix Sort
// O(maxDigits * n) = O(n)!!
//
void radixSort(std::vector<int>& data, int maxDigits)
{
    std::cout << "radix_sort() begin\n";
    print(data);
   
    for (int digitPlace = 1; digitPlace <= maxDigits; ++digitPlace)
        countingSort2(data, digitPlace);
    
    std::cout << "radix_sort() end\n";
    print(data);
}



void testMergeSort() {
    std::vector<int> data = {38, 47, 43, 3, 9, 82, 10};
    mergeSort(data.begin(), data.end());
    assert(data == std::vector<int>({3, 9, 10, 38, 43, 47, 82}));
    std::cout << "MERGE SORT TEST PASS!\n";
}

void testQuickSort() {
    std::vector<int> data = {38, 47, 43, 3, 9, 82, 10};
    quickSort(data.begin(), data.end());
    assert(data == std::vector<int>({3, 9, 10, 38, 43, 47, 82}));
    std::cout << "QUICK SORT TEST PASS!\n";
}

void testHeapSort() {
    std::vector<int> data = {38, 47, 43, 3, 9, 82, 10};
    //build_heap(data);
    heapSort(data);
    assert(data == std::vector<int>({82, 47, 43, 38, 10, 9, 3}));
    std::cout << "HEAP SORT TEST PASS!\n";
}

void testCountingSort() {
    // http://www.cs.miami.edu/home/burt/learning/Csc517.091/workbook/countingsort.html
    std::vector<int> data = {4, 5, 1, 4, 0, 3, 2, 5, 2, 2, 5, 1, 1, 3, 1, 4};
    countingSort(data, 5);
    assert(data == std::vector<int>({0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 5}));
    std::cout << "COUNTING SORT TEST PASS!\n";
}

void testRadixSort() {
    //std::initializer_list<int> il = {170, 45, 75, 90, 802, 24, 2, 66}; // to use max()
    //std::vector<int> data = il;
    std::vector<int> data = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(data, 3);
    //radixSort(data, max(il));
    assert(data == std::vector<int>({2, 24, 45, 66, 75, 90, 170, 802}));
    std::cout << "RADIX SORT TEST PASS!\n";
}

