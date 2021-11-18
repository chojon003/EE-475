#include "System.h"

System::System()
{
    ADCRefVoltage = 3.6; // default
    ADCResolution = 8; // 8 bits


    // configure ADC
    analogReadResolution(ADCResolution);


}

// will this work if battery voltage > ADCRefVoltage?
float System::getBatteryVoltage()
{
    // get battery voltage, multiply by 2 is used to undo resistor divider effect
    float batteryVoltage = analogRead(BATTERY_PIN) * 2 * ADCRefVoltage / pow(2, ADCResolution);

    return batteryVoltage;
}

void System::enableLFClock(short en)
{
    if (en == 1) // enable ultra low power 32.768 kHz clock
    {
        LFCLKSRC = 0; // set LF clock source as RC oscillator
        LFRCMODE = 0x1; // set LFRC mode to ultra low power
        TASKS_LFCLKSTART = 0x1; // start LF clock
	
        while ((LFCLKSTAT & 0x10000) == 0); // wait for LF clock to start
    }
    else // disable
    {
        TASKS_LFCLKSTOP = 0x1; // stop LF clock

        while ((LFCLKSTAT & 0x10000) != 0); // wait for LF clock to stop
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

// uses A0 pin on microcontroller board
void System::enterSleepMode()
{
    // set analog wake up pin to be A0 of board (AIN2 of microcontroller)
    LPCOMPPSEL = 0x2;

    // select comparison voltage as VDD / 2 (1.15 V)
    LPCOMPREFSEL = 0x3;

    // enable hysteresis feature
    LPCOMPHYST = 0x1;

    // configure wake up for voltage rising on wake up pin
    ANALOGDETECT = 0x1;

    // start comparator and wait for completion
    LPCOMPEN = 0x1;
    TASKS_LPCOMPSTART = 0x1;
    while (EVENTS_LPCOMPREADY == 0);

    // enter sleep mode
    SYSTEMOFF = 0x1;
}

void System::turnOffMemory()
{
    // turn off unused ram memory
    RAM4POWER = 0;
    RAM5POWER = 0;
    RAM6POWER = 0;
    RAM7POWER = 0;
    RAM8POWER = 0;
}
