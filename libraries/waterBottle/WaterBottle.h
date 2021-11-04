// placeholder file for waterbottle class, uses RGB and weight sensors

#include "HX711.h"
#include "Adafruit_TCS34725.h"
#include <Wire.h>

#ifndef WATER_BOTTLE_H
#define WATER_BOTTLE_H

class WaterBottle
{
    private:
        //HX711 wSensors;
	Adafruit_TCS34725 colorSensor;
	uint16_t rBottle, gBottle, bBottle, cBottle;
	double X;

    public:
        HX711 wSensors; // public for testing
        WaterBottle(byte HX711CLK, byte HX711Dout, byte HX711Gain /* stuff like pins for sensors*/);
	
        void tareWeightPlate();
        void calibrateBottleWeight(short knownBottleWeight); // in grams
        short getWaterWeight();
	
	void calibrateColor();
	int isWater();
	int getColor();

};

#endif // WATER_BOTTLE_H
