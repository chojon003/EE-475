// test file for the water bottle

#include "WaterBottle.h"
#include "System.h"
#include <Adafruit_TinyUSB.h>

// Acc
#include <Wire.h>
//#include <Adafruit_LIS3DH.h>
//#include <Adafruit_Sensor.h>
//Adafruit_LIS3DH lis = Adafruit_LIS3DH();
int INTERRUPT_PIN = A0;
int LIS3DH_ADDR = 0x18;


WaterBottle bottle(5, 6);
/*BLE initialization*/
System sys;
short containerWeight;
short objWeight;
long raw;
int water;
// Other variables
int reading_permission = 1; // reading allowed when the bottle turned on


void setup()
{
  // Serial setup
  Serial.begin(9600);
  while (!Serial)
  {
    Serial.print("Waiting...\n");
    delay(500);
  }

  // BLE setup
  /*BLE setup code*/

  // weight sensor setup
  bottle.tareWeightPlate();
  
  Serial.print("Put object on plate and enter its weight: ");
  while (Serial.available() == 0);
  objWeight = Serial.parseInt(); //replace with BLE func later
  Serial.print(objWeight);

  bottle.calibrateBottleWeight(objWeight);
  
  while (Serial.available() != 0) 
    Serial.readString();
  Serial.print("\n");

  // color sensor setup
  bottle.calibrateColor();
  Serial.print("Calibrate Color = ");
  Serial.print(bottle.isWater());
  Serial.print("\n\n");

  // accelerometer setup
  /*while(!lis.begin(LIS3DH_ADDR)) {
    Serial.println("Couldn't start");
  }
  Serial.println("LIS3DH found!");*/
  sys.init_ACC();
  Wire.begin();
  int res = sys.readRegister(0x0F); //WHO_AM_I
  Serial.println(res);
  pinMode(INTERRUPT_PIN, INPUT);
  //lis.setRange(LIS3DH_RANGE_2_G);   // set range to 2, 4, 8 or 16 G!
  //lis.setDataRate(LIS3DH_DATARATE_400_HZ);

  delay(100);
}

void loop() 
{  
  if(!sys.is_still(1)){ //is not still
    reading_permission = 1;
    //Serial.println("Read Permission set to 1!");
    delay(500);
    // sleep mode
    if(!sys.is_still(1)){
      // enter sleep mode
      Serial.println("Enter sleep mode!");
      sys.writeRegister(0x21, 0x09);
      while(analogRead(A0)*3.6/pow(2,8)>1.65){ 
        sys.readRegister(LIS3DH_REG_INT1SRC); //Read INT1_SRC to de-latch;
        delay(10000);
      }
      sys.readRegister(LIS3DH_REG_INT1SRC);
      sys.writeRegister(0x21, 0x00);
      //sleep mode ended
      Serial.println("Sleep mode ended!");
    }
  }else{ 
    if(reading_permission){
      // single object measuring
      Serial.print("\nEntered object weight: ");
      Serial.print(objWeight);
      raw = bottle.getWaterWeight();
      Serial.print("\nMeasured object weight: ");
      Serial.print(raw);
      Serial.print("\n");
      water = bottle.isWater();
      Serial.print("Is water: ");
      Serial.print(water);
      Serial.print("\n");

      reading_permission = 0;
      //Serial.println("Read Permission set to 0!");
      
      // send the data to phone app
      Serial.println("send the data to phone app!\n");
      /*BLE code - sending data to phone app*/
      // sleep()
    }else{
      //delay(5000);
    }
  }
  // wait for a while
  delay(500);
}

/*
// acc
int is_still(byte times){
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
      acc_z += (event.acceleration.z - 9.8) / times;
  }
  Serial.print(acc_x);
  Serial.print("\t");
  Serial.print(acc_y);
  Serial.print("\t");
  Serial.println(acc_z);
  if (abs(acc_x)<0.3 && abs(acc_y)<0.3 && abs(acc_z)<0.8){
    //Serial.println("The bottle is ready for measurement!");
    return 1;
  }
  return 0;
}


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
}*/
