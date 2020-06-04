#include "edid.h"

#include "config.h"

void setupEDID() {
  Wire.begin(SDA_PIN, SCL_PIN);

  EDID e = EDID();
  e.requestFrom(I2C_DISPLAY);
  if (e.isValid()) {
    Serial.println("Found EDID:");
    e.print();
  } else {
    Serial.println("No EDID found. Rebooting...");
    delay(5000);
    ESP.restart();
  }  
}
