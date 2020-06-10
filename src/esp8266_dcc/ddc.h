#include <Arduino.h>
#include <limits>

#define DDC_INVALID_READ(v)   (v.max == 0 && v.current == 0)
#define DDC_FLOAT_VALUE(v)    (1.0 * v.current / v.max)

#define DDC_BRIGHTNESS    0x10
#define DDC_CONTRAST      0x12
#define DDC_INPUT_SOURCE  0x60
#define DDC_AUDIO_VOLUME  0x62
#define DDC_AUDIO_MUTE    0x8D
#define DDC_POWER_CONTROL 0xE1

#define DDC_INPUT_SOURCE_DP       0x0F
#define DDC_INPUT_SOURCE_HDMI_1   0x11
#define DDC_INPUT_SOURCE_HDMI_2   0x12

#define DDC_AUDIO_MUTE_MUTED      0x1
#define DDC_AUDIO_MUTE_UNMUTED    0x2

void setupDDC();

typedef struct {
  byte max;
  byte current;
} dcc_value;

dcc_value ddc_read(byte index);
void dcc_write(byte index, byte value);
