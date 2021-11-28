// test file for the water bottle

#include "WaterBottle.h"
//#include "System.h"
#include <Adafruit_TinyUSB.h>

// Acc
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
int INTERRUPT_PIN = A0;
int LIS3DH_ADDR = 0x18;


WaterBottle bottle(5, 6);
/*BLE initialization*/
//System sys;
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
  objWeight = Serial.parseInt();
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
  if (! lis.begin(0x18)) {
    Serial.println("Couldn't start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
  lis.setRange(LIS3DH_RANGE_4_G);   // set range to 2, 4, 8 or 16 G!
  lis.setDataRate(LIS3DH_DATARATE_400_HZ);
  //init_ACC();
  //Wire.begin();
  //int res = readRegister(0x0F); //WHO_AM_I
  //Serial.println(res);
  //pinMode(INTERRUPT_PIN, INPUT); 

  delay(100);
}

void loop() 
{
  //test interupt
  //float voltage = analogRead(A0) * 3.6 / pow(2, 8);
  //Serial.print(" intPin read: "); Serial.print(voltage); Serial.print("\n");
  
  if(!is_still()){ //is not still
    reading_permission = 1;
    //Serial.println("Read Permission set to 1!");
    delay(500);
    // sleep mode
    /*
    if(!is_still()){
      // enter sleep mode
      while(analogread(INTERRUPT_PIN)>threshold/*is high*/){
        delay(500);
      }
      // sleep mode ended
    }
    */
  }else{ // is still)
    if(reading_permission){
      // enable sensors
      // fetch the reading from weight sensor
      // single object measuring
      Serial.print("Entered object weight: ");
      Serial.print(objWeight);
      raw = bottle.getWaterWeight();
      Serial.print("\nMeasured object weight: ");
      Serial.print(raw);
      Serial.print("\n");
      water = bottle.isWater(); //return 1 if it's water and 0 if not 
      Serial.print("Is water: ");
      Serial.print(water);
      Serial.print("\n");

      reading_permission = 0;
      //Serial.println("Read Permission set to 0!");
      
      Serial.print("\n");
      // send the data to phone app
      /*BLE code - sending data to phone app*/
      // sleep()
    }else{
      //delay(5000);
    }
  }
  // wait for a while
  delay(500);



  /*
  // others
  while(//function for bluetooth connection){ 
    Serial.println("Waiting for bluetooth connection");
  }
  */

  
  /*
  while(interrupt_pin){ // break when intrrupt_pin is 0 (device is still)
    delay(1000);
  } 
  if(reading_permission){
      // fetch the reading from weight sensor
      water = getColor(); //return 1 if it's water and 0 if not
      reading_permission = 0;
      // try to send the data to phone app
    }
  */
}


// acc
int is_still(){
  sensors_event_t event;
  lis.getEvent(&event);
  // Display the results (acceleration is measured in m/s^2)
  double acc_x = event.acceleration.x;
  double acc_y = event.acceleration.y;
  double acc_z = event.acceleration.z-9.8;
  /*Serial.print(acc_x);
  Serial.print("\t");
  Serial.print(acc_y);
  Serial.print("\t");
  Serial.println(acc_z);*/
  if (abs(acc_x)<0.25 && abs(acc_y)<0.25 && abs(acc_z)<0.8){
    //Serial.println("The bottle is ready for measurement!");
    return 1;
  }
  return 0;
}
/*
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

}*/
