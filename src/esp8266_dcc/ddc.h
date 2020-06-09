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

void setupDDC();

typedef struct {
  byte max;
  byte current;
} dcc_value;

dcc_value ddc_read(byte index);
