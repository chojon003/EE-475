// placeholder file for waterbottle class, uses RGB and weight sensors

#include "HX711.h"

#ifndef WATER_BOTTLE_H
#define WATER_BOTTLE_H

class WaterBottle
{
  private:
    HX711 wSensors;

    short bottleWeight; // in grams
    

  public:
    WaterBottle(/* stuff like pins for sensors*/);

    calibrateBottleWeight();
    getWaterWeight();
};

#endif // WATER_BOTTLE_H
