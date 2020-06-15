#include "Header_file.h"



int magThreshold1 = 430;
int magThreshold2 = 430;

boolean magRead(){
  int magValue1 = 0;
  int magValue2 = 0;
  magValue1 = analogRead(magSensor1);
  magValue2 = analogRead(magSensor2);
//  #if defined debug
//  Serial.print("Magnet 1 = ");
//  Serial.print(magValue1);
//  Serial.print("  Magnet 2 = ");
//  Serial.println(magValue2);
//  #endif
  if((magValue1 < magThreshold1) && (magValue2 < magThreshold2))
  {
    //Serial.println("Door Closed");
    return false;
  }
  else
  {
    //Serial.println("Door Open");
    return true;
  }
}
