#include <Arduino.h>
#include <limits>

#define INVALID_READ  std::numeric_limits<float>::infinity()


#define BRIGHTNESS  0x10

void setupDDC();

float ddc_read(byte index);
