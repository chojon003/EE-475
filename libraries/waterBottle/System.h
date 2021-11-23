#include <Arduino.h>
#include "registers.h"

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
    private:

        const byte BATTERY_PIN = A6;
        float ADCRefVoltage;
        byte ADCResolution;

        void enableLFClock(byte en);

        void enableDCReg(byte en);

        void turnOffMemory();

    public:
        System(/* stuff like pins for sensors*/);

        float getBatteryVoltage();

        void enterSleepMode();
};

#endif // SYSTEM_H
