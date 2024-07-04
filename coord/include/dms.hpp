#pragma once

#include <altitude.hpp>

namespace coord
{

class DMS
{

    public:

        const int Degrees, Minutes;
        const double Seconds;
        const Alt Altitude;
        const LLA_Type LLA_Dimension;

    public:

        DMS(const int & Degrees, const int & Minutes, const double & Seconds, const Alt & Altitude, const LLA_Type & LLA_Dimension) : 
            Degrees(Degrees),
            Minutes(Minutes),
            Seconds(Seconds),
            Altitude(Altitude),
            LLA_Dimension(LLA_Dimension)
        {};

        DMS(void) : 
            Degrees(0),
            Minutes(0),
            Seconds(0.0),
            Altitude(Alt(Alt_Type::HAE, 0.0)),
            LLA_Dimension(LLA_Type::LATITUDE)
        {};

        DMS(const DMS & DMS_p) : 
            Degrees(DMS_p.Degrees),
            Minutes(DMS_p.Minutes),
            Seconds(DMS_p.Seconds),
            Altitude(DMS_p.Altitude),
            LLA_Dimension(DMS_p.LLA_Dimension)
        {};

        ~DMS(){};
};

}