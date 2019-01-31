//
//  simplex2.cpp
//  Algorithm
//
//  Created by Choong-il Ryu on 22/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

#include "simplex2.hpp"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/*
 The main method is in this program itself.
 Instructions for compiling=>>
 Run on any gcc compiler=>>
 Special***** should compile in -std=c++11 or C++14 -std=gnu++11  *********  (mat be other versions syntacs can be different)
 turorials point online compiler
 ==> go ti link   http://cpp.sh/ or  https://www.tutorialspoint.com/cplusplus/index.htm and click try it(scorel below) and after go to c++ editor copy code and paste.
 after that click button execute.
 if you have -std=c++11 you can run in command line;
 g++ -o output Simplex.cpp
 ./output
 How to give inputs to the program =>>>
 Example:
 colSizeA = 6 // input colmn size
 rowSizeA = 3  // input row size
 float C[N]={-6,-5,-4,0,0,0};  //Initialize the C array  with the coefficients of the constraints of the objective function
 float B[M]={240,360,300};//Initialize the B array constants of the constraints respectively
 //initialize the A array by giving all the coefficients of all the variables
 float A[M][N] =  {
 { 2,  1,  1,   1,  0, 0},
 { 1,  3,  2,   0,  1, 0 },
 {   2,    1,  2,   0,  0,  1}
 };
 */



class Simplex{
private:
    int _rows, _columns;
    // Variable matrix
    std::vector<std::vector<double> > _V;
    // Constraint vector
    std::vector<double> _C;
    // Objective vector
    std::vector<double> _O;
    float _maximum;
    bool _unbounded;
    
public:
    Simplex(std::vector<std::vector<double>> V, std::vector<double> C, std::vector<double> O) : _V(V), _C(C), _O(O) {
        _maximum = 0;
        _unbounded = false;
        _rows = (int)V.size();
        _columns = (int)V[0].size();
    }
    
    void calc() {
        // If there's no negaitve value in objective vector, it means calculation is done.
        while (count_if(_O.begin(), _O.end(), [](double n) { return n < 0; })) {
            // Find pivot column whose objective coefficient is most negative.
#if 0
            int pivotColumn = std::distance(_O.begin(), std::min(_O.begin(), _O.end()));
#else
            std::vector<double>::iterator pivotColumn = std::min(_O.begin(), _O.end());
#endif
            if (_unbounded) {
                std::cout << "Error unbounded." << std::endl;
                return;
            }
            
            //find the row with the pivot value.The least value item's row in the B array
            std::vector<double>::iterator pivotRow = getPivotRow(pivotColumn);
            
            //form the next table according to the pivot value
            doPivotting(pivotRow,pivotColumn);
        }
    }
    
    void doPivotting(std::vector<double>::iterator pivotRow, std::vector<double>::iterator pivotColumn){
        double pivotValue = _V[*pivotRow][*pivotColumn];
        double pivotRowValues[_columns];
        double pivotColumnValues[_rows];
        double pivotRowNewValues[_columns]; //the row after processing the pivot value
        
        _maximum = _maximum - _O[*pivotColumn] * _C[*pivotRow] / pivotValue;
        //get the row that has the pivot value
        for(int i=0;i<_columns;i++){
            pivotRowValues[i] = _V[*pivotRow][i];
        }
        //get the column that has the pivot value
        for(int j=0;j<_rows;j++){
            pivotColumnValues[j] = _V[j][*pivotColumn];
        }
# if 0
        //set the row values that has the pivot value divided by the pivot value and put into new row
        for(int k=0;k<_columns;k++){
            pivotRowNewValues[k] = pivotRowValues[k]/pivot;
        }
        
        _C[*pivotRow] = _C[*pivotRow] / pivotValue;
        
        
        //process the other coefficients in the A array by subtracting
        for(int m=0;m<_rows;m++){
            //ignore the pivot row as we already calculated that
            if(m !=pivotRow){
                for(int p=0;p<_columns;p++){
                    float multiplyValue = pivotColumnValues[m];
                    _V[m][p] = _V[m][p] - (multiplyValue*pivotRowNewValues[p]);
                    //C[p] = C[p] - (multiplyValue*C[pivotRow]);
                    //B[i] = B[i] - (multiplyValue*B[pivotRow]);
                }
                
            }
        }
        
        //process the values of the B array
        for(int i=0;i<_C.size();i++){
            if(i != pivotRow){
                
                float multiplyValue = pivotColumn[i];
                _C[i] = _C[i] - (multiplyValue*_C[pivotRow]);
                
            }
        }
        //the least coefficient of the constraints of the objective function
        float multiplyValue = _O[pivotColumn];
        //process the C array
        for(int i=0;i<_O.size();i++){
            _O[i] = _O[i] - (multiplyValue*pivotRowNewValues[i]);
            
        }
        
        
        //replacing the pivot row in the new calculated A array
        for(int i=0;i<_columns;i++){
            _V[pivotRow][i] = rowNew[i];
        }
#endif
        
    }
    
    // Find pivot column whose objective coefficient is most negative.
    std::vector<double>::iterator getPivotRow(std::vector<double>::iterator pivotColumn) {
        double positives[_rows];
        double tmp[_rows];
        int zeroOrNegativeCount = 0;
        
        // Seach for positive values in the pivot column.
        for (int i = 0; i < _rows; i++) {
            if(_V[i][*pivotColumn] > 0) {
                positives[i] = _V[i][*pivotColumn];
                tmp[i] = _C[i] / _V[i][*pivotColumn];
            }
            else {
                positives[i] = 0;
                // Make it big to use in min() comparison.
                tmp[i] = 9876543210;
                zeroOrNegativeCount++;;
            }
        }
        
        // Check the unbound condition where all the values are negative.
        if (zeroOrNegativeCount == _rows){
            _unbounded = true;
            // TODO::2019-1-22: Is there better way?
            return _O.end();
        }
        return std::min(_O.begin(), _O.end());
    }
};
