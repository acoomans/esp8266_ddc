#include <Arduino.h>
#include <Wire.h>

#include "i2c.h"


void println_i2c_address(byte address) {
  Serial.print("0x");
  if (address < 16) Serial.print("0");
  Serial.println(address, HEX);
}

void scan_pins_i2c() {
  Serial.println("Scan each SDA:SCL pin pair from D0 to D7 for I2C devices");
  uint8_t pins[] = {16, 5, 4, 0, 2, 14, 12, 13};
  for (uint8_t i = 0; i < sizeof(pins); i++) {
    for (uint8_t j = 0; j < sizeof(pins); j++) {
      byte sda = pins[i];
      byte scl = pins[j];
      if (sda != scl) {
        byte addresses[128];
        byte nDevices = scan_i2c(sda, scl, addresses, sizeof(addresses));
        if (nDevices) {
          Serial.print(nDevices); Serial.print(" I2C devices found on SDA=GPIO"); Serial.print(sda); Serial.print(":SCL=GPIO"); Serial.println(scl);
        }
        for (int k = 0; k < nDevices; k++) {
          Serial.print("address: "); println_i2c_address(addresses[k]);
        }
      }
    }
  }
}

byte scan_i2c(byte sda, byte scl, byte addresses[], byte len) {
  byte error = 0;
  byte nDevices = 0;
  
  Wire.begin(sda, scl);

  int last = 0;
  for (byte i = 1; i < 128; i++)  {
    Wire.beginTransmission(i);
    // check if transmission was acknowledged
    error = Wire.endTransmission(); 

    if (error == 0) {
      addresses[last++] = i;
      nDevices++;
      if (nDevices >= len) { break; }
    }
  }

  return nDevices;
}
