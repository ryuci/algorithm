set(SRC_FILES
    numeric.cpp
    simpsonMethod.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(numeric ${SRC_FILES})
