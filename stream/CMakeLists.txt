project(stream)

add_definitions("-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall")
# include_directories(../common)

# file(GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_executable(sproxy sproxy.cpp)
target_link_libraries(sproxy zmq)

add_executable(sworker sworker.cpp)
target_link_libraries(sworker zmq)

add_executable(sclient sclient.cpp)
target_link_libraries(sclient zmq)

add_executable(sserver sserver.cpp)
target_link_libraries(sserver zmq)
