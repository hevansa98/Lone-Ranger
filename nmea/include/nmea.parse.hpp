#pragma once

#include <nmea.format.gga.hpp>
#include <nmea.format.rmc.hpp>

#include <string>

namespace nmea
{

    class nmea_parse
    {
    private:
        /* data */
    public:
        nmea_parse(std::string);
        ~nmea_parse();
    };

}
