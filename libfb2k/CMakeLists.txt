cmake_minimum_required(VERSION 2.8)

project(libfb2k)

# Match build folder structure to src
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Find Libraries
find_package(tag REQUIRED)

# CXX Flags
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

include_directories(${TAG_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(fb2k SHARED
	src/Block.cpp
	src/FuncMap.cpp
)

target_link_libraries(fb2k ${TAG_LIBRARIES})

# Test Suite
find_package(UnitTest++ QUIET)
if (UNITTEST++_FOUND)
	enable_testing()

	add_executable(fb2kTest
		tests/runner.cpp
		tests/BlockTest.cpp
		tests/FunctionTest.cpp
	)

	add_dependencies(fb2kTest fb2k)

	include_directories(${UNITTEST++_INCLUDE_DIR})
	include_directories(${TAG_INCLUDE_DIR})
	include_directories(${PROJECT_SOURCE_DIR}/include)

	target_link_libraries(fb2kTest ${LIBRARY_OUTPUT_PATH}/libfb2k.so)
	target_link_libraries(fb2kTest ${TAG_LIBRARIES})
	target_link_libraries(fb2kTest ${UNITTEST++_LIBRARY})

	add_test(fb2kTest fb2kTest)
endif()
