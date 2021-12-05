// This file contains code for establishing BLE connection with
// our app, as well as two way communication between this mcu and
// the app. Currently, this file is set up to send data to the app
// using the Serial input, but in the future, this file will be able
// to send important sensor values to the app.

#include <bluefruit.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

// BLE Service
BLEDfu  bledfu;  // OTA DFU service
BLEDis  bledis;  // device information
BLEUart bleuart; // uart over ble
BLEBas  blebas;  // battery
int count = 0;
void setup()
{
  Serial.begin(115200);
  connectToApp();
}

void loop()
{
//  delay(1000);
//  count++;
//  bleuart.write("HELLO");
  // Forward from Serial to BLEUART
  if (Serial.available())
  {
    // Delay to get enough input data since we have a
    // limited amount of space in the transmit buffer
    delay(2);

    uint8_t buf[64];
    int count = Serial.readBytes(buf, sizeof(buf));
    bleuart.write(buf, count);
    bleuart.flush();
    
    //    sendData(buf, count);
  }

  // Forward from BLEUART to Serial
  if ( bleuart.available() )
  {
    uint8_t ch;
    ch = getData();
    Serial.write(ch);
  }
}

// Sets up microcontroller to be used as peripheral for BLE communication
void connectToApp() {
  // Config the peripheral connection with maximum bandwidth
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

  Bluefruit.begin();
  //  Bluefruit.autoConnLed(0);
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // To be consistent OTA DFU should be added first if it exists
  bledfu.begin();

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("DrinkingBuddy");
  bledis.begin();

  // Configure and Start BLE Uart Service
  bleuart.begin();
  Serial.println(bleuart.notifyEnabled());

  // Start BLE Battery Service
  blebas.begin();
  blebas.write(100);

  // Set up Advertising Packet
  setupAdv();

  /* Start Advertising
     - Enable auto advertising if disconnected
     - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
     - Timeout for fast mode is 30 seconds
     - Start(timeout) with timeout = 0 will advertise forever (until connected)
  */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

// Sets up necessary flags for advertising to begin
void setupAdv(void) {
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  // Include bleuart 128-bit uuid
  Bluefruit.Advertising.addService(bleuart);

  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();
}

// Sends data to app
void sendData(uint8_t data, int count) {
  //  bleuart.write(data, count);
}

// Returns data from app
uint8_t getData() {
  return ((uint8_t)bleuart.read());
}

// callback invoked when central connects
void connect_callback(uint16_t conn_handle)
{
  // Get the reference to current connection
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char central_name[32] = { 0 };
  connection->getPeerName(central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);
}

/**
   Callback invoked when a connection is dropped
   @param conn_handle connection where this event happens
   @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
*/
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.println();
  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}
