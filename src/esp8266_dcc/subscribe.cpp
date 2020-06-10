#include "subscribe.h"

#include "config.h"
#include "ddc.h"

void brightness_callback(double x) {
#ifdef DEBUG
  Serial.print("Sub Brightness: "); Serial.println(x);
#endif
  dcc_write(BRIGHTNESS, x);
}

void input_source_callback(char *data, uint16_t len) {
  String input = String(data);
#ifdef DEBUG
  Serial.print("Sub Input Source: "); Serial.println(input);
#endif
  if (input == "HDMI1") {
    dcc_write(INPUT_SOURCE, INPUT_SOURCE_HDMI_1);
  } else if (input == "HDMI2") {
    dcc_write(INPUT_SOURCE, INPUT_SOURCE_HDMI_2);
  } else if (input == "DP") {
    dcc_write(INPUT_SOURCE, INPUT_SOURCE_DP);
  }
}

void volume_callback(double x) {
#ifdef DEBUG
  Serial.print("Sub Volume: "); Serial.println(x);
#endif
  dcc_write(AUDIO_VOLUME, x);
}

void mute_callback(char *data, uint16_t len) {
  String mute = String(data);
#ifdef DEBUG
  Serial.print("Sub Mute: "); Serial.println(mute);
#endif
  if (mute == "ON") {
    dcc_write(AUDIO_MUTE, AUDIO_MUTE_MUTED);
  } else if (mute == "OFF") {
    dcc_write(AUDIO_MUTE, AUDIO_MUTE_UNMUTED);
  }
}
