#include <Arduino.h>
#include <limits>

#define INVALID_READ(v)   (v.max == 0 && v.current == 0)
#define FLOAT_VALUE(v)    (1.0 * v.current / v.max)

#define BRIGHTNESS    0x10
#define CONTRAST      0x12
#define INPUT_SOURCE  0x60
#define AUDIO_VOLUME  0x62
#define AUDIO_MUTE    0x8D
#define POWER_CONTROL 0xE1

#define INPUT_SOURCE_DP  0x0F
#define INPUT_SOURCE_HDMI_1  0x11
#define INPUT_SOURCE_HDMI_2  0x12

void setupDDC();

typedef struct {
  byte max;
  byte current;
} dcc_value;

dcc_value ddc_read(byte index);
void dcc_write(byte index, byte value);
