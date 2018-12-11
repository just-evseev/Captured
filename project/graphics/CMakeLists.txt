cmake_minimum_required(VERSION 3.2)
project(graphics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


set(SOURCE_FILES main.cpp Modules/source/GraphicsController.cpp Modules/source/MouseController.cpp DataPacket.cpp Cursor.cpp client2server.pb.cc)
add_executable(graphics ${SOURCE_FILES})
include_directories("Modules/headers" ".")

# SFML LINKING PART
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(graphics ${SFML_LIBRARIES})
endif()

#
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#add_executable(graphics server2client.pb.cc client2server.pb.cc ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(graphics ${Protobuf_LIBRARIES})