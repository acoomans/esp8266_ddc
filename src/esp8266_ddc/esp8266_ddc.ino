#include "config.h"
#include "wifi.h"
#include "ota.h"
#include "mqtt.h"
#include "mdns.h"
#include "edid.h"
#include "ddc.h"
#include "button.h"

void setup() {
  Serial.begin(115200);
  Serial.print("Starting "); Serial.print(HOSTNAME); Serial.println("...");

  setupWiFi();
  setupOTA();
  setupMDNS();
  setupMQTT(MDNSquery());
  setupEDID();
  setupDDC();
  setupButton();

  Serial.println();
  Serial.println("Started.");
}

void loop() {
  handleOTA();
  loopMQTT();
  loopButton();
}
