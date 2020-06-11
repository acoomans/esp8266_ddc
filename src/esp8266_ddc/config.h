#define HOSTNAME                "ddc01"

#define OTA_PORT                8266
#define OTA_HOSTNAME            HOSTNAME

#define MDNS_HOSTNAME           HOSTNAME

#define MDNS_QUERY_SERVICE      "openhab-server"
#define MDNS_QUERY_PROTOCOL     "tcp"

#define MQTT_HOST               ""
#define MQTT_PORT               8883

#define MQTT_PUB_BRIGHTNESS     "openHAB/in/Screen01_Brightness/state"
#define MQTT_PUB_INPUTSOURCE    "openHAB/in/Screen01_InputSource/state"
#define MQTT_PUB_VOLUME         "openHAB/in/Screen01_Volume/state"
#define MQTT_PUB_MUTE           "openHAB/in/Screen01_Mute/state"

#define MQTT_SUB_BRIGHTNESS     "openHAB/out/Screen01_Brightness/command"
#define MQTT_SUB_INPUTSOURCE    "openHAB/out/Screen01_InputSource/command"
#define MQTT_SUB_VOLUME         "openHAB/out/Screen01_Volume/command"
#define MQTT_SUB_MUTE           "openHAB/out/Screen01_Mute/command"


#define MQTT_DELAY              300

#define SDA_PIN                 5
#define SCL_PIN                 4

#define I2C_EDID                0x50
#define I2C_DDC                 0x37

#define DDC_RETRY               3

#define BUTTON_PIN              2 // D4 / GPIO2
#define LED_PIN                 0 // D3 / GPIO0

//#define DEBUG                   1
