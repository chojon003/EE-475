// placeholder file for waterbottle class, uses RGB and weight sensors

#include "HX711.h"

#ifndef WATER_BOTTLE_H
#define WATER_BOTTLE_H

class WaterBottle
{
    private:
        //HX711 wSensors;

    public:
        HX711 wSensors; // public for testing
        WaterBottle(byte HX711CLK, byte HX711Dout, byte HX711Gain /* stuff like pins for sensors*/);

        void tareWeightPlate();
        void calibrateBottleWeight(short knownBottleWeight); // in grams
        short getWaterWeight();
};

#endif // WATER_BOTTLE_H
