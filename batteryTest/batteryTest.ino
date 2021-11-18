// test file for reading lipo battery voltage

#include "System.h"
#include <Adafruit_TinyUSB.h>

System test;

void setup()
{
  Serial.begin(9600);
  
  while (!Serial)
  {
    Serial.print("Waiting...\n");
    delay(500);
  }
}

void loop() 
{
  Serial.print("Battery voltage: ");
  Serial.print(test.getBatteryVoltage());
  Serial.print("\n");
  
  delay(500);
}
