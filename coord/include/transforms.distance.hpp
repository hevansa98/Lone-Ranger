#pragma once

#include <cmath>
#ifdef DEBUG_COORD
#include <iostream>
#endif

#include <dms.hpp>
#include <lla.hpp>

namespace coord
{
    /* Calculates the distance from LLA_1 to LLA_2 in meters using the Haversine formula */
    /* @param LLA_Point_1 Point of Origin */
    /* @param LLA_Point_2 End Point */
    /* @return Distance from LLA_Point_1 to LLA_Point_2 in meters */
    /* @link https://www.movable-type.co.uk/scripts/latlong.html */
    double Distance_To_Point(const LLA & LLA_Point_1, const LLA & LLA_Point_2)
    {
        const double Latitude_1 = LLA_Point_1.Get_Latitude(Angular_Type::RADIANS);
        const double Latitude_2 = LLA_Point_2.Get_Latitude(Angular_Type::RADIANS);
        const double Latitude_Distance = (LLA_Point_2.Get_Latitude(Angular_Type::RADIANS)-LLA_Point_1.Get_Latitude(Angular_Type::RADIANS));
        const double Longitude_Distance = (LLA_Point_2.Get_Longitude(Angular_Type::RADIANS)-LLA_Point_1.Get_Longitude(Angular_Type::RADIANS));

        const double a = sin(Latitude_Distance/2.0) * sin(Latitude_Distance/2.0) +
                         cos(Latitude_1) * cos(Latitude_2) *
                         sin(Longitude_Distance/2.0) * sin(Longitude_Distance/2.0);
        const double c = 2.0 * atan2(sqrt(a), sqrt(1-a));

        const double d = Earth_Radius_Meters * c; // in metres

        #ifdef DEBUG_COORD
            std::cout << "Distance: " << d << " meters" << std::endl;
        #endif

        return d;
    }
}