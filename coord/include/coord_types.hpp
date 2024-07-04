#pragma once

namespace coord
{

enum class LLA_Type
{
    LATITUDE,
    LONGITUDE,
    ALTITUDE
};

enum class Alt_Type
{
    HAE,
    MSL
};

enum class Angular_Type
{
    DEGREES,
    RADIANS,
    NUM_TYPES
};

const int Earth_Radius_Meters = 6371e3; // Meters

}