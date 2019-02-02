set(SRC_FILES 
    dynamicProg.cpp
    jumpGame.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(dynamicProg ${SRC_FILES})
