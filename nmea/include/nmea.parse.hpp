#pragma once

#include <nmea.format.gga.hpp>
#include <nmea.format.rmc.hpp>
#include <nmea.format.gsv.hpp>

#include <string>

namespace nmea
{

    class nmea_parse
    {
    private:
        /* data */
    public:
        nmea_parse(std::string, std::vector<Satellite_Data_Type> &);
        ~nmea_parse();
    };

}
