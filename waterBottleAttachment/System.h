#include <Arduino.h>

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
  private:

  
    byte batteryOutputPin;
    float ADCRefVoltage;
    byte ADCResolution;
    
    

  public:
    System(/* stuff like pins for sensors*/);

    bool batteryIsLow(float threshold);
};

#endif // SYSTEM_H
