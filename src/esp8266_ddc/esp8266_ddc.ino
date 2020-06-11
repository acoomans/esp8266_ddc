#include "config.h"
#include "wifi.h"
#include "ota.h"
#include "mqtt.h"
#include "mdns.h"
#include "edid.h"
#include "ddc.h"

void setup() {
  Serial.begin(115200);
  Serial.print("Starting "); Serial.print(HOSTNAME); Serial.println("...");

  setupWiFi();
  setupOTA();
  setupMDNS();
  setupMQTT(MDNSquery());
  setupEDID();
  setupDDC();

  Serial.println();
  Serial.println("Started.");
}

void loop() {
  handleOTA();
  loopMQTT();
}
