#include "mqtt.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "secrets.h"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, MQTT_HOST, MQTT_PORT, MQTT_USER, MQTT_PASSWD);

Adafruit_MQTT_Publish brightness_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_BRIGHTNESS);
Adafruit_MQTT_Publish inputsource_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_INPUTSOURCE);
Adafruit_MQTT_Publish volume_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_VOLUME);
Adafruit_MQTT_Publish mute_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_MUTE);

void setupMQTT(String host_addr) {
  if (mqtt.connected()) {
    return;
  }

  mqtt = Adafruit_MQTT_Client(&client, host_addr.c_str(), MQTT_PORT, MQTT_USER, MQTT_PASSWD);

  Serial.print("Connecting to MQTT... ");

  int8_t ret;
  uint8_t retries = 5;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Error connecting to MQTT; retrying");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
    }
  }

  brightness_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_BRIGHTNESS);
  inputsource_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_INPUTSOURCE);
  volume_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_VOLUME);
  mute_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_MUTE);
  
  Serial.println("Connected to MQTT.");
}
