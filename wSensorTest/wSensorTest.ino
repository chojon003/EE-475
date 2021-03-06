// test file for weight sensor

#include "WaterBottle.h"
#include <Adafruit_TinyUSB.h>

WaterBottle bottle;
short objWeight;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    Serial.print("Waiting...\n");
    delay(500);
  }

  bottle.tareWeightPlate();
  
  Serial.print("Put object on plate and enter its weight: ");
  while (Serial.available() == 0);
  objWeight = Serial.parseInt();
  Serial.print(objWeight);
  
  while (Serial.available() != 0) 
    Serial.readString();
  Serial.print("\n\n");
}

void loop() 
{
  // single object measuring
  Serial.print("Entered object weight: ");
  Serial.print(objWeight);

  Serial.print("\nMeasured object weight: ");
  Serial.print(bottle.getWeight());

  Serial.print("\n\n");

  delay(100);
}
