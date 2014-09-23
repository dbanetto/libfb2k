cmake_minimum_required(VERSION 3.0)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(BUILD_TESTING True)

set(FB2K_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libfb2k/include" CACHE INTERNAL "fb2k_include")
set(FB2K_LIBRARY "${CMAKE_BINARY_DIR}/libfb2k.so" CACHE INTERNAL "fb2k_library")

# Projects
add_subdirectory(libfb2k)
add_subdirectory(tf2k)
