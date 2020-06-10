#include "publish.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "mqtt.h"
#include "ddc.h"

void publishCheck();

int publish_brightness_errors = 0;

void publishBrightness() {
  dcc_value val = ddc_read(DDC_BRIGHTNESS);
  
  if (DDC_INVALID_READ(val)) {
    Serial.println(F("Error reading brightness"));
    publish_brightness_errors++;  
  } else {
    int brightness = DDC_FLOAT_VALUE(val) * 100;
#ifdef DEBUG
    Serial.print("Pub Brightness: "); Serial.println(brightness);
#endif
    
    if (brightness_pub.publish(brightness)) {
      publish_brightness_errors = 0;
    } else {
      Serial.println(F("Error publishing brightness"));
      publish_brightness_errors++;
    }
  }
  publishCheck();
}

int publish_inputsource_errors = 0;

void publishInputSource() {
  dcc_value val = ddc_read(DDC_INPUT_SOURCE);
  
  if (DDC_INVALID_READ(val)) {
    Serial.println(F("Error reading input source"));
    publish_inputsource_errors++;
  } else {
    const char *inputsource = "Undefined";
    switch (val.current) {
      case DDC_INPUT_SOURCE_DP:
        inputsource = MQTT_INPUT_SOURCE_DP;
        break;
      case DDC_INPUT_SOURCE_HDMI_1:
        inputsource = MQTT_INPUT_SOURCE_HDMI_1;
        break;
      case DDC_INPUT_SOURCE_HDMI_2:
        inputsource = MQTT_INPUT_SOURCE_HDMI_2;
        break;
    }
#ifdef DEBUG
    Serial.print("Pub Input Source: "); Serial.println(inputsource);
#endif
    
    if (inputsource_pub.publish(inputsource)) {
      publish_inputsource_errors = 0;
    } else {
      Serial.println(F("Error publishing input source"));
      publish_inputsource_errors++;
    }
  }
  publishCheck();
}

int publish_volume_errors = 0;

void publishVolume() {
  dcc_value val = ddc_read(DDC_AUDIO_VOLUME);
  
  if (DDC_INVALID_READ(val)) {
    Serial.println(F("Error reading volume"));
    publish_volume_errors++;  
  } else {
    int volume = DDC_FLOAT_VALUE(val) * 100;
#ifdef DEBUG
    Serial.print("Pub Volume: "); Serial.println(volume);
#endif
    
    if (volume_pub.publish(volume)) {
      publish_volume_errors = 0;
    } else {
      Serial.println(F("Error publishing volume"));
      publish_volume_errors++;
    }
  }
  publishCheck();
}

int publish_mute_errors = 0;

void publishMute() {
  dcc_value val = ddc_read(DDC_AUDIO_MUTE);
  
  if (DDC_INVALID_READ(val)) {
    Serial.println(F("Error reading mute"));
    publish_mute_errors++;  
  } else {
    const char *mute = "UNDEF";
    switch (val.current) {
      case DDC_AUDIO_MUTE_MUTED:
        mute = MQTT_MUTE_MUTED;
        break;
      case DDC_AUDIO_MUTE_UNMUTED:
        mute = MQTT_MUTE_UNMUTED;
        break;
    }
#ifdef DEBUG
    Serial.print("Pub Mute: "); Serial.println(mute);
#endif
    
    if (mute_pub.publish(mute)) {
      publish_mute_errors = 0;
    } else {
      Serial.println(F("Error publishing mute"));
      publish_mute_errors++;
    }
  }
  publishCheck();
}


void publishCheck() {
  if (
    publish_brightness_errors > 5 ||
    publish_inputsource_errors > 5 || 
    publish_volume_errors > 5 ||
    publish_mute_errors > 5
    ) {
    Serial.println(F("Too many errors, killing..."));
    delay(5000);
    ESP.restart();
  }
}
