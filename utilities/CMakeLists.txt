cmake_minimum_required(VERSION 3.10)

# set the project name
project(utilities VERSION 0.0.1)

# add xsimd
add_subdirectory(libs/xsimd)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(utilities ${SOURCES})

target_include_directories(utilities PUBLIC include)
target_include_directories(utilities PUBLIC libs/xsimd/include)
target_include_directories(utilities PUBLIC libs/stb)
target_include_directories(utilities PUBLIC ../shared)