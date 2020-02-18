
cmake_minimum_required(VERSION 3.5.0)

project(embeddedOS)

# file(GLOB SOURCES "Scheduler/*.c" "simpleQueue/*.c")
# file(GLOB Q_SOURCES "simpleQueue/*.c")
file(GLOB Q_SOURCES "simpleQueue/*.cpp")
file(GLOB SCH_SOURCES "Scheduler/*.c")
# file(GLOB TC_SOURCES "taskClass/*.cpp" "taskClass/*.h")

include_directories(simpleQueue Scheduler taskClass)

add_executable(testSched2 testSched2.c ${SCH_SOURCES})
add_executable(testQ testQ.c ${Q_SOURCES})

# add_executable(testOS testOS.cpp ${Q_SOURCES} ${SCH_SOURCES} ${TC_SOURCES} )
add_executable(testOS testOS.cpp ${Q_SOURCES} ${SCH_SOURCES} )
add_executable(qtestOS qtestOS.cpp ${SCH_SOURCES} )



