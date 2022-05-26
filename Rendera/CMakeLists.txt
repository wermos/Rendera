cmake_minimum_required(VERSION 3.10)

# set the project name
project(Celerity VERSION 0.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the SFML library
add_subdirectory()

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.cxx
)

# add the executable
add_executable(Rendera ${SOURCES})

target_include_directories(Celerity PUBLIC include)
target_include_directories(Celerity PUBLIC libs/SFML)

target_link_libraries(Celerity PUBLIC utilities)
target_link_libraries(Celerity PUBLIC )


