
cmake_minimum_required(VERSION 3.5.0)

project(embeddedOS)

# file(GLOB SOURCES "Scheduler/*.c" "simpleQueue/*.c")
file(GLOB Q_SOURCES "simpleQueue/*.c")
file(GLOB SCH_SOURCES "Scheduler/*.c")

include_directories(simpleQueue Scheduler)

add_executable(testSched2 testSched2.c ${SCH_SOURCES})
add_executable(testQ testQ.c ${Q_SOURCES})
add_executable(testOS testOS.c ${Q_SOURCES} ${SCH_SOURCES})



