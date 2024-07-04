#pragma once

#ifdef DEBUG_COORD
#include <iostream>
#endif

#include <dms.hpp>
#include <lla.hpp>

namespace coord
{
    /* Converts from a LLA reference to an DMS reference */
    /* @param LLA_p LLA reference */
    /* @param LLA_Select_p selects output as Latitude or Longitude */
    /* @return DMS translation of LLA_p */
    DMS LLA_To_DMS(const LLA & LLA_p, const LLA_Type & LLA_Select_p)
    {

        double LL      = -360.0;
        int    Degrees = -360.0;
        int    Minutes = -360.0;
        double Seconds = -360.0;
        Alt    Altitude = LLA_p.Altitude;

        switch (LLA_Select_p)
        {
        case LLA_Type::LATITUDE:
            LL = LLA_p.Get_Latitude(Angular_Type::DEGREES);
            break;
        case LLA_Type::LONGITUDE:
            LL = LLA_p.Get_Longitude(Angular_Type::DEGREES);
            break;
        
        default:
            DMS DMS_p(Degrees, Minutes, Seconds, Altitude, LLA_Select_p);
            return DMS_p;
            break;
        }

        Degrees = LL;
        Minutes = (LL - Degrees) * 60.0;
        Seconds = (LL - Degrees - Minutes / 60.0) * 3600.0;

        DMS DMS_p(Degrees, Minutes, Seconds, Altitude, LLA_Select_p);

        #ifdef DEBUG_COORD
            std::cout << "Degrees: "  << DMS_p.Degrees << "\n";
            std::cout << "Minutes: "  << DMS_p.Minutes << "\n";
            std::cout << "Seconds: "  << DMS_p.Seconds << "\n";
            std::cout << "Altitude: " << DMS_p.Altitude.Altitude << std::endl;
        #endif

        return DMS_p;
    }

    /* Converts from a DMS reference to an LLA reference */
    /* @param DMS_p DMS reference */
    /* @return LLA translation of DMS_p */
    LLA DMS_To_LLA(const DMS & DMS_p)
    {
        double LL = 0.0;

        LL = (double)(DMS_p.Degrees) + (DMS_p.Minutes/60.0) + (DMS_p.Seconds/3600.0);

        LLA LLA_p(DMS_p.LLA_Dimension == LLA_Type::LATITUDE  ? LL : 0.0, 
                  DMS_p.LLA_Dimension == LLA_Type::LONGITUDE ? LL : 0.0, 
                  DMS_p.Altitude);

        #ifdef DEBUG_COORD
            std::cout << "Latitude: "  << LLA_p.Get_Latitude(Angular_Type::DEGREES) << "\n";
            std::cout << "Longitude: " << LLA_p.Get_Longitude(Angular_Type::DEGREES) << "\n";
            std::cout << "Altitude: "  << LLA_p.Altitude.Altitude << std::endl;
        #endif

        return LLA_p;
    }
}