// file for bluetooth communication

#include <bluefruit.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

#ifndef BLE_COMMS_H
#define BLE_COMMS_H

//void connect_callback(uint16_t conn_handle);
//void disconnect_callback(uint16_t conn_handle, uint8_t reason);

class BLEComms
{
    private:
        BLEDfu bledfu;  // OTA DFU service
        BLEDis bledis;  // device information
        BLEUart bleuart; // uart over ble
        BLEBas blebas;  // battery

        void setupAdv();

        static void connect_callback(uint16_t conn_handle);

        static void disconnect_callback(uint16_t conn_handle, uint8_t reason);

    public:
        void connectToApp();

        // measWeight - four digits max (0 - 9999)
        // isWater - one digit max (0 or 1)
        // batteryPct - three digits max (0 - 100)
        // sends data as a string given by "measWeight isWater batteryPct"
        void sendData(short measWeight, byte isWater, byte batteryPct);

        //short getData();

        // returns true if app has requested calibration, done by sending a "1"
        // to the microcontroller
        bool calibrateRequest();

        //static void connect_callback(uint16_t conn_handle);

        //static void disconnect_callback(uint16_t conn_handle, uint8_t reason);
};

#endif // BLE_COMMS_H
