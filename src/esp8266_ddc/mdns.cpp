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

String MDNSquery() {
  Serial.println("Sending mDNS query");
  int n = MDNS.queryService(MDNS_QUERY_SERVICE, MDNS_QUERY_PROTOCOL);
  if (n == 0) {
    Serial.println("No mDNS services found");
  }
  else {
    Serial.print(n);
    Serial.println(" mDNS services found");
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(MDNS.hostname(i));
      Serial.print(" (");
      Serial.print(MDNS.IP(i));
      Serial.print(":");
      Serial.print(MDNS.port(i));
      Serial.println(")");
    }
  }
  Serial.println();

  return MDNS.IP(0).toString();
}
