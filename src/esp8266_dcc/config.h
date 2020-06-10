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
#define MQTT_DELAY              120

#define SDA_PIN                 5
#define SCL_PIN                 4

#define I2C_EDID                0x50
#define I2C_DDC                 0x37

#define DDC_RETRY               3

#define DEBUG                   1
