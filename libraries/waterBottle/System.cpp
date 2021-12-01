#include "System.h"

System::System()
{
    ADCRefVoltage = 3.6; // default
    ADCResolution = 8; // 8 bits

    // configure ADC
    analogReadResolution(ADCResolution);

    // set low power
    //enableLFClock(1);
    //enableDCReg(1);
    //turnOffMemory();

    // initialize accelerometer
    lis = Adafruit_LIS3DH();
    lis.begin(0x18);
    //Wire.begin();
    //pinMode(INTERRUPT_PIN, INPUT);
    //lis.setRange(LIS3DH_RANGE_4_G);   // set range to 2, 4, 8 or 16 G!
    //lis.setDataRate(LIS3DH_DATARATE_400_HZ); //set data rate

}

int System::getBatteryPct()
{
    // get battery voltage, multiply by 2 is used to undo resistor divider effect
    float batteryVoltage = analogRead(BATTERY_PIN) * 2 * ADCRefVoltage / pow(2, ADCResolution);

    return constrain(round(batteryVoltage / 3.7 * 100), 0, 100);
}

void System::enableLFClock(byte en)
{
    if (en == 1) // enable ultra low power 32.768 kHz clock
    {
        LFCLKSRC = 0; // set LF clock source as RC oscillator
        LFRCMODE = 0x1; // set LFRC mode to ultra low power
        TASKS_LFCLKSTART = 0x1; // start LF clock

        while ((LFCLKSTAT & 0x10000) == 0); // wait for LF clock to start
    }
    else // disable
    {
        TASKS_LFCLKSTOP = 0x1; // stop LF clock

        while ((LFCLKSTAT & 0x10000) != 0); // wait for LF clock to stop
    }
}

void System::enableDCReg(byte en)
{
    // enable DC/DC regulator for microchip voltage supply
    if (en == 1)
        DCDCEN = 0x1;
    else
        DCDCEN = 0;
}
/*
// uses A0 pin on microcontroller board
void System::enterSystemOffMode()
{
    // set analog reset pin to be A0 of board (AIN2 of microcontroller)
    LPCOMPPSEL = 0x2;

    // select comparison voltage as VDD / 2 (1.15 V)
    LPCOMPREFSEL = 0x3;

    // enable hysteresis feature
    LPCOMPHYST = 0x1;

    // configure reset for voltage rising on reset pin
    ANALOGDETECT = 0x1;

    // start comparator and wait for completion
    LPCOMPEN = 0x1;
    TASKS_LPCOMPSTART = 0x1;
    while (EVENTS_LPCOMPREADY == 0);

    // enter system off mode
    SYSTEMOFF = 0x1;
}
*/
/*
void System::turnOffMemory()
{
    // turn off unused ram memory
    RAM4POWER = 0;
    RAM5POWER = 0;
    RAM6POWER = 0;
    RAM7POWER = 0;
    RAM8POWER = 0;
}
*/
int System::is_still(byte times){
  sensors_event_t event;

  double acc_x = 0;
  double acc_y = 0;
  double acc_z = 0;

  for (byte i = 0; i < times; i++)
  {
      lis.getEvent(&event);   // get a new accelerometer event
      // Display the results (acceleration is measured in m/s^2)
      acc_x += event.acceleration.x / times;
      acc_y += event.acceleration.y / times;
      acc_z += (event.acceleration.z - 10.2) / times;
  }
  Serial.print(acc_x);
  Serial.print("\t");
  Serial.print(acc_y);
  Serial.print("\t");
  Serial.println(acc_z);
  if (abs(acc_x)<0.3 && abs(acc_y)<0.3 && abs(acc_z)<0.8)
    return 1;

  return 0;
}

unsigned int System::readRegister(byte reg)
{
     Wire.beginTransmission(0x18);
     Wire.write(reg);
     Wire.endTransmission();
     Wire.requestFrom(0x18, 1);
     return Wire.read();
}

void System::writeRegister(byte reg, byte data)
{
     Wire.beginTransmission(0x18);
     Wire.write(reg);
     Wire.write(data);
     Wire.endTransmission();
}

void System::init_ACC(void)
{

   // configurations for control registers
   writeRegister(0x20, 0x57); //Write 57h into CTRL_REG1;      // Turn on the sensor, enable X, Y, Z axes with ODR = 100Hz normal mode.
   //writeRegister(0x21, 0x09); //Write 09h into CTRL_REG2;      // High-pass filter (HPF) enabled
   writeRegister(0x21, 0x00); //Write 00h into CTRL_REG2;      // High-pass filter (HPF) disabled
   writeRegister(0x22, 0x40); //Write 40h into CTRL_REG3;      // ACC AOI1 interrupt signal is routed to INT1 pin.
   writeRegister(0x23, 0x00); //Write 00h into CTRL_REG4;      // Full Scale = +/-2 g
   writeRegister(0x24, 0x08); //Write 08h into CTRL_REG5;      // Default value is 00 for no latching. Interrupt signals on INT1 pin is not latched.
                                                //Users don’t need to read the INT1_SRC register to clear the interrupt signal.
   // configurations for wakeup and motionless detection
   writeRegister(0x32, 0x10); //Write 10h into INT1_THS;          // Threshold (THS) = 16LSBs * 15.625mg/LSB = 250mg.
   writeRegister(0x33, 0x00); //Write 00h into INT1_DURATION;     // Duration = 1LSBs * (1/10Hz) = 0.1s.
   //readRegister();  //Dummy read to force the HP filter to set reference acceleration/tilt value
   writeRegister(0x30, 0x2A); //Write 2Ah into INT1_CFG;          // Enable XLIE, YLIE, ZLIE interrupt generation, OR logic.
   //writeRegister(0x30, 0x95); //free-fall recognition

}
