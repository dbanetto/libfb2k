cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Build Tests
set(BUILD_TESTING True)

# Point to libfb2k
set(FB2K_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libfb2k/include" CACHE INTERNAL "fb2k_include")
set(FB2K_LIBRARY "${CMAKE_BINARY_DIR}/libfb2k/libfb2k.so" CACHE INTERNAL "fb2k_library")

# Projects
add_subdirectory(libfb2k)
add_subdirectory(tf2k)
