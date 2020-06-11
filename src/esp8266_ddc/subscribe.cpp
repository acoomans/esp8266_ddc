#include "subscribe.h"

#include "config.h"
#include "ddc.h"
#include "mqtt.h"

void brightness_callback(double x) {
  if (!process_messages) return;
#ifdef DEBUG
  Serial.print("Sub Brightness: "); Serial.println(x);
#endif
  dcc_write(DDC_BRIGHTNESS, x);
}

void input_source_callback(char *data, uint16_t len) {
  if (!process_messages) return;
  String input = String(data);
#ifdef DEBUG
  Serial.print("Sub Input Source: "); Serial.println(input);
#endif
  if (input == MQTT_INPUT_SOURCE_HDMI_1) {
    dcc_write(DDC_INPUT_SOURCE, DDC_INPUT_SOURCE_HDMI_1);
  } else if (input == MQTT_INPUT_SOURCE_HDMI_2) {
    dcc_write(DDC_INPUT_SOURCE, DDC_INPUT_SOURCE_HDMI_2);
  } else if (input == MQTT_INPUT_SOURCE_DP) {
    dcc_write(DDC_INPUT_SOURCE, DDC_INPUT_SOURCE_DP);
  }
}

void volume_callback(double x) {
  if (!process_messages) return;
#ifdef DEBUG
  Serial.print("Sub Volume: "); Serial.println(x);
#endif
  dcc_write(DDC_AUDIO_VOLUME, x);
}

void mute_callback(char *data, uint16_t len) {
  if (!process_messages) return;
  String mute = String(data);
#ifdef DEBUG
  Serial.print("Sub Mute: "); Serial.println(mute);
#endif
  if (mute == MQTT_MUTE_MUTED) {
    dcc_write(DDC_AUDIO_MUTE, DDC_AUDIO_MUTE_MUTED);
  } else if (mute == MQTT_MUTE_UNMUTED) {
    dcc_write(DDC_AUDIO_MUTE, DDC_AUDIO_MUTE_UNMUTED);
  }
}
