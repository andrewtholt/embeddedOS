
cmake_minimum_required(VERSION 3.5.0)

project(embeddedOS)

set(CMAKE_CXX_FLAGS "-Wfatal-errors")

# file(GLOB SOURCES "Scheduler/*.c" "simpleQueue/*.c")
# file(GLOB Q_SOURCES "simpleQueue/*.c")
file(GLOB Q_SOURCES "simpleQueue/*.cpp")
file(GLOB SCH_SOURCES "Scheduler/*.c")
file(GLOB UTILS_SOURCES "Utils/*.cpp")

file(GLOB MSG_SOURCES "msgClass/*.cpp" "msgClass/*.h")
# file(GLOB TC_SOURCES "taskClass/*.cpp" "taskClass/*.h")

include_directories(simpleQueue Scheduler taskClass msgClass Utils)

add_library(utils STATIC  ${UTILS_SOURCES} ${MSG_SOURCES})

add_executable(testSched2 testSched2.c ${SCH_SOURCES})
add_executable(testQ testQ.c ${Q_SOURCES})

# add_executable(testOS testOS.cpp ${Q_SOURCES} ${SCH_SOURCES} ${TC_SOURCES} )
add_executable(testOS testOS.cpp ${Q_SOURCES} ${SCH_SOURCES} )
target_link_libraries(testOS PUBLIC utils)

add_executable(qtestOS qtestOS.cpp ${SCH_SOURCES} )
add_executable(fullTest fullTest.cpp ${SCH_SOURCES} )
target_link_libraries(fullTest PUBLIC utils)

add_executable(msgTst msgTst.cpp )

target_link_libraries(msgTst PUBLIC utils)

add_executable(msgPoolTst msgPoolTst.cpp )
target_link_libraries(msgPoolTst PUBLIC utils)



