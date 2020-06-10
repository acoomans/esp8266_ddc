#include "config.h"

#include "wifi.h"
#include "ota.h"
#include "mqtt.h"
#include "publish.h"
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

//  dcc_write(INPUT_SOURCE, INPUT_SOURCE_HDMI_1);
//  dcc_write(INPUT_SOURCE, INPUT_SOURCE_HDMI_2);
//  dcc_write(INPUT_SOURCE, INPUT_SOURCE_DP);

  Serial.println();
  Serial.println("Started.");
}

void loop() {
  handleOTA();
  publishBrightness();
  publishInputSource();
  publishVolume();
  publishMute();
  delay(MQTT_DELAY * 1000);
}
