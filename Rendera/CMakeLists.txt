cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# add the executable
add_executable(Rendera ${SOURCES})

target_include_directories(Rendera PUBLIC include)

target_link_libraries(Rendera PUBLIC utilities)
target_include_directories(Rendera PUBLIC ../shared)


