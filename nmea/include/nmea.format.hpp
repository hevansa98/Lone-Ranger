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

    typedef struct _Satellite_Data_Type
    {
        uint64_t ID, Elevation, Azimuth, SNR;
        _Satellite_Data_Type()
        {
            ID = Elevation = Azimuth = SNR = 0;
        };
    }Satellite_Data_Type;

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
                uint64_t Checksum;
                _Current_Fields_Struct()
                {
                    UTC = 0;
                    Latitude = Longitude = 0.0;
                    Checksum = 0;
                }
            } Current_Fields_Struct;
        
            Current_Fields_Struct Current_Fields;

            double   Get_Latitude (void){ return Current_Fields.Latitude; };
            double   Get_Longitude(void){ return Current_Fields.Longitude; };
            uint64_t Get_UTC      (void){ return Current_Fields.UTC; };

            std::string RAW_String;

            /* Processes and parses the NMEA data */
            virtual void Process_Fields() = 0;

            /* Checks the NMEA string and calculates the checksum to evaluate against */
            /* @param Whole_Message NMEA message unaltered */
            /* @param Output_Checksum Calculated checksum */
            /* @return Whether calculated checksum matches message checksum */
            bool Is_Checksum_Valid(const std::string& Whole_Message, uint64_t & Output_Checksum) 
            {
                bool Valid_Checksum = false;

                /* Remove the starting $ and the incoming checksum */
                std::string Removed_Prefix_Delimiters = RAW_String.substr(1, RAW_String.length()-4);
                /* Isolate the incoming checksum to compare against */
                std::string RAW_Checksum = RAW_String.substr(RAW_String.length()-2, 2);

                Output_Checksum = 0;

                /* Despite some sources indicating commas need be ignored, keep the commas in the calculation */
                for (char ch : Removed_Prefix_Delimiters) {
                    Output_Checksum ^= ch; // XOR operation with each character
                }

                if(stoi(RAW_Checksum, 0, 16) == Output_Checksum)
                {
                    Valid_Checksum = true;
                }

                return Valid_Checksum;
            }

            /* Converts NMEA LLA format to Decimal format */
            /* @param RAW NMEA LLA format DDMM.MMMM */
            /* @param Decimal Degrees in decimal format DD.DDDD */
            void Convert_RAW_LLA_To_Decimal(const double & RAW, double & Decimal){

                double DD, SS; /* Decimal Degrees, Decimal Seconds */

                DD  = int(double(RAW)/100.0);

                SS  = double(RAW) - DD * 100.0;

                Decimal  = DD + SS/60.0;

            }

            /* Parses the UTC value from the NMEA string */
            /* @param RAW_UTC NMEA UTC unaltered */
            /* @param Output_UTC Parsed UTC value */
            void Convert_UTC(const std::string & RAW_UTC, uint64_t & Output_UTC)
            {
                Output_UTC = stoul(RAW_UTC);
            }
    };

}