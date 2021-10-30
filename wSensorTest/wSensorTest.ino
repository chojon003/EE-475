// test file for load cell weight sensors

#include "WaterBottle.h"
#include <Adafruit_TinyUSB.h>

WaterBottle bottle(5, 6, 64);
short containerWeight;
short objWeight;

void setup()
{

  Serial.begin(9600);
  while (!Serial)
  {
    Serial.print("Waiting...\n");
    delay(500);
  }

  // suggested test routine
  bottle.wSensors.power_up();
  bottle.wSensors.read();
  bottle.wSensors.set_scale();
  bottle.wSensors.tare();

  Serial.print("\nPut object on plate and enter its weight: ");
  while (Serial.available() == 0);
  objWeight = Serial.parseInt();
  bottle.wSensors.set_scale(bottle.wSensors.get_units(10) / objWeight);
  while (Serial.available() != 0) 
    Serial.readString();

  // thorough test routine
  /*
  Serial.print("Weight plate on sensors? ");
  while (Serial.available() == 0);
  bottle.tareWeightPlate();
  while (Serial.available() != 0)
    Serial.readString();
    
  Serial.print("\nPut container on plate and enter its weight: ");
  while (Serial.available() == 0);
  containerWeight = Serial.parseInt();
  bottle.calibrateBottleWeight(containerWeight);
  while (Serial.available() != 0) 
    Serial.readString();

  Serial.print("\nPut object in/on container and enter its weight: ");
  while (Serial.available() == 0);
  objWeight = Serial.parseInt();
  while (Serial.available() != 0)
    Serial.readString();
  */
}

void loop() 
{
  Serial.print("Entered object weight: ");
  Serial.print(objWeight);

  Serial.print("\nMeasured object weight: ");
  Serial.print(bottle.wSensors.get_units(10));

  Serial.print("\n\n");

  delay(500);
  /*
  Serial.print("Entered object weight, container weight: ");
  Serial.print(objWeight);
  Serial.print(", ");
  Serial.print(containerWeight);

  Serial.print("\nMeasured object weight: ");
  Serial.print(bottle.getWaterWeight());

  Serial.print("\n\n");

  delay(500);
  */
}
