#include "WaterBottle.h"

WaterBottle::WaterBottle(byte HX711CLK, byte HX711Dout)
{
    // initialize weight sensor
    wSensor.begin(HX711Dout, HX711CLK, 64);
    wSensor.power_up();
    wSensor.read();
    wSensor.power_down();

    // initialize color sensor
    colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
    X = 25.0;

    // initialize accelerometer
    Adafruit_LIS3DH lis = Adafruit_LIS3DH();
    lis.begin(0x19);
    lis.setRange(LIS3DH_RANGE_4_G);   // set range to 2, 4, 8 or 16 G!
    lis.setDataRate(LIS3DH_DATARATE_400_HZ); //set data rate
}

void WaterBottle::tareWeightPlate()
{
    wSensor.power_up();

    wSensor.tare();

    wSensor.power_down();
}

void WaterBottle::calibrateBottleWeight(short knownBottleWeight)
{
    wSensor.power_up();

    wSensor.set_scale(wSensor.get_units(10) / knownBottleWeight);

    wSensor.tare();

    wSensor.power_down();
}

short WaterBottle::getWaterWeight()
{
    short measuredWaterWeight = 0;

    wSensor.power_up();

    measuredWaterWeight = round(wSensor.get_units(10));

    wSensor.power_down();

    return measuredWaterWeight;
}

void WaterBottle::calibrateColor()
{
    colorSensor.getRawData(&rBottle, &gBottle, &bBottle, &cBottle);
}

int WaterBottle::isWater()
{
    // get current color
    uint16_t r, g, b, c;
    colorSensor.getRawData(&r, &g, &b, &c);

    // compare current color to water bottle rgb values
    // if any rgb value is >X% different, than liquid is not water
    float rDiff, gDiff, bDiff;
    rDiff = (float)rBottle - (float)r;
    rDiff = abs(rDiff);
    rDiff = rDiff / rBottle;

    gDiff = (float)gBottle - (float)g;
    gDiff = abs(gDiff);
    gDiff = gDiff / gBottle;

    bDiff = (float)bBottle - (float)b;
    bDiff = abs(bDiff);
    bDiff = bDiff / bBottle;

    // if rbg value is > certain percentage X,meaning the color is more than X% different.
    if (((rDiff * 100) > X) || ((gDiff * 100) > X) || ((bDiff * 100) > X))
        return 0;
    else
        return 1;
}


int WaterBottle::is_still(){
  sensors_event_t event;
  lis.getEvent(&event);   // get a new accelerometer event
  // Display the results (acceleration is measured in m/s^2)
  double acc_x = event.acceleration.x;
  double acc_y = event.acceleration.y;
  double acc_z = event.acceleration.z+9.8;
  if (a+b+c<1.5 && c>-0.5){
    Serial.println("The bottle is ready for measurement!");
    return 1;
  }
  return 0;
}
