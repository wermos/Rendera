cmake_minimum_required(VERSION 3.10)

# set the project name
project(Rendera VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.cxx
)

# add the executable
add_executable(Rendera ${SOURCES})

target_include_directories(Rendera PUBLIC include)

target_link_libraries(Rendera PUBLIC utilities)


