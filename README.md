# Lone-Ranger

Lone Ranger utilizes a NEO-6M GPS module via Raspberry Pi GPIO to receive GPS information at 1 Hz

Lone Ranger is currently comprised of 2 libraries in addition to the core operating routine: nmea and coord

## nmea 

nmea is responsible for interpreting the NEO-6M NMEA-Standard formatted messages

NMEA Message Information sourced from [NovAtel](https://docs.novatel.com/OEM7/Content/Logs/Core_Logs.htm?tocpath=Commands%20%2526%20Logs%7CLogs%7CGNSS%20Logs%7C_____0) and [Trimble](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_MessageOverview.html?tocpath=Output%20Messages%7CNMEA-0183%20Messages%7C_____0)

Currently supports the following NMEA message types:

`GGA`
`RMC`
`GSV`

## coord

coord is a coordinate transformation library to handle LLA (Latitude, Longitude, Altitude) operations

# 🚧 Installation 
## (Compile instructions valid, Raspberry Pi setup instructions still in work)

Assumes Raspberry Pi 5 Platform

Assumes NEO-6M module on UART GPIO connection

nmea library assumes NEO-6M publishes device at `/dev/ttyAMA0`
```
mkdir build
cd build
cmake ..
make
```
