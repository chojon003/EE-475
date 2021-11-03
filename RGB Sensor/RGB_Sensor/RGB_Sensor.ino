// This file controls the functionality of the RGB light sensor
// The light sensor determines the color of the liquid in the clear water bottle 
// and returns whether or not the liquid is water or not.
// This file also has calibration settings that allow the sensor to calibrate to the
// color of the water bottle without any liquid in it.
//


#include <Wire.h>
#include "Adafruit_TCS34725.h"

void setup() {
  // put your setup code here, to run once:

}

// method to calibrate base color reading for water bottle
void calibrate() {
  
}

// method returns 1 if liquid is water
// method returns 0 if liquid is not water
int isWater() { 
  // get color of liquid

  // if color is not clear return 0
  if (getColor() == 1) {
    return 0;
  }
  // else liquid is water
  return 1;
}

void loop() {
  // put your main code here, to run repeatedly:

}
