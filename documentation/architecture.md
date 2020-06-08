# Architecture

## Hardware

Connect DDC Clock and Data to the Arduino. A pull-up resistor might be necessary. See the HDMI and Fritzing files.

## Software

### I2C

I2C is implemented by the `Wire` library on Arduino. It lets you specify the Clock and Data pins with `Wire.begin()`.

The `Wire` library will send bytes by:

1. Sends the address (e.g. 0x37) and its read/write bit (e.g. 0x37 becomes 0x6E)
2. Sends bytes

Similarily, the `Wire` library will receive bytes by:

1. Request the address (e.g. 0x37) and its read/write bit (e.g. 0x37 becomes 0x6F) for bytes
2. Receive bytes

Note: the I2C protocol and the `Wire` library does not provide any additional mechanism, like checksum or retry.

### DDC

DDC is the protocol used to query and manipulate the display's properties (e.g. brightness).

DDC uses I2C and extends to add a few more features:

- Subaddress
- Payload with variable length
- Checksum

Note: the DDC protocol does not define any explicit retry mechanism.

When using the `Wire` library:

1. Let `Wire` deal with the address and its read/write bit
2. Handle the subaddress byte
3. Handle payload length byte
4. Handle any payload
5. Calculate the checksum. The checksum needs to be calculated with the address.

In summary: let `Wire` handle the address, but we need the address to calculate the checksum because it's not part of I2C and not handled by `Wire`.

### EDID

EDID is the format of the data identifying the display.

