// This file controls the functionality of the RGB light sensor
// The light sensor determines the color of the liquid in the clear water bottle 
// and returns whether or not the liquid is water or not.
// This file also has calibration settings that allow the sensor to calibrate to the
// color of the water bottle without any liquid in it.
//

#include "WaterBottle.h"
#include <Adafruit_TinyUSB.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// currently stores data in global var, when implemented will change so that app can
// send these values to the mcu instead.
uint16_t rBottle, gBottle, bBottle, cBottle;
double X = 15.0;

void setup() {
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("Found sensor");
    calibrate();
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

// method to calibrate base color reading for water bottle
// is called whenever user wants to calibrate the color of the water bottle
// stores the data in global variables
void calibrateColor() {
  tcs.getRawData(&rBottle, &gBottle, &bBottle, &cBottle);
}

// method returns 1 if liquid is water
// method returns 0 if liquid is not water
int isWater() { 
  // check color of liquid, if color is not clear return 0
  if (getColor() == 1) {
    return 0;
  }
  // else liquid is water
  return 1;
}

// method returns 1 if liquid if clear
// method returns 0 if liquid is not clear
int getColor() {
  // get current color
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // compare current color to water bottle rgb values
  // if any rgb value is >15% different, than liquid is not water
  double rDiff, gDiff, bDiff;
  rDiff = (double)rBottle - (double)r;
  rDiff = abs(rDiff);
  rDiff = rDiff / rBottle;
  
  gDiff = (double)gBottle - (double)g;
  gDiff = abs(gDiff);
  gDiff = gDiff / gBottle;
  
  bDiff = (double)bBottle - (double)b;
  bDiff = abs(bDiff);
  bDiff = bDiff / bBottle;
  
  // if rbg value is > certain percentage X,meaning the color is more than X% different.
  if (((rDiff * 100) > X) || ((gDiff * 100) > X) || ((bDiff * 100) > X)) {
    return 0;
  }
  return 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
