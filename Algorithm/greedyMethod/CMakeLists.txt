set(SRC_FILES 
    greedyMethod.cpp
    meetingRoom.cpp
    fightOrder.cpp
    heatingOrder.cpp
    joinString.cpp
    minasTirith.cpp
)
# Creates a new library target built from sources.
# add_library(target [STATIC | SHARED | MODULE] sources…)
add_library(greedyMethod ${SRC_FILES})
