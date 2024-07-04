#include <iostream>
#include <thread>

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

    thread tr1(spawn1);
    thread tr2(spawn2);

    //coord::LLA LLA_1(33.116560, -97.034864, DEFAULT_ALT);
    //coord::LLA LLA_2(32.990590, -96.908204, DEFAULT_ALT);

    tr1.join();
    tr2.join();

    coord::Distance_To_Point(*LLA_1, *LLA_2);

    //coord::LLA LLA_2(coord::DMS_To_LLA(DMS_1));

    return EXIT_SUCCESS;
}