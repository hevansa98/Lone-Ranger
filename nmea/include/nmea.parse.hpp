#pragma once

#include <mutex>
#include <semaphore>

#include <nmea.format.gga.hpp>
#include <nmea.format.rmc.hpp>
#include <nmea.format.gsv.hpp>

#include <string>

namespace nmea
{

    class nmea_parse
    {
    private:
        std::unique_ptr<nmea_format_gsv> GSV_Parser;
    public:
        nmea_parse();
        ~nmea_parse();

        void Parse(const std::string &);
        void Assign_Satellite_Table_Mutex(std::vector<Satellite_Data_Type> *, std::shared_ptr<std::binary_semaphore> = nullptr);
    };

}
