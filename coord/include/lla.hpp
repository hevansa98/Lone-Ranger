#pragma once

#include <array>
#include <cmath>

#include <altitude.hpp>

namespace coord
{

class LLA
{
public:
    const std::array<double, (size_t)Angular_Type::NUM_TYPES> Latitude, Longitude;
    const Alt Altitude;

public:
    double Get_Latitude(const Angular_Type & Angular) const
    {
        return (double)Latitude.at((size_t)Angular);
    }
    double Get_Longitude(const Angular_Type & Angular) const
    {
        return (double)Longitude[(size_t)Angular];
    }
public:
    LLA(const double & Latitude, const double & Longitude, const Alt & Altitude) :
        Latitude({Latitude, Latitude * M_PI/180.0}),
        Longitude({Longitude, Longitude * M_PI/180.0}),
        Altitude(Altitude)
    {};
    
    ~LLA(){};
};

}
