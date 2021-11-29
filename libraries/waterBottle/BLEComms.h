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
        //BLEUart bleuart; // uart over ble
        BLEBas blebas;  // battery

        void setupAdv();

        static void connect_callback(uint16_t conn_handle);

        static void disconnect_callback(uint16_t conn_handle, uint8_t reason);

    public:
        BLEUart bleuart; // uart over ble (public for testing, keep private otherwise)
        void connectToApp();

        void sendData(uint8_t data, int count); // doesn't work (compile error)

        uint8_t getData();

        //static void connect_callback(uint16_t conn_handle);

        //static void disconnect_callback(uint16_t conn_handle, uint8_t reason);
};

#endif // BLE_COMMS_H
