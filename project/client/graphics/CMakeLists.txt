cmake_minimum_required(VERSION 3.2)
project(graphics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES src/main.cpp GraphicsController.cpp Player.cpp DataPacket.cpp)
add_executable(graphics ${SOURCE_FILES})
include_directories(.)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(graphics ${SFML_LIBRARIES})
endif()