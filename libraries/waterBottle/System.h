#include <Arduino.h>
#include "registers.h"
#include <Wire.h>
#include "Adafruit_LIS3DH.h"
#include "Adafruit_Sensor.h"

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
    private:

        Adafruit_LIS3DH lis;
        const int INTERRUPT_PIN = A0;
        const int LIS3DH_ADDR = 0x18;

        const byte BATTERY_PIN = A6;
        float ADCRefVoltage;
        byte ADCResolution;

        // enables ultra low power 32.768 kHz clock
        void enableLFClock();

        // enables DC/DC regulator for microchip voltage supply
        void enableDCReg();

        // i2c read register function, for accelerometer registers
        unsigned int readRegister(byte reg);

        // i2c write register function, for accelerometer registers
        void writeRegister(byte reg, byte data);

    public:
        System();

        // enables options for low power (wasn't working in constructor, not sure why)
        void setLowPower();

        // returns battery percentage as an integer from 0 to 100. 100 is returned if
        // battery is disconnected.
        int getBatteryPct();

        // initializes accelerometer
        void init_ACC();

        // returns 1 or 0 if system is still or not, using an average of times
        // accelerometer readings
        int is_still(byte times);
};

#endif // SYSTEM_H
