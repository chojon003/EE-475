// This file contains code for establishing BLE connection with 
// our app, as well as two way communication between this mcu and
// the app. Currently, this file is set up to send data to the app 
// using the Serial input, but in the future, this file will be able 
// to send important sensor values to the app.

#include "BLEComms.h"

BLEComms comm;

void setup()
{
  Serial.begin(115200);
  
  comm.connectToApp();
}

void loop()
{
  // Forward from Serial to BLEUART
  if (Serial.available())
  {
    // Delay to get enough input data since we have a
    // limited amount of space in the transmit buffer
    delay(2);

    uint8_t buf[64];
    int count = Serial.readBytes(buf, sizeof(buf));
    comm.sendData(buf, count);
  }

  // Forward from BLEUART to Serial (won't be used with .h file)
  if ( comm.bleuart.available() )
  {
    uint8_t ch;
    ch = comm.getData();
    Serial.write(ch);
  }
}
