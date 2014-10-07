cmake_minimum_required(VERSION 2.8)

project(tf2k)

# Match build folder structure to src
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Find Libraries
find_package(tag REQUIRED)
find_package(fb2k REQUIRED)

# CXX flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

include_directories(${TAG_INCLUDE_DIR})
include_directories(${FB2K_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(tf2k src/main.cpp)

add_dependencies(tf2k fb2k)

target_link_libraries(tf2k ${TAG_LIBRARIES})
target_link_libraries(tf2k ${FB2K_LIBRARIES})
