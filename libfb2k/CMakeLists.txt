cmake_minimum_required(VERSION 2.6.2)

project(libfb2k)

include_directories(
    .
    .
    /home/drb/Documents/Project/cpp/libfb2k/libfb2k/
    /home/drb/Documents/Project/cpp/libfb2k/libfb2k/
)

set(CMAKE_CXXFLAGS "${CMAKE_CXXFLAGS}  -g")

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

set(SRCS
    include/libfb2k.h
)

add_library(libfb2k SHARED ${SRCS})

