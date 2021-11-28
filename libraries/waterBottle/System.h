#include <Arduino.h>
#include "registers.h"

#ifndef SYSTEM_H
#define SYSTEM_H
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

class System
{
    private:

        Adafruit_LIS3DH lis;
        const int INTERRUPT_PIN = A0;
        const int LIS3DH_ADDR = 0x18;
        unsigned int readRegister(byte reg);
        void writeRegister(byte reg, byte data);
        void init_ACC(void);


        const byte BATTERY_PIN = A6;
        float ADCRefVoltage;
        byte ADCResolution;

        void enableLFClock(byte en);

        void enableDCReg(byte en);

        void turnOffMemory();

    public:
        System(/* stuff like pins for sensors*/);

        float getBatteryVoltage();

        void enterSystemOffMode();

        int is_still(byte times);
};

#endif // SYSTEM_H
