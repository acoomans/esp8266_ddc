#include "mdns.h"

#include "config.h"

#include <ESP8266mDNS.h>

void setupMDNS() {
  if (MDNS.begin(MDNS_HOSTNAME)) {
    Serial.println("Setting up MDNS responder");
  } else {
    Serial.println("Error setting up MDNS responder");
  }
}
