//
//  sa.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 18/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//
//  References:
//      [1] http://www.theprojectspot.com/tutorial-post/simulated-annealing-algorithm-for-beginners/6
//      [2] https://www.springer.com/cda/content/document/cda_downloaddocument/9783319411910-c2.pdf?SGWID=0-0-45-1579890-p180080441
//      [3] http://www.mit.edu/~dbertsim/papers/Optimization/Simulated%20annealing.pdf
//      [4] http://toddwschneider.com/posts/traveling-salesman-with-simulated-annealing-r-and-shiny/
//      [5] https://pdfs.semanticscholar.org/e34f/94561872a20130addfaec69de096582516de.pdf
//      [6] http://image.diku.dk/imagecanon/material/GemanPAMI84.pdf
//
#include "helper.hpp"
#include "runtime.hpp"
#include <cmath>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#ifdef INCLUDE_OPENCV
#include "../opencv/opencvbridge.hpp"
#endif

//#define RANDOM_CITIES

class TSP {
private:
    // Cities list in the order of travelling.
    std::vector<Point<int>> _cities;
    // Placeholder of alternative cities list.
    std::vector<Point<int>> _altCities;
    bool _visualize;
    const int _width, _height;
#ifdef INCLUDE_OPENCV
    // For visuallization.
    OpencvWrapper _ocw;
#endif
    const int _pointSize = 5;

public:
    // Constructor
    //
    TSP(bool visualize = false, int width = 300, int height = 300)
    : _visualize(visualize), _width(width), _height(height) {
        if (_visualize) {
                
        }
    };
    
    // Add given city.
    //
    void addCity(Point<int> city) {
        if (city.x >= 0 && city.x < _width &&
            city.y >= 0 && city.y < _height) {
            _cities.push_back(city);
#ifdef INCLUDE_OPENCV
            if (_visualize) _ocw.putPixel(_pointSize, city);
#endif
        }
        else
            std::cout << "City (" << city.x << "," << city.y << ") is out of range.\n";
    }
    
    // Add random city.
    //
    void addCity() {
        Point<int> pt;
        pt.x = rand() % _width;
        pt.y = rand() % _height;
        _cities.push_back(pt);
#ifdef INCLUDE_OPENCV
        if (_visualize) _ocw.putPixel(_pointSize, pt);
#endif
    }

    // Distance from two cities.
    //
    double distance(const Point<int>& here, const Point<int>& there) {
        int xDistance = here.x - there.x;
        int yDistance = here.y - there.y;
        return sqrt((xDistance * xDistance) + (yDistance * yDistance));
    }
    
    // Distance of full travel.
    //
    double distance(const std::vector<Point<int>>& points) {
        double sum = 0.0;
        int i;
        for (i = 0; i < points.size() - 1; ++i) {
            sum += distance(points[i], points[i+1]);
        }
        sum += distance(points[i], points[0]);
        return sum;
    }
    
    double distance() { return distance(_cities); }

    // Distance of alternative full travel.
    //
    double altDistanceCandidate() {
        
        // TODO:1-27-2017: Because I will just swap two cities, there will be a better way
        //                 than copying full list. To be fixed.
        _altCities = _cities;

        // Swqp two cities and get new distance.
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, (int)_altCities.size() - 1);
        int index1 = dist(rng);
        int index2 = dist(rng);
        std::swap(_altCities[index1], _altCities[index2]);
        std::cout << "Swap(" << index1 << "," << index2 << "), ";
        return distance(_altCities);
    }

    // Take candidate.
    void takeCandidate() { _cities = _altCities; }
    
    // Shuffle cities.
    //
    void shuffleCities(std::vector<Point<int>> points) {
        // Random shuffle.
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::shuffle(points.begin(), points.end(), rng);
    }

    void shuffleCities() { shuffleCities(_cities); }

    // To string.
    //
    std::string toString() {
        std::stringstream ret;
        ret << _cities.size() << " cities: ";
        for (int i = 0; i < _cities.size(); i++) {
            ret << "(" << _cities[i].x << "," << _cities[i].y << ")";
        }
        ret << std::endl;
        return ret.str();
    }

    // To CSV file.
    //
    void toCsv() {
        writeCSV("/Users/ryuci/Dropbox/workspace/cpp/Algorithm/Algorithm/sa_out.csv" , _cities);
    }
    
    void wait(int t) {
#ifdef INCLUDE_OPENCV
        _ocw.wait(t);
#endif
        
    }
};

// Calculate the acceptance probability
//
static double acceptanceProbability(int oldE, int newE, double T) {
    if (newE < oldE) {
        // Accept better solution.
        return 1.0;
    }
    // Calculate acceptance probability for worse solution.
    return exp((oldE - newE) / T);
}

void testSaTSP() {
    TSP tsp(true);
#ifndef RANDOM_CITIES
    tsp.addCity(Point<int>(60, 200)); tsp.addCity(Point<int>(180, 200));
    tsp.addCity(Point<int>(80, 180)); tsp.addCity(Point<int>(140, 180));
    tsp.addCity(Point<int>(20, 160)); tsp.addCity(Point<int>(100, 160));
    tsp.addCity(Point<int>(200, 160)); tsp.addCity(Point<int>(140, 140));
    tsp.addCity(Point<int>(40, 120)); tsp.addCity(Point<int>(100, 120));
    tsp.addCity(Point<int>(180, 100)); tsp.addCity(Point<int>(60, 80));
    tsp.addCity(Point<int>(120, 80)); tsp.addCity(Point<int>(180, 60));
    tsp.addCity(Point<int>(20, 40)); tsp.addCity(Point<int>(100, 40));
    tsp.addCity(Point<int>(200, 40)); tsp.addCity(Point<int>(20, 20));
    tsp.addCity(Point<int>(60, 20)); tsp.addCity(Point<int>(160, 20));
#else
    for (int i = 0; i < 100; i++)
        tsp.addCity();
#endif
    tsp.shuffleCities();
    
    double T = 10000;
    double coolingRate = 0.003;
    // Baseline.
    double currentE = tsp.distance();
    std::cout << "Initial distance: " << currentE << std::endl;
 
    int count = 0;
    while (T > 1) {
        // Calculate new energy level.
        double newE = tsp.altDistanceCandidate();
        
        // Decide take or leave.
        double prob = acceptanceProbability(currentE, newE, T);
        std::cout << "New E = " << newE << ", Prob = " << prob << ", ";
        if (prob == 1.0 || prob > (double)rand() / RAND_MAX) {
            tsp.takeCandidate();
            currentE = newE;
            std::cout << "Take\n";
        }
        else std::cout << "Leave\n";

        // Cool system
        T *= 1 - coolingRate;
        count++;
    }
    
    std::cout << "Final solution distance: " << currentE << std::endl;
    std::cout << "Iterations: " << count << std::endl;
    std::cout << "Path: " << tsp.toString() << std::endl;
    
    wait(0);
}
