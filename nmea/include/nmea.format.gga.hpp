#pragma once

#include <string>
#include <iostream>
#include <iomanip>

#include <nmea.format.hpp>

namespace nmea
{
    class nmea_format_gga : protected nmea_format
    {
    private:
        enum class FIELDS
        {
            MESSAGE_ID,
            UTC_POS_FIX,
            LATITUDE,
            LATITUDE_DIRECTION,
            LONGITUDE,
            LONGITUDE_DIRECTION,
            GPS_QUALITY_INDICATOR,
            SV_IN_USE,
            HDOP,
            ORTHOMETRIC_HEIGHT_MSL,
            ORTHOMETRIC_HEIGHT_MSL_UNIT,
            GEOID_SEPARATION,
            GEOID_SEPARATION_UNIT,
            AGE_OF_DIFFERENTIAL_GPS_DATA_RECORD,
            REFERENCE_STATION_ID,
            CHECKSUM,
            NUM_OF_FIELDS
        };
        std::string Currently_Processed_Message_Dbg[(size_t)FIELDS::NUM_OF_FIELDS];

        void Process_Fields() final;
        
    public:
        nmea_format_gga(std::string);
        ~nmea_format_gga();
    };
    
    nmea_format_gga::nmea_format_gga(std::string RAW_Input)
    {
        FIELDS Currently_Processed_Field = FIELDS::MESSAGE_ID;

        RAW_String = RAW_Input;

        for(std::string::iterator Current_Character = RAW_Input.begin(); Current_Character != RAW_Input.end(); Current_Character++)
        {
            if((*Current_Character == ',') || (*Current_Character == '*'))
            {
                Currently_Processed_Field = (FIELDS)((size_t)Currently_Processed_Field + 1);      
            }

            if((*Current_Character != ',') && (*Current_Character != '*'))
            {
                Currently_Processed_Message_Dbg[(size_t)Currently_Processed_Field] += *Current_Character;
            }
        }

        /* Validate the checksum first so we do not waste time on bad data */
        if(Is_Checksum_Valid(RAW_String, Current_Fields.Checksum))
        {
            Process_Fields();
        }
    }
    
    nmea_format_gga::~nmea_format_gga()
    {
    }

    void nmea_format_gga::Process_Fields()
    {
        for(size_t Field = (size_t)FIELDS::MESSAGE_ID; Field < (size_t)FIELDS::NUM_OF_FIELDS; Field++)
        {
            switch ((FIELDS)Field)
            {
                case FIELDS::MESSAGE_ID:
                    break;
                case FIELDS::UTC_POS_FIX:

                    Convert_UTC(Currently_Processed_Message_Dbg[(size_t)FIELDS::UTC_POS_FIX], Current_Fields.UTC);
                    break;

                case FIELDS::LATITUDE:

                    Convert_RAW_LLA_To_Decimal( std::stod(Currently_Processed_Message_Dbg[(size_t)FIELDS::LATITUDE]), 
                                                Current_Fields.Latitude );
                    break;

                case FIELDS::LATITUDE_DIRECTION:

                    if(Currently_Processed_Message_Dbg[(size_t)FIELDS::LATITUDE_DIRECTION][0] == 'S')
                    {
                        Current_Fields.Latitude *= -1.0;
                    }
                    break;

                case FIELDS::LONGITUDE:

                    Convert_RAW_LLA_To_Decimal( std::stod(Currently_Processed_Message_Dbg[(size_t)FIELDS::LONGITUDE]), 
                                                Current_Fields.Longitude );
                    break;

                case FIELDS::LONGITUDE_DIRECTION:

                    if(Currently_Processed_Message_Dbg[(size_t)FIELDS::LONGITUDE_DIRECTION][0] == 'W')
                    {
                        Current_Fields.Longitude *= -1.0;
                    }
                    break;

                case FIELDS::GPS_QUALITY_INDICATOR:
                    break;
                case FIELDS::SV_IN_USE:
                    break;
                case FIELDS::HDOP:
                    break;
                case FIELDS::ORTHOMETRIC_HEIGHT_MSL:
                    break;
                case FIELDS::ORTHOMETRIC_HEIGHT_MSL_UNIT:
                    break;
                case FIELDS::GEOID_SEPARATION:
                    break;
                case FIELDS::GEOID_SEPARATION_UNIT:
                    break;
                case FIELDS::AGE_OF_DIFFERENTIAL_GPS_DATA_RECORD:
                    break;
                case FIELDS::REFERENCE_STATION_ID:
                    break;
                case FIELDS::CHECKSUM:
                    break;
                default:
                    break;
            }
        }

        std::cout << std::setprecision(10) << "Lat/Long Dec: " << Current_Fields.Latitude << ", " << Current_Fields.Longitude << std::endl;
    }
    
}