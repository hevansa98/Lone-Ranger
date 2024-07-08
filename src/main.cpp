#include <iostream>
#include <thread>
#include <array>
#include <fstream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <semaphore>

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

std::shared_ptr<std::mutex> Mute_Satellite;
std::shared_ptr<std::binary_semaphore> Semaphore_Satellite;

std::vector<nmea::Satellite_Data_Type> Satellite_Table;

void Produce_Data()
{

    ifstream GPS_Stream("/dev/ttyAMA0", ios::in);

    string Current_Line;

    array<string, 30> Read_Buffer;

    const int Buffer_Size = 30;

    int count = 0;

    unique_ptr<nmea::nmea_parse> Parser;

    Parser = std::make_unique<nmea::nmea_parse>();
    Parser->Assign_Satellite_Table_Mutex(&Satellite_Table, Semaphore_Satellite);

    while(getline(GPS_Stream, Current_Line))
    {
        Read_Buffer.at(count) = Current_Line;

        Parser->Parse(Read_Buffer.at(count));

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

void Consume_Data()
{
    std::vector<nmea::Satellite_Data_Type> Local_Sat_Data;
    while(true)
    {
        Semaphore_Satellite->acquire();
        {
            if((Satellite_Table.size() == Satellite_Table.capacity()) && (Satellite_Table.capacity() > 0))
            {
                auto start = std::chrono::high_resolution_clock::now();
                //for(const nmea::Satellite_Data_Type Sat : Satellite_Table)
                //{
                //    std::cout << "ID: " << Sat.ID << " Azimuth: " << Sat.Azimuth << " Elevation: " << Sat.Elevation << " SNR: " << Sat.SNR << std::endl;
                //}
                Local_Sat_Data = Satellite_Table;
                Satellite_Table.clear();
                Satellite_Table.shrink_to_fit();
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                std::cout << "Time elapsed: " << duration.count() << std::endl;
            }
            else
            {
                //std::cout << "Size: " << Satellite_Table.size() << " Capacity: " << Satellite_Table.capacity() << std::endl;
            }
        }
        Semaphore_Satellite->release();
        //usleep(20);
    }
}

int main(void)
{

    Mute_Satellite = make_shared<std::mutex>();
    Semaphore_Satellite = make_shared<std::binary_semaphore>(1);
    Satellite_Table.clear();

    //thread tr1(spawn1);
    //thread tr2(spawn2);

    //coord::LLA LLA_1(33.116560, -97.034864, DEFAULT_ALT);
    //coord::LLA LLA_2(32.990590, -96.908204, DEFAULT_ALT);

    //tr1.join();
    //tr2.join();

    //coord::Distance_To_Point(*LLA_1, *LLA_2);

    //coord::LLA LLA_2(coord::DMS_To_LLA(DMS_1));

    thread tr1(Produce_Data);
    //Semaphore_Satellite->release();
    thread tr2(Consume_Data);

    tr1.join();
    tr2.join();

    return EXIT_SUCCESS;
}