#include "config.h"

#include "wifi.h"
#include "ota.h"
#include "mdns.h"

#include <Wire.h>
#include "i2c.h"
#include "edid.h"


#define SDA_PIN 5
#define SCL_PIN 4

const int16_t I2C_SLAVE = 0x08;

void setup() {
  Serial.begin(115200);
  Serial.print("Starting "); Serial.print(HOSTNAME); Serial.println("...");

  setupWiFi();
  setupOTA();
  setupMDNS();

  delay(1000);
  
  byte addresses[24];
  byte nDevices = scan_i2c(SDA_PIN, SCL_PIN, addresses, sizeof(addresses));
  for (int i=0; i < nDevices; i++) {
    delay(100);
    byte address = addresses[i];
    Serial.print("Scanning 0x"); Serial.print(address, HEX);
    
    EDID e = EDID();
    e.requestFrom(address);
    if (e.isValid()) {
      Serial.println(" Found EDID");
      e.print();
    } else {
      Serial.println();
    }
  }
  
  Serial.println("Started.");
}

void loop() {
  handleOTA();
}
