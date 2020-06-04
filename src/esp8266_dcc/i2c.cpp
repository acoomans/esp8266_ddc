#include <Arduino.h>
#include <Wire.h>

#include "i2c.h"

byte scan_i2c(byte sda, byte scl, byte addresses[], byte len) {
  byte nDevices = 0;
  
  Wire.begin(sda, scl);

  byte error = 0;
  for (byte i = 1; i < 128; i++)  {
    
    Wire.beginTransmission(i);
    // check if transmission was acknowledged
    error = Wire.endTransmission(); 

    if (error == 0) {
      addresses[nDevices++] = i;
      if (nDevices >= len) { break; }
    }
  }

  return nDevices;
}
