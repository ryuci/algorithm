set(SRC_FILES
    numericalAnalysis.cpp
    simpsonMethod.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(numericalAnalysis ${SRC_FILES})
