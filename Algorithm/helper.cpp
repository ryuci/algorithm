//
//  helper.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 18/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#define helper_cpp
#include "main.hpp"
#include "helper.hpp"
#include <ctime>
#include <vector>
#if __cplusplus > 201402L // 199711L, 201703L
#include <filesystem>
#else
#include <unistd.h>
#endif

#include <sstream>
#include <fstream>
#include <queue>
#include <cstdio>

//
// TIMER
//

static clock_t c0;

void startTimer() {
    c0 = clock();
}


void stopTimer() {
    std::cout << (double)(clock() - c0)/CLOCKS_PER_SEC*1000 << " ms" << std::endl;
}

double stopTimerRet() {
    return (double)(clock() - c0)/CLOCKS_PER_SEC*1000;
}

//
// PRINT STL CONTAINERS
//

std::ostream& operator<<(std::ostream& os, const Point<int>& pt) {
    return os << "(" << pt.x << "," << pt.y << ")";
}

std::ostream& operator<<(std::ostream& os, const std::vector<Point<int>>& v) {
    for (int i = 0; i < v.size(); i++)
        os << v[i];
    return os;
}



#if 0
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
void print(std::vector<std::vector<T>> const &v)
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
#endif

//
// EXPORT STL CONTAINERS
//

int writeCSV(std::string fname, std::vector<Point<int>>& data) {
    std::ofstream file(fname.data());
    if (file.is_open()) {
        for (int i = 0; i < data.size(); i++) {
            file << data[i].x << "," << data[i].y << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Unable to open " << fname << std::endl;
#if __cplusplus > 201402L
        std::cout << "cwd = " << std::filesystem::current_path() << std::endl;
#else
        char cwd[256];
        getcwd(cwd, 256);
        std::cout << "cwd = " << cwd << std::endl;
#endif
    }
    return 0;
}

//
// MENU CONSTRUCTION
//

void NA() {
    std::cout << "--------------------" << std::endl;
    std::cout << "Not implemented yet" << std::endl;
    std::cout << "--------------------" << std::endl;
}

extern std::queue<int> autoInput;

void displayMenu(std::vector<std::pair<std::string,void (*)()>> menu, std::string title) {
    while (true) {
        std::cout << std::string(title.length(), '-') << std::endl;
        std::cout << title << std::endl;
        std::cout << std::string(title.length(), '-') << std::endl;
        for (int i = 0; i < menu.size(); i++)
            std::cout << "[" << i << "] " << menu[i].first
                      << ((menu[i].second == NA) ? " - N/A":"") << std::endl;
        std::cout << "[-1] Exit" << std::endl;
        std::cout << std::string(title.length(), '-') << std::endl;
        int ans = -100;
        while (ans < -1 && ans >= menu.size()) {
            std::cout << "Enter a number: ";
            if (!autoInput.empty()) {
                ans = autoInput.front();
                autoInput.pop();
                std::cout << std::endl;
            }
            else {
                std::cin >> ans;
                // Discard input buffer.
                while ((getchar()) != '\n');
            }
        }
        if (ans == -1) break;
        menu[ans].second();
        std::cout << "Press enter to continue." << std::endl;
        while (getchar() != '\n');
    }
}

