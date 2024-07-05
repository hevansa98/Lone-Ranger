#pragma once

#include <stdint.h>
#include <string>
#include <iostream>

namespace nmea
{

    const int NMEA_TALKER_ID_PREFIX_LENGTH = 2+1; /* Account for carriage return */

    enum NMEA_TALKER_ID_PREFIX_ENUM
    {
        BEIDOU_1,
        BEIDOU_2,
        GALILEO,
        GPS,
        GLONASS,
        NMEA_TALKER_ID_PREFIX_COUNT
    };

    char NMEA_TALKER_ID_PREFIX_CHAR[NMEA_TALKER_ID_PREFIX_COUNT][NMEA_TALKER_ID_PREFIX_LENGTH]
    {
        "BD",
        "GB",
        "GA",
        "GP",
        "GL"
    };

    const int NMEA_TALKER_ID_POSTFIX_LENGTH = 3+1; /* Account for carriage return */

    enum NMEA_TALKER_ID_POSTFIX_ENUM
    {
        GGA_GPS_FIXED_DATA,
        GLL_GEOGRAPHIC_POSITION_LLA,
        GSA_GNSS_DOP_AND_ACTIVE_SATELLITES,
        GSV_GNSS_SATELLITES_IN_VIEW,
        RMC_RECOMMENDED_MINIMUM_SPECIFIC_GPS_DATA,
        VTG_COURSE_OVER_GROUND_AND_GROUND_SPEED,
        NMEA_TALKER_ID_POSTFIX_COUNT
    };

    char NMEA_TALKER_ID_POSTFIX_CHAR[NMEA_TALKER_ID_POSTFIX_COUNT][NMEA_TALKER_ID_POSTFIX_LENGTH]
    {
        "GGA",
        "GLL",
        "GSA",
        "GSV",
        "RMC",
        "VTG"
    };

    class nmea_format
    {
        public:
            nmea_format(){};
            ~nmea_format(){};

        protected:

            typedef struct _Current_Fields_Struct
            {
                uint64_t UTC;
                double Latitude;
                double Longitude;
                int Checksum;
                _Current_Fields_Struct()
                {
                    UTC = 0;
                    Latitude = Longitude = 0.0;
                    Checksum = 0;
                }
            } Current_Fields_Struct;

            std::string RAW_String;
            virtual void Process_Fields() = 0;

            bool Is_Checksum_Valid(const std::string& Whole_Message, int & Output_Checksum) 
            {
                bool Valid_Checksum = false;

                /* Remove the starting $ and the incoming checksum */
                std::string Removed_Prefix_Delimiters = RAW_String.substr(1, RAW_String.length()-4);
                /* Isolate the incoming checksum to compare against */
                std::string RAW_Checksum = RAW_String.substr(RAW_String.length()-2, RAW_String.length());

                Output_Checksum = 0;

                for (char ch : Removed_Prefix_Delimiters) {
                    if(ch != ',')
                    {
                        Output_Checksum ^= ch; // XOR operation with each character
                    }
                }

                if(stoi(RAW_Checksum, 0, 16) == Output_Checksum)
                {
                    Valid_Checksum = true;
                }

                return Valid_Checksum;
            }

            void Convert_RAW_LLA_To_Decimal(const double & RAW, double & Decimal){

                double DD, SS; /* Decimal Degrees, Decimal Seconds */

                DD  = int(double(RAW)/100.0);

                SS  = double(RAW) - DD * 100.0;

                Decimal  = DD + SS/60.0;

            }

            void Convert_UTC(const std::string & RAW_UTC, uint64_t & Output_UTC)
            {
                Output_UTC = stoul(RAW_UTC);
            }
    };

}