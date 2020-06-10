#include "mqtt.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "secrets.h"
#include "publish.h"
#include "subscribe.h"

WiFiClient client;

bool process_messages = false;

Adafruit_MQTT_Client mqtt(&client, MQTT_HOST, MQTT_PORT, MQTT_USER, MQTT_PASSWD);

Adafruit_MQTT_Publish brightness_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_BRIGHTNESS);
Adafruit_MQTT_Publish inputsource_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_INPUTSOURCE);
Adafruit_MQTT_Publish volume_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_VOLUME);
Adafruit_MQTT_Publish mute_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_PUB_MUTE);

Adafruit_MQTT_Subscribe brightness_sub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_SUB_BRIGHTNESS);
Adafruit_MQTT_Subscribe inputsource_sub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_SUB_INPUTSOURCE);
Adafruit_MQTT_Subscribe volume_sub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_SUB_VOLUME);
Adafruit_MQTT_Subscribe mute_sub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_SUB_MUTE);

void setupMQTT(String host_addr) {
  if (mqtt.connected()) {
    return;
  }

  mqtt = Adafruit_MQTT_Client(&client, host_addr.c_str(), MQTT_PORT, MQTT_USER, MQTT_PASSWD);

  Serial.print("Connecting to MQTT... ");

  brightness_sub.setCallback(brightness_callback);
  inputsource_sub.setCallback(input_source_callback);
  volume_sub.setCallback(volume_callback);
  mute_sub.setCallback(mute_callback);

  mqtt.subscribe(&brightness_sub);
  mqtt.subscribe(&inputsource_sub);
  mqtt.subscribe(&volume_sub);
  mqtt.subscribe(&mute_sub);

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

  process_messages = true;

  Serial.println("Connected to MQTT.");
}

long previousMillis = 0;

void loopMQTT() {
  mqtt.processPackets(20);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > MQTT_DELAY * 1000) {
    previousMillis = currentMillis;
    publishBrightness();
    publishInputSource();
    publishVolume();
    publishMute();
  }
}
