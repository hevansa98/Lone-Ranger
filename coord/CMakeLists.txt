cmake_minimum_required(VERSION 3.25.0)

project(coordinate)

include_directories(include)

add_library(coordinate
            SHARED
            src/transforms.earth.cpp
)
