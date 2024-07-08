cmake_minimum_required(VERSION 3.25.0)

project(controller)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DDEBUG_COORD)

add_subdirectory(coord)

add_subdirectory(nmea)

#link_directories(coord/build)

add_subdirectory(src)

add_executable(controller ${SOURCE})

#target_link_libraries(controller wiringPi)

target_include_directories(controller PUBLIC "coord/include")

target_link_libraries(controller coordinate)

target_include_directories(controller PUBLIC "nmea/include")

target_link_libraries(controller nmea)
