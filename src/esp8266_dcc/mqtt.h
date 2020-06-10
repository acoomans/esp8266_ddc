#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define MQTT_INPUT_SOURCE_DP      "DP"
#define MQTT_INPUT_SOURCE_HDMI_1  "HDMI1"
#define MQTT_INPUT_SOURCE_HDMI_2  "HDMI2"

#define MQTT_MUTE_MUTED           "ON"
#define MQTT_MUTE_UNMUTED         "OFF"

extern bool process_messages;

extern Adafruit_MQTT_Publish brightness_pub;
extern Adafruit_MQTT_Publish inputsource_pub;
extern Adafruit_MQTT_Publish volume_pub;
extern Adafruit_MQTT_Publish mute_pub;

extern Adafruit_MQTT_Subscribe brightness_sub;
extern Adafruit_MQTT_Subscribe inputsource_sub;
extern Adafruit_MQTT_Subscribe volume_sub;
extern Adafruit_MQTT_Subscribe mute_sub;

void setupMQTT(String host_addr);
void loopMQTT();
