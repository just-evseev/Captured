cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES ./src/main.cpp src/RenderManager.cpp ./include/StructInit.h ./include/RenderManager.h ./include/Hex.h)
add_executable(server ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(server ${SFML_LIBRARIES})
endif()



