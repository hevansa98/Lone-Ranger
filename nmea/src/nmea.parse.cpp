#include <nmea.parse.hpp>
#include <iostream>

namespace nmea
{

    nmea_parse::nmea_parse(std::string RAW, std::vector<Satellite_Data_Type> & Satellite_Table)
    {

        if(RAW.empty() == false)
        {
            std::string Prefix = RAW.substr(3, 3);
            std::cout << Prefix << std::endl;
            
            if(RAW[0] == '$')
            {

                if(Prefix.compare(NMEA_TALKER_ID_POSTFIX_CHAR[GGA_GPS_FIXED_DATA]) == 0)
                {
                    nmea_format_gga GGA(RAW);
                }

                if(Prefix.compare(NMEA_TALKER_ID_POSTFIX_CHAR[GLL_GEOGRAPHIC_POSITION_LLA]) == 0)
                {

                }

                if(Prefix.compare(NMEA_TALKER_ID_POSTFIX_CHAR[GSA_GNSS_DOP_AND_ACTIVE_SATELLITES]) == 0)
                {

                }

                if(Prefix.compare(NMEA_TALKER_ID_POSTFIX_CHAR[GSV_GNSS_SATELLITES_IN_VIEW]) == 0)
                {
                    nmea_format_gsv GSV(RAW, Satellite_Table);
                }

                if(Prefix.compare(NMEA_TALKER_ID_POSTFIX_CHAR[RMC_RECOMMENDED_MINIMUM_SPECIFIC_GPS_DATA]) == 0)
                {
                    nmea_format_rmc RMC(RAW);
                }

                if(Prefix.compare(NMEA_TALKER_ID_POSTFIX_CHAR[VTG_COURSE_OVER_GROUND_AND_GROUND_SPEED]) == 0)
                {

                }

            }
        }
    }

    nmea_parse::~nmea_parse()
    {
    }

}