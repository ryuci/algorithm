set(SRC_FILES 
    arctic.cpp
    canadaTrip.cpp
    optByDecision.cpp
    DARPA.cpp
    withdrawal.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(optByDecision ${SRC_FILES})
