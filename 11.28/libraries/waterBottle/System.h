#include <Arduino.h>
#include "registers.h"
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

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

        void enableLFClock(byte en);

        void enableDCReg(byte en);

        void turnOffMemory();

    public:
        System();

        float getBatteryVoltage();

        void enterSleepMode();

        void init_ACC(void);
        unsigned int readRegister(byte reg);
        void writeRegister(byte reg, byte data);

        int is_still();
};

#endif // SYSTEM_H