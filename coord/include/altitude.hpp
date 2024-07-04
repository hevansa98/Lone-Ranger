#pragma once

#ifdef DEBUG_COORD
#include <iostream>
#endif

#include <coord_types.hpp>

namespace coord
{

class Alt
{
public:
    const Alt_Type Alt_Ref;
    const double Altitude;
public:
    Alt(const Alt_Type & Ref, const double & Altitude) : 
        Alt_Ref(Ref), 
        Altitude(Altitude)
    {};
    Alt(const Alt & Altitude_p) : 
        Alt_Ref(Altitude_p.Alt_Ref), 
        Altitude(Altitude_p.Altitude)
    {};
    ~Alt(){};
};

};
