set(SRC_FILES 
    binomial.cpp
    boardCover.cpp
    boggle.cpp
    cutRod.cpp
    dynamicProg.cpp 
    fence.cpp
    maxsum.cpp
    movingAverage.cpp
    picnic.cpp
    runtime.cpp 
    sa.cpp
    saEasom.cpp
    setcover.cpp
    simplex.cpp 
    sorting.cpp 
    tsp.cpp 
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(runtime ${SRC_FILES})
