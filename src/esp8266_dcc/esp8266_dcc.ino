#include "config.h"

#include "wifi.h"
#include "ota.h"
#include "mdns.h"
#include "edid.h"
#include "ddc.h"

void setup() {
  Serial.begin(115200);
  Serial.print("Starting "); Serial.print(HOSTNAME); Serial.println("...");

//  setupWiFi();
//  setupOTA();
//  setupMDNS();
//  setupEDID();
  setupDDC();

  Serial.println();
  Serial.println("Started.");
}

void loop() {
//  handleOTA();

  delay(1000);
  float val = ddc_read(BRIGHTNESS);
  if (val != INVALID_READ) {
    Serial.print("Brightness: "); Serial.println(val);
  }
}
