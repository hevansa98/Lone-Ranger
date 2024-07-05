#include <fstream>
#include <sstream>
#include <array>

#include <iostream>

using namespace std;

int main(void)
{

    ifstream GPS_Stream("/dev/ttyAMA0", ios::in);

    string Current_Line;

    array<string, 30> Read_Buffer;

    const int Buffer_Size = 30;

    int count = 0;

    while(getline(GPS_Stream, Current_Line))
    {
        if(Current_Line[0] == '$')
        {
            Read_Buffer.at(count) = Current_Line;
            cout << "Size: " << Read_Buffer.size() << " Count: " << count << " " << Read_Buffer.at(count) << endl;
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
    //int GPS_Device = open("/dev/ttyAMA0", O_RDONLY);
    //if(GPS_Device == -1)
    //{
    //    cout << "Could not open /dev/ttyAMA0" << endl;
    //}
    //char read_buf [256];
    //string tmp;
//
    //while(1)
    //{
    //    // Read bytes. The behaviour of read() (e.g. does it block?,
    //    // how long does it block for?) depends on the configuration
    //    // settings above, specifically VMIN and VTIME
    //    int n = read(GPS_Device, &read_buf, sizeof(read_buf));
//
    //    tmp = read_buf;
//
    //    cout << tmp << endl;
    //}

    return EXIT_SUCCESS;
}