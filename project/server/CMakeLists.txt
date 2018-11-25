cmake_minimum_required(VERSION 3.12)
project(serverCaptured)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")
add_executable(serverCaptured include/StructInit.h include/MapRender.h src/main.cpp src/MapRender.cpp)