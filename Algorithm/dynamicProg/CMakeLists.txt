set(SRC_FILES 
    dynamicProg.cpp
    jumpGame.cpp
    longestIncreasingSubseq.cpp
    snail.cpp
    tiling.cpp
    trianglePath.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(dynamicProg ${SRC_FILES})
