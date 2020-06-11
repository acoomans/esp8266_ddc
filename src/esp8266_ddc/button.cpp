#include "button.h"

#include "config.h"
#include "ddc.h"

void setupButton() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

bool isButtonPressed() {
  
  static unsigned long previousMillis = 0;
  static int previousButtonRead = LOW;
  
  unsigned long currentMillis = millis();
  int currentButtonRead = digitalRead(BUTTON_PIN);
  
  bool res = (
    (currentMillis - previousMillis) > 200 &&
    previousButtonRead == LOW && 
    currentButtonRead == HIGH
  );
  if (res) {
    previousMillis = currentMillis;
  }
  previousButtonRead = currentButtonRead;
  return res;
}

void nextInputSource() {
  dcc_value val = ddc_read(DDC_INPUT_SOURCE);
  
  if (DDC_INVALID_READ(val)) {
    Serial.println(F("Error reading input source"));
  } else {
    switch (val.current) {
      case DDC_INPUT_SOURCE_DP:
        dcc_write(DDC_INPUT_SOURCE, DDC_INPUT_SOURCE_HDMI_1);
        break;
      case DDC_INPUT_SOURCE_HDMI_1:
        dcc_write(DDC_INPUT_SOURCE, DDC_INPUT_SOURCE_HDMI_2);
        break;
      case DDC_INPUT_SOURCE_HDMI_2:
      default:
        dcc_write(DDC_INPUT_SOURCE, DDC_INPUT_SOURCE_DP);
    }
  }
}

void loopButton() {
    if (isButtonPressed()) {
    nextInputSource();
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }
}
