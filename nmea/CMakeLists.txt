cmake_minimum_required(VERSION 3.25.0)

project(nmea)

include_directories(include)

add_library(nmea
            SHARED
            src/nmea.parse.cpp
)
