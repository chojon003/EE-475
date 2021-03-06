#include "WaterBottle.h"

WaterBottle::WaterBottle()
{
    // initialize weight sensor
    wSensor.begin(HX711_DOUT_PIN, HX711_CLK_PIN, HX711_GAIN);
    wSensor.power_up();
    wSensor.read();
    wSensor.set_scale(W_SENSOR_SCALE);
    wSensor.power_down();

    // initialize color sensor and related variables
    colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
    rBottle = 0;
    gBottle = 0;
    bBottle = 0;
    cBottle = 0;
    X = 25.0;
}

void WaterBottle::tareWeightPlate()
{
    wSensor.power_up();

    wSensor.tare();

    wSensor.power_down();
}

short WaterBottle::getWeight()
{
    short measuredWeight = 0;

    wSensor.power_up();

    measuredWeight = round(wSensor.get_units(10));

    wSensor.power_down();

    return measuredWeight;
}

void WaterBottle::calibrateColor(byte times)
{
    // calibrate the color of the water bottle using averaged readings
    uint16_t color[4];

    rBottle = 0;
    gBottle = 0;
    bBottle = 0;
    cBottle = 0;

    for (byte i = 0; i < times; i++)
    {
        colorSensor.getRawData(&color[0], &color[1], &color[2], &color[3]);

        rBottle += round(color[0] / (float) times);
        gBottle += round(color[1] / (float) times);
        bBottle += round(color[2] / (float) times);
        cBottle += round(color[3] / (float) times);
    }
}

int WaterBottle::isWater(byte times)
{
    // get current color, averaged
    uint16_t color[4];
    uint16_t r = 0;
    uint16_t g = 0;
    uint16_t b = 0;
    uint16_t c = 0;

    for (byte i = 0; i < times; i++)
    {
        colorSensor.getRawData(&color[0], &color[1], &color[2], &color[3]);

        r += round(color[0] / (float) times);
        g += round(color[1] / (float) times);
        b += round(color[2] / (float) times);
        c += round(color[3] / (float) times);
    }

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
