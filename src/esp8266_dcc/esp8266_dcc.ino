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

//  dcc_write(INPUT_SOURCE, INPUT_SOURCE_HDMI_1);
//  dcc_write(INPUT_SOURCE, INPUT_SOURCE_HDMI_2);
  dcc_write(INPUT_SOURCE, INPUT_SOURCE_DP);

  Serial.println();
  Serial.println("Started.");
}

void loop() {
//  handleOTA();
  
//  dcc_value val = ddc_read(INPUT_SOURCE);
//  if (!INVALID_READ(val)) {
//    Serial.print("Brightness: "); Serial.print(val.current, HEX); Serial.print("/"); Serial.println(val.max, HEX);
//  }
  
  delay(500);
}
