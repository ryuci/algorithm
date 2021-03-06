//
//  main.hpp
//  Algorithm
//
//  Created by Choong-il Ryu on 15/01/2019.
//  Copyright © 2019 codetolearn.kr. All rights reserved.
//

// Unlike Xcode, CMake does not recursively search header files.
// So, suffixing  relative path is required.
//
#include "helper.hpp"
#include "dynamicProg/dynamicProg.hpp"
#include "combinatorics/combinatorics.hpp"
#include "dataStructure/dataStructure.hpp"
#include "geometry/geometry.hpp"
#include "greedyMethod/greedyMethod.hpp"
#include "matrix/matrix.hpp"
#include "memory/memory.hpp"
#include "misc/misc.hpp"
#include "numberTheory/numberTheory.hpp"
#include "numericalAnalysis/numericalAnalysis.hpp"
#include "optByDecision/optByDecision.hpp"
#ifdef INCLUDE_OPENCV
#include "opencv/opencvbridge.hpp"
#endif
#include "runtime/runtime.hpp"
#ifdef INCLUDE_VTK
#include "vtk/vtk.hpp"
#endif

