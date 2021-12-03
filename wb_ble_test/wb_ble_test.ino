// test file for the water bottle

#include "WaterBottle.h"
#include "System.h"
#include "BLEComms.h"
#include <Adafruit_TinyUSB.h>
#include <Wire.h>

WaterBottle bottle(5, 6);
System sys;
BLEComms ble;

int INTERRUPT_PIN = A0;
int LIS3DH_ADDR = 0x18;
short containerWeight;
short objWeight;
long raw;
int water;
int battery;
int reading_permission = 1; // reading allowed when the bottle turns on


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
  ble.connectToApp();

  // weight sensor setup
  bottle.tareWeightPlate();
  
  Serial.print("Put object on plate and enter its weight: ");
  /*while (Serial.available() == 0);
  objWeight = Serial.parseInt();*/
  while (ble.calibrateRequest());
  objWeight = ble.getdata();
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
      battery = sys.getBatteryPct();
      Serial.print("Battery: ");
      Serial.print(baterry);
      Serial.print("\n");

      reading_permission = 0;
      //Serial.println("Read Permission set to 0!");
      
      // send the data to phone app
      Serial.println("send the data to phone app!\n");
      //BLE code - sending data to phone app
      ble.sendData(raw,water,battery);
      
      // sleep()
    }else{
      //delay(5000);
    }
  }
  // wait for a while
  delay(500);
}
