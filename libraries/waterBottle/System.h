//#include <Arduino.h> // maybe just need stdint.h? only included for bytes
#include <stdint.h>
#include "registers.h"

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
    private:

        const byte BATTERY_PIN = A6;
        float ADCRefVoltage;
        byte ADCResolution;



    public:
        System(/* stuff like pins for sensors*/);

        bool batteryIsLow(float threshold);

        void enableLFClock(short en); // 0 or 1, might not need function at all

        void enableDCReg(short en); // might save some power, make private or remove function later, public for testing
        void enterSleepMode(); // need some way to wake microcontroller up
        // void enable low power mode? not sure if needed, system already starts in this mode?
};

#endif // SYSTEM_H
