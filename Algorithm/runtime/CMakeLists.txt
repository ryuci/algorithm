set(SRC_FILES 
    binomial.cpp
    boardCover.cpp
    boggle.cpp
    clockSync.cpp
    cutRod.cpp
    dynamicProg.cpp 
    fence.cpp
    maxsum.cpp
    movingAverage.cpp
    multiply.cpp
    picnic.cpp
    runtime.cpp 
    sa.cpp
    saEasom.cpp
    setcover.cpp
    simplex.cpp 
    sorting.cpp
    sum.cpp
    tsp.cpp 
    tspDp.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(runtime ${SRC_FILES})
