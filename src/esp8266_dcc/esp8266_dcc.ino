#include <Wire.h>
#include "i2c.h"
#include "edid.h"

#define SDA_PIN 5
#define SCL_PIN 4

const int16_t I2C_SLAVE = 0x08;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  delay(1000);
  
  byte addresses[24];
  byte nDevices = scan_i2c(SDA_PIN, SCL_PIN, addresses, sizeof(addresses));
  for (int i=0; i < nDevices; i++) {
    delay(100);
    byte address = addresses[i];
    EDID e = EDID();
    e.requestFrom(address);
    if (e.isValid()) {
      Serial.print("Found EDID at 0x"); Serial.println(address, HEX);
      e.print();
    }
  }
  
  Serial.println("Started.");
}

void loop() {
}
