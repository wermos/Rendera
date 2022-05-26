cmake_minimum_required(VERSION 3.10)

# set the project name
project(utilities VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add xsimd
add_subdirectory(libs/xsimd)

file(GLOB_RECURSE SOURCES
	CONFIGURE_DEPENDS
	src/*.cpp)

add_library(utilities ${SOURCES})

target_include_directories(utilities PUBLIC include)
target_include_directories(utilities PUBLIC libs/xsimd/include)
