cmake_minimum_required(VERSION 3.10)

# set the project name
project(Rendera VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set SFML library compilation settings
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# we don't need the audio and networking subsystems for now
set(SFML_BUILD_AUDIO FALSE CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK FALSE CACHE BOOL "" FORCE)

# add the SFML library
add_subdirectory(libs/sfml)

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.cxx
)

# add the executable
add_executable(Rendera ${SOURCES})

target_include_directories(Rendera PUBLIC include)
target_include_directories(Rendera PUBLIC libs/SFML)

target_link_libraries(Rendera PUBLIC utilities)
target_link_libraries(Rendera PUBLIC sfml‑window)
target_link_libraries(Rendera PUBLIC sfml‑graphics)


