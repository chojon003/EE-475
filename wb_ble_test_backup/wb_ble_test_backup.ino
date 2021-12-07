// test file for the water bottle

#include "WaterBottle.h"
#include "System.h"
#include "BLEComms.h"
#include <Adafruit_TinyUSB.h>
#include <Wire.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
WaterBottle bottle;
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


int is_still(byte times);
unsigned int readRegister(byte reg);
void writeRegister(byte reg, byte data);
void init_ACC(void);

void setup() // User's First Time Setup with Device
{
  // Connect to App using BLE
  ble.connectToApp();

  // Wait for confirmation to calibrate 
  while (!ble.calibrateRequest());
  while (Serial.available() != 0) 
    Serial.readString();
  Serial.print("\n");
  
  // weight sensor setup
  bottle.tareWeightPlate();  

  // color sensor setup
  bottle.calibrateColor(5);
  Serial.print("Calibrate Color = ");
  Serial.print(bottle.isWater(5));
  Serial.print("\n\n");

  // accelerometer setup
  lis.begin(0x18);
  init_ACC();
  Wire.begin();
  int res = readRegister(0x0F); //WHO_AM_I
  Serial.println(res);
  pinMode(INTERRUPT_PIN, INPUT);

  // Sets up MCU for low power
  sys.setLowPower();
  
  delay(100);
}

void loop() 
{  
  if(!is_still(1)){ // moving
    reading_permission = 1;
    //Serial.println("Read Permission set to 1!");
    delay(500);
    
    if(!is_still(1)){ // If moving for a long time
      // enter sleep mode
      Serial.println("Enter sleep mode!");
      writeRegister(0x21, 0x09);
      while(analogRead(A0)*3.6/pow(2,8)>1.65){ // checks if device is still moving every 10 seconds
        readRegister(LIS3DH_REG_INT1SRC); //Read INT1_SRC to de-latch;
        delay(10000);
      }
      readRegister(LIS3DH_REG_INT1SRC);
      writeRegister(0x21, 0x00);
      //sleep mode ended
      Serial.println("Sleep mode ended!");
    }
  }else{ //not in motion
    // attempt to connect to App

    // catch for color calibration request
    if(ble.calibrateRequest()){ 
      // calibrate device again 
        bottle.calibrateColor(5);
        Serial.println("Recalibrated color success");
    }
    
    // Sends values to App only the first time not in motion
    if(reading_permission){
      // single object measuring
      Serial.print("\nEntered object weight: ");
      Serial.print(objWeight);
      raw = bottle.getWeight();
      Serial.print("\nMeasured object weight: ");
      Serial.print(raw);
      Serial.print("\n");
      water = bottle.isWater(5);
      Serial.print("Is water: ");
      Serial.print(water);
      Serial.print("\n");
      battery = sys.getBatteryPct();
      Serial.print("Battery: ");
      Serial.print(battery);
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
        acc_z += (event.acceleration.z - 10.2) / times;
    }

    if (abs(acc_x)<0.3 && abs(acc_y)<0.3 && abs(acc_z)<0.8)
        return 1;

    return 0;
}

unsigned int readRegister(byte reg)
{
    Wire.beginTransmission(0x18);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(0x18, 1);
    return Wire.read();
}

void writeRegister(byte reg, byte data)
{
    Wire.beginTransmission(0x18);
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
}
