set(SRC_FILES
    fossil.cpp
    geometry.cpp
    quadTree.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(geometry ${SRC_FILES})
