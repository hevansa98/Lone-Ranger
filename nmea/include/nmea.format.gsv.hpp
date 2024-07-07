#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <nmea.format.hpp>

namespace nmea
{
        
    class nmea_format_gsv : protected nmea_format
    {
    private:
        enum class FIELDS
        {
            MESSAGE_ID,
            NUMBER_OF_MESSAGES,
            GSV_MESSAGE_COUNT,
            SATELLITES_IN_VIEW,
            SATELLITE_ID_1,
            ELEVATION_1,
            AZIMUTH_1,
            SIGNAL_NOISE_RATIO_1,
            SATELLITE_ID_2,
            ELEVATION_2,
            AZIMUTH_2,
            SIGNAL_NOISE_RATIO_2,
            SATELLITE_ID_3,
            ELEVATION_3,
            AZIMUTH_3,
            SIGNAL_NOISE_RATIO_3,
            SATELLITE_ID_4,
            ELEVATION_4,
            AZIMUTH_4,
            SIGNAL_NOISE_RATIO_4,
            CHECKSUM,
            NUM_OF_FIELDS
        };
        std::string Currently_Processed_Message_Dbg[(size_t)FIELDS::NUM_OF_FIELDS];

        const int STARTING_GSV_BUNDLE_MESSAGE_ID = 1;

        std::vector<Satellite_Data_Type> & Satellite_Table;

        void Process_Fields() final;
        
    public:

        nmea_format_gsv(std::string, std::vector<Satellite_Data_Type> &);
        ~nmea_format_gsv();
    };
    
    nmea_format_gsv::nmea_format_gsv(std::string RAW_Input, std::vector<Satellite_Data_Type> & Incoming_Satellite_Table) : Satellite_Table(Incoming_Satellite_Table)
    {
        FIELDS Currently_Processed_Field = FIELDS::MESSAGE_ID;

        RAW_String = RAW_Input;

        std::cout << RAW_String << std::endl;

        for(std::string::iterator Current_Character = RAW_Input.begin(); Current_Character != RAW_Input.end(); Current_Character++)
        {
            /* Wait for the SATELLITES_IN_VIEW to finish being processed */
            /* Check before processing the delimiter so a blank value is not calculated */
            if((Currently_Processed_Field == FIELDS::SATELLITES_IN_VIEW) && (*Current_Character == ','))
            {
                /* Check the first sat info, if it is the first GSV message in the bundle, resize the vector */
                int Current_Message = stoul(Currently_Processed_Message_Dbg[(size_t)FIELDS::GSV_MESSAGE_COUNT]);

                if(Current_Message == STARTING_GSV_BUNDLE_MESSAGE_ID)
                {
                    Satellite_Table.clear();
                    Satellite_Table.reserve(stoul(Currently_Processed_Message_Dbg[(size_t)FIELDS::SATELLITES_IN_VIEW]));
                    std::cout << "Number of sats: " << Satellite_Table.capacity() << std::endl;
                }
            }

            /* At the end of each sat bundle, check if the next element is the checksum delimiter */
            if(((Currently_Processed_Field == FIELDS::SIGNAL_NOISE_RATIO_1) ||
                (Currently_Processed_Field == FIELDS::SIGNAL_NOISE_RATIO_2) ||
                (Currently_Processed_Field == FIELDS::SIGNAL_NOISE_RATIO_3)) &&
               (*Current_Character == '*'))
            {
                //std::cout << "Jumping to checksum from " << (size_t)Currently_Processed_Field << std::endl;
                /* Jump to processing the checksum */
                Currently_Processed_Field = FIELDS::CHECKSUM;
            }

            /* If on a delimiter, move to the next element */
            else if((*Current_Character == ',') || (*Current_Character == '*'))
            {
                Currently_Processed_Field = (FIELDS)((size_t)Currently_Processed_Field + 1);      
            }

            /* Append the current character to the field string */
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
    
    nmea_format_gsv::~nmea_format_gsv()
    {
    }

    void nmea_format_gsv::Process_Fields()
    {
        /* Tracking value to be added to the vector */
        Satellite_Data_Type Current_Satellite;
        /* Tracks if the necessary number of fields are populated so that the Sat info can be added to the vector */
        int Valid_Field_Counter = 0;
        for(size_t Field = (size_t)FIELDS::MESSAGE_ID; Field < (size_t)FIELDS::NUM_OF_FIELDS; Field++)
        {
            switch ((FIELDS)Field)
            {
                case FIELDS::SATELLITE_ID_1:
                case FIELDS::SATELLITE_ID_2:
                case FIELDS::SATELLITE_ID_3:
                case FIELDS::SATELLITE_ID_4:

                    if(Satellite_Table.capacity() > 0)
                    {
                        //std::cout << "SATELLITE_ID_" << (size_t)(Field) << ": " << Currently_Processed_Message_Dbg[(size_t)Field] << std::endl;
                        if(!Currently_Processed_Message_Dbg[(size_t)Field].empty())
                        {
                            Valid_Field_Counter++;
                            Current_Satellite.ID = stoul(Currently_Processed_Message_Dbg[(size_t)Field]);
                        }
                    }
                    break;

                case FIELDS::ELEVATION_1:
                case FIELDS::ELEVATION_2:
                case FIELDS::ELEVATION_3:
                case FIELDS::ELEVATION_4:

                    if(Satellite_Table.capacity() > 0)
                    {
                        //std::cout << "ELEVATION_" << (size_t)(Field) << ": " << Currently_Processed_Message_Dbg[(size_t)Field] << std::endl;
                        if(!Currently_Processed_Message_Dbg[(size_t)Field].empty())
                        {
                            Valid_Field_Counter++;
                            Current_Satellite.Elevation = stoul(Currently_Processed_Message_Dbg[(size_t)Field]);
                        }
                    }
                    break;

                case FIELDS::AZIMUTH_1:
                case FIELDS::AZIMUTH_2:
                case FIELDS::AZIMUTH_3:
                case FIELDS::AZIMUTH_4:

                    if(Satellite_Table.capacity() > 0)
                    {
                        //std::cout << "AZIMUTH_" << (size_t)(Field) << ": " << Currently_Processed_Message_Dbg[(size_t)Field] << std::endl;
                        if(!Currently_Processed_Message_Dbg[(size_t)Field].empty())
                        {
                            Valid_Field_Counter++;
                            Current_Satellite.Azimuth = stoul(Currently_Processed_Message_Dbg[(size_t)Field]);
                        }
                    }
                    break;

                case FIELDS::SIGNAL_NOISE_RATIO_1:
                case FIELDS::SIGNAL_NOISE_RATIO_2:
                case FIELDS::SIGNAL_NOISE_RATIO_3:
                case FIELDS::SIGNAL_NOISE_RATIO_4:

                    if(Satellite_Table.capacity() > 0)
                    {
                        std::cout << "SNR_" << (size_t)(Field) << ": " << Currently_Processed_Message_Dbg[(size_t)Field] << " " << Currently_Processed_Message_Dbg[(size_t)Field].length() << std::endl;
                        if(!Currently_Processed_Message_Dbg[(size_t)Field].empty())
                        {
                            Valid_Field_Counter++;
                            Current_Satellite.SNR = stoul(Currently_Processed_Message_Dbg[(size_t)Field]);
                        }
                        if(Valid_Field_Counter >= 3)
                        {
                            Satellite_Table.push_back(Current_Satellite);
                        }
                    }
                    Valid_Field_Counter = 0;
                    break;
                    
                default:
                    break;
            }
        }
    }
    
}