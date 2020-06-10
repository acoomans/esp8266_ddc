#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

extern Adafruit_MQTT_Publish brightness_pub;
extern Adafruit_MQTT_Publish inputsource_pub;
extern Adafruit_MQTT_Publish volume_pub;
extern Adafruit_MQTT_Publish mute_pub;

void setupMQTT(String host_addr);
