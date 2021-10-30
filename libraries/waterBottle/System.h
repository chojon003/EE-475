#include <Arduino.h>

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
  private:

    const byte BATTERY_PIN = A6;
    float ADCRefVoltage;
    byte ADCResolution;
    
    

  public:
    System(/* stuff like pins for sensors*/);

    bool batteryIsLow(float threshold);
};

#endif // SYSTEM_H
