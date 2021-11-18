// test file for measuring power consumption/current draw

#include "System.h"
#include <Adafruit_TinyUSB.h>

System powerTest;

void setup()
{
  // DC/DC reg option
  //powerTest.enableDCReg(1);

  // Sleep mode option
  //powerTest.enterSleepMode();

  // Reduced memory option
  //powerTest.turnOffMemory();

  // Low frequency clock enabled
  //powerTest.enableLFClock(1);
}

void loop() 
{
  // Using delay
  /*
  delay(2000);
  for (int i = 0; i < 10000; i++)
    analogRead(A0);
  */
}
