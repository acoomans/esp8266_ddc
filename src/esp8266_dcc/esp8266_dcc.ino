#include <Wire.h>
#include "i2c.h"

#define SDA_PIN 5
#define SCL_PIN 4

const int16_t I2C_SLAVE = 0x08;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  scan_pins_i2c();
  Serial.println("Started.");
}

void loop() {
}
