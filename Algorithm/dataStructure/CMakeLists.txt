set(SRC_FILES graph.cpp hash.cpp kdtree.cpp nrkdtree.cpp rshash.cpp tree.cpp)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(dataStructure ${SRC_FILES})