#include "wifi.h"

#include "secrets.h"

#include <ESP8266WiFi.h>

void setupWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.println("Connecting to WiFi...");
  WiFi.begin(WLAN_SSID, WLAN_PASSWD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Serial.println("Connected to WiFi.");
}
