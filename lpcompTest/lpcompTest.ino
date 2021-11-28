// test file for getting the microcontroller out of system off mode with the microcontroller's lpcomp module
// assumes adc ref voltage is 3.6v (default), bits of resolution = 8
/*
#include "System.h"
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TinyUSB.h>

System test;
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

int INTERRUPT_PIN = A0;
int LIS3DH_ADDR = 0x18;

unsigned int readRegister(byte reg)
{
   Wire.beginTransmission(LIS3DH_ADDR);
   Wire.write(reg);
   Wire.endTransmission();
   Wire.requestFrom(LIS3DH_ADDR, 1);
   return Wire.read();
}

void setup()
{
  Serial.begin(9600);
  
  while (!Serial)
  {
    Serial.print("Waiting...\n");
    delay(500);
  }

  Serial.print("Just began, or out of sleep mode!\n");
  
  delay(1000);

  if (!lis.begin(0x18)) 
  {
    Serial.println("Couldnt start");
    while (1) yield();
  }
  
  lis.setRange(LIS3DH_RANGE_2_G);

  // 0 = turn off click detection & interrupt
  // 1 = single click only interrupt output
  // 2 = double click only interrupt output, detect single click
  // Adjust threshhold, higher numbers are less sensitive
  lis.setClick(1, 80);
  
  delay(100);
  
  //test.enterSleepMode();
}

void loop() 
{
  // print acc
  float voltage = analogRead(INTERRUPT_PIN) * 3.6 / pow(2, 8);
  sensors_event_t event;
  lis.getEvent(&event);
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y);
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
  Serial.print(" m/s^2 ");
  Serial.print(" intPin read: ");Serial.print(voltage);Serial.print("\t");
  
  
  //lis.read();      // get X Y and Z data at once
  //Serial.println(INT_COUNT);
  //Serial.print(digitalRead(INTERRUPT_PIN));
  delay(200);
  //this works:
  if(voltage > 1.5) {
    //Serial.print("  \tinterrupt: ");
    //Serial.print(INT_COUNT++); Serial.print(",  ");
  readRegister(0x21); Serial.print(",  "); //read register to reset high-pass filter
  readRegister(0x26); Serial.print(",  "); //read register to set reference acceleration
  readRegister(LIS3DH_REG_INT1SRC);//Read INT1_SRC to de-latch;
  }
  //Serial.println();
  delay(1000);
}
*/

#include "System.h"
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

System test;
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

int INTERRUPT_PIN = A0;
int LIS3DH_ADDR = 0x18;

unsigned int readRegister(byte reg)
{
   Wire.beginTransmission(LIS3DH_ADDR);
   Wire.write(reg);
   Wire.endTransmission();
   Wire.requestFrom(LIS3DH_ADDR, 1);
   return Wire.read();
}

void writeRegister(byte reg, byte data)
{
   Wire.beginTransmission(LIS3DH_ADDR);
   Wire.write(reg);
   Wire.write(data);
   Wire.endTransmission();
}

void init_ACC(void)
{
   // configurations for control registers
   writeRegister(0x20, 0x57); //Write 57h into CTRL_REG1;      // Turn on the sensor, enable X, Y, Z axes with ODR = 100Hz normal mode.
   writeRegister(0x21, 0x09); //Write 09h into CTRL_REG2;      // High-pass filter (HPF) enabled
   writeRegister(0x22, 0x40); //Write 40h into CTRL_REG3;      // ACC AOI1 interrupt signal is routed to INT1 pin.
   writeRegister(0x23, 0x00); //Write 00h into CTRL_REG4;      // Full Scale = +/-2 g
   writeRegister(0x24, 0x08); //Write 08h into CTRL_REG5;      // Default value is 00 for no latching. Interrupt signals on INT1 pin is not latched.
                                                //Users don’t need to read the INT1_SRC register to clear the interrupt signal.
   
   // configurations for wakeup and motionless detection
   writeRegister(0x32, 0x10); //Write 10h into INT1_THS;          // Threshold (THS) = 16LSBs * 15.625mg/LSB = 250mg.
   writeRegister(0x33, 0x00); //Write 00h into INT1_DURATION;     // Duration = 1LSBs * (1/10Hz) = 0.1s.
   //readRegister();  //Dummy read to force the HP filter to set reference acceleration/tilt value
   writeRegister(0x30, 0x2A); //Write 2Ah into INT1_CFG;          // Enable XLIE, YLIE, ZLIE interrupt generation, OR logic.

}

void setup(void) 
{
  //Serial.begin(9600);
  
  //while (!Serial)
  //{
  //  Serial.print("Waiting...\n");
  //  delay(500);
  //}
  
  lis.begin(LIS3DH_ADDR);
  
  Wire.begin();
  init_ACC();
 
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!

  float voltage = analogRead(INTERRUPT_PIN) * 3.6 / pow(2, 8);
  
  Serial.print(" intPin read: "); Serial.print(voltage); Serial.print("\n");
  readRegister(LIS3DH_REG_INT1SRC); //Read INT1_SRC to de-latch;

  Serial.print("Just began, or out of system off mode! Entering system off mode...\n");
  
  delay(5000);

  test.enterSystemOffMode();
  
}

void loop() 
{
  //float voltage = analogRead(INTERRUPT_PIN) * 3.6 / pow(2, 8);
  
  //Serial.print(" intPin read: "); Serial.print(voltage); Serial.print("\n");
  //readRegister(LIS3DH_REG_INT1SRC); //Read INT1_SRC to de-latch;
  
  //delay(1000);
  //readRegister(LIS3DH_REG_INT1SRC);//Read INT1_SRC to de-latch;
}
