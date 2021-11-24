// file for waterbottle class, uses RGB and weight sensors

#include "HX711.h"
#include "Adafruit_TCS34725.h"
#include <Wire.h>

#ifndef WATER_BOTTLE_H
#define WATER_BOTTLE_H

class WaterBottle
{
    private:
        HX711 wSensor;

        Adafruit_TCS34725 colorSensor;
        uint16_t rBottle, gBottle, bBottle, cBottle;
        double X;

    public:
        // constructor, requires that nothing be on weight sensors when started
        WaterBottle(byte HX711CLK, byte HX711Dout);

        // tares the initial weight on the weight sensor
        void tareWeightPlate();

        // calibrates the weight sensor readings, requires an empty bottle to be
        // placed on the weight sensing plate
        void calibrateBottleWeight(short knownBottleWeight); // in grams

        // returns the current weight of water in the water bottle
        short getWaterWeight();

        // saves the base color of the water bottle
        void calibrateColor();

        // gets the color of the liquid in the water bottle, returns 1 if water,
        // 0 if not
        int isWater();

        // is_still returns 1 if the bottle is not in motion or tilt
        int is_still();
};

#endif // WATER_BOTTLE_H