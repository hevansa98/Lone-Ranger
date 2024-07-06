#include <iostream>
#include <thread>
#include <array>
#include <fstream>
#include <sstream>

#include <nmea.parse.hpp>

#include <transforms.earth.hpp>
#include <transforms.distance.hpp>

using namespace std;

unique_ptr<coord::LLA> LLA_1, LLA_2;

const coord::Alt DEFAULT_ALT(coord::Alt_Type::MSL, 0.0);

void spawn1()
{
    LLA_1 = make_unique<coord::LLA>(33.116560, -97.034864, DEFAULT_ALT);

    coord::DMS DMS_1(coord::LLA_To_DMS(*LLA_1, coord::LLA_Type::LATITUDE));
}

void spawn2()
{
    LLA_2 = make_unique<coord::LLA>(32.990590, -96.908204, DEFAULT_ALT);

    coord::DMS DMS_1(coord::LLA_To_DMS(*LLA_2, coord::LLA_Type::LATITUDE));
}

int main(void)
{

    //thread tr1(spawn1);
    //thread tr2(spawn2);

    //coord::LLA LLA_1(33.116560, -97.034864, DEFAULT_ALT);
    //coord::LLA LLA_2(32.990590, -96.908204, DEFAULT_ALT);

    //tr1.join();
    //tr2.join();

    //coord::Distance_To_Point(*LLA_1, *LLA_2);

    //coord::LLA LLA_2(coord::DMS_To_LLA(DMS_1));

    ifstream GPS_Stream("/dev/ttyAMA0", ios::in);

    string Current_Line;

    array<string, 30> Read_Buffer;

    const int Buffer_Size = 30;

    int count = 0;

    unique_ptr<nmea::nmea_parse> Parser;

    while(getline(GPS_Stream, Current_Line))
    {
        if(Current_Line[0] == '$')
        {
            Read_Buffer.at(count) = Current_Line;
            //cout << "Size: " << Read_Buffer.size() << " Count: " << count << " " << Read_Buffer.at(count) << endl;
            Parser = make_unique<nmea::nmea_parse>(Current_Line);
            //if(Current_Line.substr(3, 3) == "GGA")
            //nmea::nmea_format_gga ohboy(Current_Line);
            //if(Current_Line.substr(3, 3) == "RMC")
            //nmea::nmea_format_rmc ohboy(Current_Line);

            if(count == Buffer_Size-1)
            {
                count = 0;
            }
            else
            {
                count++;
            }
        }
    }

    return EXIT_SUCCESS;
}