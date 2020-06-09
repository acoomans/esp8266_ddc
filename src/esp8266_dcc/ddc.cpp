#include "ddc.h"

#include <Wire.h>
#include <limits>

#include "config.h"

void setupDDC() {
  Wire.begin(SDA_PIN, SCL_PIN);
}

/* A full 8 bit address is the 7 bit address, shifted by one bit, and the last bit it 0 for a write or 1 for a read. E.g. a 7 bit address 0x37 is either 0x6E write and 0x6F read 8 bit addresses.
 */
 
typedef enum {
  write = 0,
  read = 1,
} packet_type;

byte fulladdr(byte addr, packet_type type) {
  return (addr << 1) + type;
}

/* The checksum is calculated based on the address and all other bytes. E.g. 0x6E ^ 0x51 ^ 0x82 ^ 0x01 ^ 0x10. Not managed by the Wire library.
 */
byte checksum(byte addr, byte data[], byte len) {
  byte res = addr;
  for (int i = 0; i < len; i++) {
    res ^= data[i];
  }
  return res;
}

/* Format of write packets:
 *   address: The address to send the packet to, shifted by one bit. The last bit indicates if it's a read or a write. E.g. 0x6E.
 *            The Wire library sends this address in `Wire.beginTransmission`; so just pass address as the `addr` parameter, and do NOT pass the address in the data buffer. 
 *            This address needs to be used for the checksum calculcation however.
 *   subaddress: Whatever the spec says. E.g. 0x51
 *   length: Number of bytes of the payload, OR'ed with 0x80. E.g. for a 2 bytes payload, it's 0x82. Not managed by the Wire library.
 *   payload:
 *     command: E.g. 0x01 for read
 *     index of value: E.g. 0x10 for brightness.
 *   checksum: Calculated based on the address and all other bytes. E.g. 0x6E ^ 0x51 ^ 0x82 ^ 0x01 ^ 0x10. Not managed by the Wire library.
 */
 
void ddc_send(byte addr, packet_type type, byte data[], byte len) {
  byte calculated_checksum = checksum(fulladdr(addr, type), data, len);
  
  Wire.beginTransmission(addr);
#ifdef DEBUG
  Serial.print("ddc_send: ");
  for (int i = 0; i < len; i++) {
    Wire.write(data[i]);
    Serial.print(data[i], HEX); Serial.print(" ");
  }
  Wire.write(calculated_checksum);
  Serial.println(calculated_checksum, HEX);
#else
  Wire.write(data, len);
  Wire.write(calculated_checksum);
#endif
  Wire.endTransmission();  
  delay(40);
}

/* Format of read packets:
 *   address: The address the packet was received on, shifted by one bit. The last bit indicates if it's a read or a write. E.g. 0x6F.
 *            The Wire library receives this address in `Wire.requestFrom`; so the address will NOT be in the data buffer.
 *            This address needs to be used for the checksum calculcation however.
 *   ack: Acknowledges the previously written packet. E.g. 0x6E.
 *   length: Number of bytes of the payload, OR'ed with 0x80. E.g. for a 8 bytes payload, it's 0x88. Not managed by the Wire library.
 *   payload: variable number of bytes; when reading a value it will be the following:
 *     0x02
 *     0x00
 *     index of value: E.g. 0x10 for brightness.
 *     0x00
 *     0x00
 *     max value: E.g. 0xFE
 *     0x00
 *     current value: E.g. 0x50
 *   checksum: Calculated based on the address and all other bytes. E.g. 0x6F ^ 0x6E ^ 0x88 ^ ... Not managed by the Wire library.
 */
byte ddc_receive(byte addr, byte data[], byte len) {
  byte i;
#ifdef DEBUG
  Serial.print("ddc_receive: ");
#endif
  Wire.requestFrom(addr, len + 1);
  for (i = 0; i < len; i++) {
    data[i] = Wire.read();
#ifdef DEBUG
    Serial.print(data[i], HEX); Serial.print(" ");
#endif
  }

  if (Wire.available()) {
    byte checksum_byte = Wire.read();
#ifdef DEBUG
    Serial.println(checksum_byte, HEX);
#endif
    byte calculated_checksum = checksum(fulladdr(addr, read), data, len);
    calculated_checksum ^= 0x6E ^ 0x51; // replace 0x6E by 0x51 for some reason
    if (calculated_checksum != checksum_byte) {
      Serial.print("Checksum mismatch ("); Serial.print(calculated_checksum, HEX); Serial.print(" instead of "); Serial.print(checksum_byte, HEX); Serial.println(")");
      return 0;
    }
#ifdef DEBUG
    Serial.println("Checksum OK");
#endif
  } else {
    Serial.println("Missing checksum");
    return 0;
  }

  delay(40);
  return i;
}

/* Reading values is done by first sending a write packet then reading the response read packet
 */
dcc_value ddc_read(byte index) {

  dcc_value val;
  
  byte data_in[] = {
    0x51,       // subaddress
    0x80 | 2,   // number of bytes in message
    0x01,       // read
    index,      // index
  };
  ddc_send(I2C_DDC, write, data_in, sizeof(data_in));
  
  byte data_out[2 + 8];

  byte retries = RETRY_COUNT;
  while (retries && !ddc_receive(I2C_DDC, data_out, sizeof(data_out))) {
#ifdef DEBUG
    Serial.println("Invalid bytes received: retrying...");
#endif
    retries--;
  }
  if (!retries) {
    Serial.println("Max retries reached");
    val.max = 0;
    val.current = 0;
    return val;
  }
  
#ifdef DEBUG
  if (data_out[0] != 0x6E) Serial.println("Invalid destination address: not 6E");
  if (data_out[1] != 0x88) Serial.println("Invalid length: not 8 bytes");
  if (data_out[2] != 0x2) Serial.println("Invalid byte 2");
  if (data_out[3] != 0x0) Serial.println("Invalid byte 3");
  if (data_out[4] != data_in[3]) Serial.println("Invalid index: not requested index");
  if (data_out[5] != 0x0) Serial.println("Invalid byte 5");
  if (data_out[6] != 0x0) Serial.println("Invalid byte 6");
  val.max = data_out[7]; Serial.print("Max value: "); Serial.println(val.max, HEX);
  if (data_out[8] != 0x0) Serial.println("Invalid byte 8");
  val.current = data_out[9]; Serial.print("Current value: "); Serial.println(val.current, HEX);
#else
  byte val.max = data_out[7];
  byte val.current = data_out[9];
#endif
    
  return val;
}
