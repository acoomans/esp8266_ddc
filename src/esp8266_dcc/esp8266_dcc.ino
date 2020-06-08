#include "config.h"

#include "wifi.h"
#include "ota.h"
#include "mdns.h"

//#include <Wire.h>
#include "edid.h"
#include "ddc.h"


//void checksum(byte data[], int len) {
//  byte res = data[0];
//  res ^= data[1] ^ data[2];
//  for (int i = 3; i < len - 1; i++) {
//    res ^= data[i];
//  }
//  data[len-1] = res;
//}


//void ddc_read() {
//  Wire.begin(SDA_PIN, SCL_PIN);
//  
//  delay(40);
//  Serial.println("Requesting: Brightness");
//  
//  byte data[] = {
////    0x6E,       // read
//    0x51,       // subaddress
//    0x80 | 2,   // number of bytes in message
//    
//    0x01,       // read
//    0x10,       // brightness
//    
//    0xAC           // checksum
//  };
////  checksum(data, sizeof(data));
//  
//  Wire.beginTransmission(0x37);
//  for (int i = 0; i < sizeof(data); i++) {
//    Wire.write(data[i]);
//    Serial.println(data[i], HEX);
//  }
////  Wire.write(data, sizeof(data));
//  Wire.endTransmission();
//  
//  delay(40);
//  Serial.println("Response:");
//
//  Wire.requestFrom(0x37, 3 + 8);
//
//  while(Wire.available()) { 
//    char c = Wire.read();
//    Serial.println(c, HEX);
//  }
//  
//  Serial.println("Done.");
//}


void setup() {
  Serial.begin(115200);
  Serial.print("Starting "); Serial.print(HOSTNAME); Serial.println("...");

//  setupWiFi();
//  setupOTA();
//  setupMDNS();
//  setupEDID();
  setupDDC();

  Serial.println();
  Serial.println("Started.");
}

void loop() {
//  handleOTA();

  delay(1000);
  float val = ddc_read(BRIGHTNESS);
  Serial.print("Brightness: "); Serial.println(val);
}
