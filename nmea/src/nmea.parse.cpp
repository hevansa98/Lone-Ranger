#include <nmea.parse.hpp>
#include <iostream>

namespace nmea
{

    nmea_parse::nmea_parse(std::string)
    {
        std::cout << NMEA_TALKER_ID_PREFIX_CHAR[GPS] << NMEA_TALKER_ID_POSTFIX_CHAR[VTG_COURSE_OVER_GROUND_AND_GROUND_SPEED] << std::endl;
    }

    nmea_parse::~nmea_parse()
    {
    }

}