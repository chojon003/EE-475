// test file for load cell weight sensors

#include "WaterBottle.h"
#include <Adafruit_TinyUSB.h>

WaterBottle bottle(5, 6);
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

  Serial.print("Weight plate on sensors? ");
  while (Serial.available() == 0);
  bottle.tareWeightPlate();
  while (Serial.available() != 0)
    Serial.readString();
  /*
  Serial.print("\nPut container on plate and enter its weight: ");
  while (Serial.available() == 0);
  containerWeight = Serial.parseInt();
  bottle.calibrateBottleWeight(containerWeight);
  while (Serial.available() != 0)
    Serial.readString();
*/
  Serial.print("\nPut object in/on container and enter its weight: ");
  while (Serial.available() == 0);
  objWeight = Serial.parseInt();
  while (Serial.available() != 0)
    Serial.readString();

}

void loop() 
{
  Serial.print("Entered object weight, container weight: ");
  Serial.print(objWeight);
  Serial.print(", ");
  Serial.print(containerWeight);

  Serial.print("\nMeasured object weight: ");
  Serial.print(bottle.getWaterWeight());

  Serial.print("\n\n");

  delay(500);
}
