#include <EEPROM.h>
#include "Header_file.h"

extern int photoThreshold1UpperSta;
extern int photoThreshold1LowerSta;

extern int photoThreshold2UpperSta;
extern int photoThreshold2LowerSta;


void EEPROMWrite()
{
  #if defined debug
  Serial.println("\nWriting ints to 2 bytes each");
  #endif
    EEPROM.put(0, photoThreshold1UpperSta);
    EEPROM.put(2, photoThreshold1LowerSta);
        
    EEPROM.put(4, photoThreshold2UpperSta);
    EEPROM.put(6, photoThreshold2LowerSta);

    EEPROM.put(8, magThreshold1);
    EEPROM.put(10, magThreshold2);
}

void EEPROMRead()
{
  int intData = 0;
  byte eepromPosition = 0;
  #if defined debug
  Serial.println("Reading ints");
  #endif
  for (int eepromCount = 0; eepromCount < 6; eepromCount++)
  {
    eepromPosition = eepromCount * 2;
    EEPROM.get(eepromPosition, intData);
    #if defined debug
    Serial.print("position : ");
    Serial.print(eepromPosition);
    Serial.print(" : ");
    Serial.println(intData);
    #endif
  }
}
