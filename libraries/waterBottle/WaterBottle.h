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
        const byte HX711_CLK_PIN = 12;
        const byte HX711_DOUT_PIN = 11;
        const byte HX711_GAIN = 64; // 64 or 128
        const short W_SENSOR_SCALE = 100; // temporary value, determined through testing, value of wSensor.get_units(10) / knownBottleWeight

        Adafruit_TCS34725 colorSensor;
        uint16_t rBottle, gBottle, bBottle, cBottle;
        float X;

    public:
        // constructor, requires that nothing be on weight sensors when started
        WaterBottle();

        // tares the initial weight on the weight sensor
        void tareWeightPlate();

        // returns the current weight measured
        short getWeight();

        // saves the base color of the water bottle, averaged over times readings
        void calibrateColor(byte times);

        // gets the color of the liquid in the water bottle, using times readings.
        // returns 1 if water, 0 if not
        int isWater(byte times);
};

#endif // WATER_BOTTLE_H
