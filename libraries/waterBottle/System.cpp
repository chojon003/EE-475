#include "System.h"

System::System()
{

    //ADCRefVoltage = AR_INTERNAL; // 3.6 V, just able to do 3.6?
    //ADCRefVoltage = AR_INTERNAL_3_0; neither working, not sure why
    ADCResolution = 8; // 8 bits


    // configure ADC
    //analogReference(ADCRefVoltage);
    analogReadResolution(ADCResolution);


}

// will this work if battery voltage > ADCRefVoltage?
bool System::batteryIsLow(float threshold)
{
    // get battery voltage, multiply by 2 is used to undo resistor divider effect
    float batteryVoltage = analogRead(BATTERY_PIN) * 2 * ADCRefVoltage / pow(2, ADCResolution);

    return batteryVoltage < threshold;
}

// notes:
// - a 32.768 external clock is supplied
// - low frequency clk can be calibrated with high frequency clock
void System::setClockSpeed(int speed)
{
    if (speed == 32) // enable ultra low power 32 kHz clock
    {
        // stop higher frequency clocks?

        LFCLKSRC = 0; // set LF clock source as RC oscillator
        LFRCMODE = 0x1; // set LFRC mode to ultra low power
        TASKS_LFCLKSTART = 0x1; // start LF clock

        while (LFCLKSTAT &= 0x10000 != 0); // wait for LF clock to start
    }
    else if (speed == 1) // enable 1 MHz clock
    {

    }
    else // enable 64 MHz clock
    {

    }
}

void System::enableLFClock(short en)
{
    if (en == 1) // enable ultra low power 32.768 kHz clock
    {
        LFCLKSRC = 0; // set LF clock source as RC oscillator
        LFRCMODE = 0x1; // set LFRC mode to ultra low power
        TASKS_LFCLKSTART = 0x1; // start LF clock

        while (LFCLKSTAT &= 0x10000 == 0); // wait for LF clock to start
    }
    else // disable
    {
        TASKS_LFCLKSTOP = 0x1; // stop LF clock

        while (LFCLKSTAT &= 0x10000 != 0); // wait for LF clock to stop
    }
}

void System::enableDCReg(short en)
{
    // enable DC/DC regulator for microchip voltage supply
    if (en == 1)
        DCDCEN = 0x1;
    else
        DCDCEN = 0;
}

void System::enterSleepMode()
{
    SYSTEMOFF = 0x1; // toggle microcontroller system off mode
}
