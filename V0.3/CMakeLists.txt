
cmake_minimum_required(VERSION 3.5.0)

project(embeddedOS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wfatal-errors")
set(CMAKE_C_FLAGS "-Wfatal-errors")

file(GLOB Q_SOURCES "simpleQueue/*.c")
file(GLOB SCH_SOURCES "Scheduler/*.c")
file(GLOB UTILS_SOURCES "Utils/*.c")
file(GLOB TASK_SOURCES "Tasks/*.c")
file(GLOB MSG_SOURCES "Msg/*.c")
# file(GLOB DB_SOURCES "simpleDatabase/*.cpp" "simpleDatabase/*.h")
file(GLOB DB_SOURCES "simpleDatabase/*.cpp" )

include_directories(simpleQueue Scheduler taskClass Utils simpleDatabase Tasks Msg)

add_library(utils STATIC ${MSG_SOURCES} ${TASK_SOURCES} ${SCH_SOURCES} ${UTILS_SOURCES} ${Q_SOURCES} ${DB_SOURCES})

add_executable(testSched2 testSched2.c ${SCH_SOURCES})
add_executable(testSchedQ testSchedQ.c )
target_link_libraries(testSchedQ PUBLIC utils)

# add_executable(testQ testQ.c ${Q_SOURCES})

# add_executable(testOS testOS.cpp ${Q_SOURCES} ${SCH_SOURCES} )
# target_link_libraries(testOS PUBLIC utils)

add_executable(qtestOS qtestOS.cpp ${SCH_SOURCES} )
add_executable(tstMsg tstMsg.c ${MSG_SOURCES} )

add_executable(fullTest fullTest.c )
target_link_libraries(fullTest PUBLIC utils)

add_executable(tstDatabase tstDatabase.cpp )
target_link_libraries(tstDatabase PUBLIC utils)

add_executable(tstLib tstLib.cpp )
target_link_libraries(tstLib PUBLIC utils)

