#include "System.h"

System::System()
{
  
  //ADCRefVoltage = AR_INTERNAL; // 3.6 V, just able to do 3.6?
  //ADCRefVoltage = AR_INTERNAL_3_0; neither working, not sure why
  ADCResolution = 8; // 8 bits

  
  // configure ADC 
  //analogReference(ADCRefVoltage);
  analogReadResolution(ADCResolution);

  
}

// will this work if battery voltage > ADCRefVoltage?
bool System::batteryIsLow(float threshold)
{
  // get battery voltage, multiply by 2 is used to undo resistor divider effect
  float batteryVoltage = analogRead(BATTERY_PIN) * 2 * ADCRefVoltage / pow(2, ADCResolution);

  return batteryVoltage < threshold;
}
