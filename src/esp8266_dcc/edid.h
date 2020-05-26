#include <Arduino.h>
#include <Wire.h>pr

// https://en.wikipedia.org/wiki/Extended_Display_Identification_Data

enum displayDescriptorType {
    serialNumber,
    unspecifiedText,
    displayName,
    other,
};
typedef displayDescriptorType displayDescriptorType_t;

class EDIDDisplayDescriptor {
public:
    displayDescriptorType_t displayDescriptorType;
    char displayDescriptorText[13] = "\n";
    bool isDisplayDescriptorTextReadable = false;

    void parse(unsigned char *arr) {
        bool isDisplayDescriptor = ((arr[0] << 8) + arr[1]) == 0;
        if (!isDisplayDescriptor) { return; }

        unsigned char displayDescriptorTypeByte = arr[3];
        switch (displayDescriptorTypeByte) {
            case 0xFF:
                displayDescriptorType = serialNumber;
                break;
            case 0xFE:
                displayDescriptorType = unspecifiedText;
                break;
            case 0xFC:
                displayDescriptorType = displayName;
                break;
            default:
                displayDescriptorType = other;
        }

        switch (displayDescriptorType) {
            case serialNumber:
            case unspecifiedText:
            case displayName:
                for (int i = 0; i <= 12; i++) {
                  char c = arr[i + 5];
                  displayDescriptorText[i] = c;
                  if (
                    ('a' <= c && c <= 'z') ||
                    ('A' <= c && c <= 'Z')
                    ) {
                      isDisplayDescriptorTextReadable = true;
                  }
                }
            default: break;
        }
        displayDescriptorText[12] = '\0';
    }

    void print() {
      switch (displayDescriptorType) {
        case serialNumber:
          Serial.print("serialNumber: ");
          break;
        case unspecifiedText:
          Serial.print("unspecifiedText: ");
          break;
         case displayName:
           Serial.print("displayName: ");
           break;
         default:
           Serial.print("other: ");
      }
      Serial.print(displayDescriptorText);
    }
};

typedef enum {
    undefined,
    HDMIa,
    HDMIb,
    MDDI,
    DisplayPort,
} videoInterface;

class EDID {
public:
    bool hasHeader = false;
    bool isChecksumValid = false;
    
    char manufacturerID[4] = "";
    bool isDigital = false;
    videoInterface video_interface = undefined;
    
    EDIDDisplayDescriptor displayDescriptor0;
    EDIDDisplayDescriptor displayDescriptor1;
    EDIDDisplayDescriptor displayDescriptor2;
    EDIDDisplayDescriptor displayDescriptor3;

    void requestFrom(byte address) {
      byte bytes = Wire.requestFrom(address, 128);
      unsigned char buffer[128];
      for (int i=0; Wire.available() && i < sizeof(buffer); i++) {
        buffer[i] = Wire.read();
      }
      parse(buffer);
    }

    bool isValid() {
        return hasHeader && isChecksumValid;
    }
    
    void parse(unsigned char *arr) {
        hasHeader = (
                (arr[0] == 0x0) &&
                (arr[1] == 0xFF) &&
                (arr[2] == 0xFF) &&
                (arr[3] == 0xFF) &&
                (arr[4] == 0xFF) &&
                (arr[5] == 0xFF) &&
                (arr[6] == 0xFF) &&
                (arr[7] == 0x0)
        );
        if (!hasHeader) { return; }

        unsigned char checksum = 0;
        for (int i = 0; i < 128; i++) {
            checksum += arr[i] % 256;
        }
        isChecksumValid = (checksum == 0);
        if (!isChecksumValid) { return; }

        unsigned int manufacturerBytes = (arr[8] << 8) + arr[9];
        char offset = 'a' - 1;
        manufacturerID[0] = offset + ((manufacturerBytes & (31 << 10)) >> 10);
        manufacturerID[1] = offset + ((manufacturerBytes & (31 << 5)) >> 5);
        manufacturerID[2] = offset + ((manufacturerBytes & (31 << 0)) >> 0);
        manufacturerID[3] = '\0';

        unsigned char displayBytes = arr[20];
        isDigital = displayBytes & 128;
        if (isDigital) {
            unsigned char video_interface_bits = displayBytes & (7 << 4) >> 4;
            switch (video_interface_bits) {
                case 1:
                    video_interface = HDMIa;
                    break;
                case 2:
                    video_interface = HDMIb;
                    break;
                case 4:
                    video_interface = DisplayPort;
                    break;
                default:
                    video_interface = undefined;
            }
        }

        displayDescriptor0 = EDIDDisplayDescriptor();
        displayDescriptor0.parse(arr + 54);

        displayDescriptor1 = EDIDDisplayDescriptor();
        displayDescriptor1.parse(arr + 72);

        displayDescriptor2 = EDIDDisplayDescriptor();
        displayDescriptor2.parse(arr + 90);

        displayDescriptor3 = EDIDDisplayDescriptor();
        displayDescriptor3.parse(arr + 108);
    }

    void print() {
      if (!hasHeader) { Serial.println("no EDID header"); return; }
      if (!isChecksumValid) { Serial.println("invalid checksum"); return; }
      
      Serial.print("manufacturerID: ");
      Serial.println(manufacturerID);

      Serial.print("input: ");
      if (isDigital) {
        Serial.println("digital");
        
        Serial.print("video_interface: ");
        switch (video_interface) {
          case undefined:
            Serial.println("Undefined");
            break;
          case HDMIa:
          case HDMIb:
            Serial.println("HDMI");
            break;
          case DisplayPort:
            Serial.println("DisplayPort");
            break;
          default:
            Serial.println("Other");
        }
      }

      if (displayDescriptor0.isDisplayDescriptorTextReadable) {
        displayDescriptor0.print();
      }
      if (displayDescriptor1.isDisplayDescriptorTextReadable) {
        displayDescriptor1.print();
      }
      if (displayDescriptor2.isDisplayDescriptorTextReadable) {
        displayDescriptor2.print();
      }
      if (displayDescriptor3.isDisplayDescriptorTextReadable) {
        displayDescriptor3.print();
      }
    }
};
