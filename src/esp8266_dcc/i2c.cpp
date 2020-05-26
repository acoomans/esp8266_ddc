#include <Arduino.h>
#include <Wire.h>

#include "i2c.h"

void scan_pins_i2c() {
  Serial.println("Scan each SDA:SCL pin pair from D0 to D7 for I2C devices");
  uint8_t pins[] = {16, 5, 4, 0, 2, 14, 12, 13};
  for (uint8_t i = 0; i < sizeof(pins); i++) {
    for (uint8_t j = 0; j < sizeof(pins); j++) {
      if (i != j){
        scan_i2c(pins[i], pins[j]);
      }
    }
  }
}

void println_i2c_address(byte address) {
  Serial.print("0x");
  if (address < 16) Serial.print("0");
  Serial.println(address, HEX);
}

void scan_i2c(byte sda, byte scl) {
  bool headerPrinted = false;
  byte error = 0;
  int nDevices = 0;
  
  Wire.begin(sda, scl);

  for (byte address = 1; address < 128; address++ )  {
    Wire.beginTransmission(address);
    // check if transmission was acknowledged
    error = Wire.endTransmission(); 

    if (error == 0) {
      if (!headerPrinted) {
        Serial.print("I2C devices on SDA=GPIO");
        Serial.print(sda);
        Serial.print(":SCL=GPIO");
        Serial.print(scl);
        Serial.println(" pin pair:");
        headerPrinted = true;
      }
      Serial.print("address: ");
      println_i2c_address(address);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      println_i2c_address(address);
    }
  }
  
  if (nDevices > 0) {
    Serial.print("I2C devices found: ");
    Serial.println(nDevices);
  }
}
