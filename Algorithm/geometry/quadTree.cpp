//
//  quadTree.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 01/02/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "helper.hpp"
#include "geometry.hpp"

static const int MAX_SIZE = 20;
static char picture[MAX_SIZE][MAX_SIZE];

// Print Picture
//
static void print() {
    
}

// Decompress code tree.
//
static void decompressQuadTree(std::string::iterator& it, int y, int x, int size) {
    char head = *(it++);
    if (head == 'b' || head == 'w') {
        // Fill in.
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                picture[y + i][x + j] = head;
    }
    else {
        int half = size / 2;
        decompressQuadTree(it, y, x, half);
        decompressQuadTree(it, y, x + half, half);
        decompressQuadTree(it, y + half, x, half);
        decompressQuadTree(it, y + half, x + half, half);
    }
}

// Reverse Quad Tree
// Problem: If we take decompress, reverse, compress approach, it takes huge memory.
//          So, we need to find out how to reverse without full decompression.
// Complexity:
static std::string reverseQuadTree(std::string::iterator& it) {
    char head = *(it++);
    if (head == 'b' || head == 'w')
        return std::string(1, head);
    std::string tl = reverseQuadTree(it);
    std::string tr = reverseQuadTree(it);
    std::string bl = reverseQuadTree(it);
    std::string br = reverseQuadTree(it);
    // Merge by exchanging top and bottom.
    return "x" + bl + br + tl + tr;
}

void testQuadTreeReverse() {
    std::vector<std::string> problems = {
        "w",
        "xbwwb",
        "xbwxwbbwb",
        "xxwwwbxwxwbbbwwxxxwwbbbwwwwbb",
    };
    std::vector<std::string> solutions = {
        "w",
        "xwbbw",
        "xxbwwbbbw",
        "xxwbxwwxbbwwbwbxwbwwxwwwxbbwb",
    };
    for (int i = 0; i < problems.size(); i++) {
        std::string::iterator it = problems[i].begin();
        std::cout << reverseQuadTree(it) << std::endl;
        // Reset iterator.
        it = problems[i].begin();
        assert(reverseQuadTree(it) == solutions[i]);
        it = problems[i].begin();
        decompressQuadTree(it, 0, 0, MAX_SIZE);
        print();
        it = solutions[i].begin();
        decompressQuadTree(it, 0, 0, MAX_SIZE);
        print();
        // TODO:1-22-2019: Find out why we can't pass iterator string.begin() as
        //                 a reference. It doesn't look like const.
        
        //it = problems[i].begin();
        //std::cout << reverseQuadTree(it) << std::endl;
        //it = problems[i].begin();
        //assert(reverseQuadTree(it) == solutions[i]);
        //std::cout << "QUAD-TREE TEST PASS!\n";

    }
}

#include "geometry.hpp"
class geometry::QuadTree {
private:
    int _capacity;
    Point<int> _tl, _br;
    bool _divided;
    bool _logOn;
    std::string _label;
    std::vector<Point<int>> _points;
    std::unique_ptr<QuadTree> _nw;
    std::unique_ptr<QuadTree> _ne;
    std::unique_ptr<QuadTree> _sw;
    std::unique_ptr<QuadTree> _se;

public:
    QuadTree(Point<int> tl, Point<int> br, int capacity, std::string label, bool logOn=false) :
        _tl(tl), _br(br), _capacity(capacity), _label(label), _logOn(logOn) {
        // Width and height are assumed even number.
        // TODO:2-2-2019: label null check.
        _divided = false;
    };
    
    bool contains(Point<int> pt) {
        return pt.x >= _tl.x &&
        pt.x < _br.x &&
        pt.y >= _br.y &&
        pt.y < _tl.y;
    }

    void insert(Point<int> pt) {
        if (!contains(pt))
            return;
        // pt may fit in this area.
        if (_logOn) std::cout << "Inserting (" << pt.x << "," << pt.y << ")\n";
        if (_points.size() == _capacity) {
            // Capacity is full. Need to try subareas.
            if (_logOn) std::cout << _label << " Full\n";
            if (!_divided) {
                // Make sub-quadtree.
                if (_logOn) std::cout << "Divide\n";
                // Divide the area.
                Point<int> tc = Point<int>(_tl.x + (_br.x-_tl.x)/2, _tl.y);
                Point<int> lc = Point<int>(_tl.x, _br.y+(_tl.y-_br.y)/2);
                Point<int> cc = Point<int>(_tl.x+(_br.x-_tl.x)/2, _br.y+(_tl.y-_br.y)/2);
                Point<int> rc = Point<int>(_br.x, _br.y+(_tl.y-_br.y)/2) ;
                Point<int> bc = Point<int>(_tl.x+(_br.x-_tl.x)/2, _br.y);
                if (_logOn)  {
                    std::cout << "tc (" << tc.x << "," << tc.y << ")\n";
                    std::cout << "lc (" << lc.x << "," << lc.y << ")\n";
                    std::cout << "cc (" << cc.x << "," << cc.y << ")\n";
                    std::cout << "rc (" << rc.x << "," << rc.y << ")\n";
                    std::cout << "bc (" << bc.x << "," << bc.y << ")\n";
                }
                
                _nw = std::unique_ptr<QuadTree>(new QuadTree(_tl, cc, _capacity, _label + ":NW", _logOn));
                _ne = std::unique_ptr<QuadTree>(new QuadTree(tc, rc, _capacity, _label + ":NE", _logOn));
                _sw = std::unique_ptr<QuadTree>(new QuadTree(lc, bc, _capacity, _label + ":SW", _logOn));
                _se = std::unique_ptr<QuadTree>(new QuadTree(cc, _br, _capacity, _label + ":SE", _logOn));
                assert(_nw != nullptr);
                assert(_ne != nullptr);
                assert(_sw != nullptr);
                assert(_se != nullptr);
                
                _divided = true;
            }
            else {
                if (_logOn) std::cout << "No need to divide\n";
            }
            // Try to insert in the sub-quadtrees.
            if (_logOn) std::cout << "Trying " << _label << ":NW\n";
            _nw->insert(pt);
            if (_logOn) std::cout << "Trying " << _label << ":NE\n";
            _ne->insert(pt);
            if (_logOn) std::cout << "Trying " << _label << ":SW\n";
            _sw->insert(pt);
            if (_logOn) std::cout << "Trying " << _label << ":SE\n";
            _se->insert(pt);
        }
        else {
            if (_logOn) std::cout << "Done in " << _label << "\n";
            _points.push_back(pt);
        }
    }

    std::vector<Point<int>> search(Point<int> pt) {
        if (!contains(pt))
            return std::vector<Point<int>>();

        if (_logOn) std::cout << "Searching (" << pt.x << "," << pt.y << ")\n";
        
        if (std::find(_points.begin(), _points.end(), pt) != _points.end()) {
            // It's here.
            if (_logOn) std::cout << "Done in " << _label << "\n";
            return _points;
        }

        if (_divided) {
            std::vector<Point<int>> ret;
            ret = _nw->search(pt);
            if (!ret.empty()) return ret;
            ret = _ne->search(pt);
            if (!ret.empty()) return ret;
            ret = _sw->search(pt);
            if (!ret.empty()) return ret;
            ret = _se->search(pt);
            if (!ret.empty()) return ret;
        }
        
        // Tried all for nothing.
        return std::vector<Point<int>>();
    }
};

// TODO:2-2-2019: Under Development
//
void testQuadTreeNeighborSearch() {
//    QuadTree qt = QuadTree(Point<int>(0, 200), Point<int>(200, 0), 3, "ROOT", true);
    geometry::QuadTree qt = geometry::QuadTree(Point<int>(0, 256), Point<int>(256, 0), 4, "ROOT", true);
    std::vector<Point<int>> ptList = {{7,49}, {73,58}, {130,72}, {144,78}, {123,109},
                                      {40,165}, {92,42}, {187,103}, {127,129}, {40,12}};
    std::vector<Point<int>> ret;
    
    for (int i = 0; i < 10; ++i) {
#if 1
        qt.insert(ptList[i]);
#else
        qt.insert(Point<int>(rand() % 200, rand() % 200));
#endif
    }
    HR;
    std::cout << "SEARCH A PIXEL'S NEIGHBORS\n";
    ret = qt.search(ptList[5]);
    std::cout << ret << std::endl;
    HR;
    std::cout << "SEARCH A PIXEL'S NEIGHBORS\n";
    ret = qt.search(ptList[9]);
    std::cout << ret << std::endl;
    HR;
}
