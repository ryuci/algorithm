set(SRC_FILES 
    numberTheory.cpp
    sieveOfEratosthenes.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(numberTheory ${SRC_FILES})
