#include "System.h"

System::System()
{
  batteryOutputPin = A6;
  //ADCRefVoltage = AR_INTERNAL; // 3.6 V, just able to do 3.6?
  ADCRefVoltage = 3.6;
  ADCResolution = 8; // 8 bits

  
  // configure ADC 
  analogReference(ADCRefVoltage);
  analogReadResolution(ADCResolution);

  
}

bool System::batteryIsLow(float threshold)
{
  // get battery voltage, multiply by 2 is used to undo resistor divider effect
  batteryVoltage = analogRead(batteryOutputPin) * 2 * ADCRefVoltage / pow(2, ADCResolution)

  return true
}
