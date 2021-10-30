#include "WaterBottle.h"
#include <Adafruit_TinyUSB.h> // for testing, remove later

WaterBottle::WaterBottle(byte HX711CLK, byte HX711Dout)
{
  wSensors.begin(HX711Dout, HX711CLK); // add gain to this???
  wSensors.power_down();

  
}

void WaterBottle::tareWeightPlate()
{
  wSensors.power_up();

  wSensors.tare();
  
  //wSensors.power_down();
}

void WaterBottle::calibrateBottleWeight(short knownBottleWeight)
{
  float waterBottleWeight = 0;
  //wSensors.power_up();
 
  while (round(waterBottleWeight) != knownBottleWeight)
  {
    // get average (weight - tare weight) and divide by scale factor (use raw values to get right number)
    waterBottleWeight = wSensors.get_units(10);

    wSensors.set_scale(waterBottleWeight / knownBottleWeight);
    Serial.print("\n"); // for testing, remove later
    Serial.print("Scale is: ");
    Serial.print(wSensors.get_scale());
    Serial.print("\n");
    Serial.print("Measured is: ");
    Serial.print(waterBottleWeight);
    Serial.print("\n");
  }

  wSensors.tare();
  
  //wSensors.power_down();
}

short WaterBottle::getWaterWeight()
{
  //wSensors.power_up();
  
  short measuredWaterWeight = round(wSensors.get_units(10));

  //wSensors.power_down();
  
  return measuredWaterWeight;
}
