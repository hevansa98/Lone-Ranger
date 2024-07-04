cmake_minimum_required(VERSION 3.28.0)

project(controller)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DDEBUG_COORD)

add_subdirectory(coord)

#link_directories(coord/build)

add_subdirectory(src)

add_executable(controller ${SOURCE})

target_include_directories(controller PUBLIC "coord/include")

target_link_libraries(controller coordinate)