#include "config.h"

#include "wifi.h"
#include "ota.h"
#include "mdns.h"

#include <Wire.h>
#include "edid.h"

void setup() {
  Serial.begin(115200);
  Serial.print("Starting "); Serial.print(HOSTNAME); Serial.println("...");

  setupWiFi();
  setupOTA();
  setupMDNS();
  setupEDID();

  Serial.println();
  Serial.println("Started.");
}

void loop() {
  handleOTA();
}
