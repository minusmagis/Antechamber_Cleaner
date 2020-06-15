#include "Header_file.h"

int photoValueL = 0;
int photoValueR = 0;
int photoState_Vacuum_L = 557;
int photoState_Vacuum_R = 1002;
int photoState_Full_L = 375;
int photoState_Full_R = 821;


#define Calibration_Vacuum 1
#define Calibration_Full 2

int photoRead(boolean fast = false , int calibration = 0 ) {

  int averages = 50;
  int cycles = 550;     //Approx execution time is 82.2 ms so 550 cycles are a 45 second timeout (250 cycles more or less 25 seconds)

  if (fast) {
    averages = 20;
    cycles = 40;
  }

  int i = 0;
  int tempL[averages];
  int tempR[averages];
  unsigned long averageL = 0;
  unsigned long averageR = 0;

  for (int l = 0; l < averages; l++) {
    tempL[l] = 0;
    tempR[l] = 0;
  }


  for (  int timeout = 0; timeout <= cycles; timeout++) {
    if (i >= averages) {
      i = 0;
    }

    digitalWrite(irledPinL, LOW);
    digitalWrite(irledPinR, LOW);
    int backgroundL = analogRead(photoPinL);
    if (fast == false) delay(9);
    delay(1);
    digitalWrite(irledPinL, HIGH);
    if (fast == false) delay(9);
    delay(1);
    photoValueL = analogRead(photoPinL);
    if (fast == false) delay(9);
    delay(1);
    digitalWrite(irledPinL, LOW);
    if (fast == false) delay(9);
    delay(1);
    int backgroundR = analogRead(photoPinR);
    if (fast == false) delay(9);
    delay(1);
    digitalWrite(irledPinR, HIGH);
    if (fast == false) delay(9);
    delay(1);
    photoValueR = analogRead(photoPinR);
    if (fast == false) delay(9);
    delay(1);
    digitalWrite(irledPinR, LOW);
    if (fast == false) delay(9);
    delay(1);
    tempL[i] = abs(-photoValueL + backgroundL);
    tempR[i] = abs(-photoValueR + backgroundR);


    for (int j = 0; j < averages; j++) {
      averageL += tempL[j];
    }
    averageL = averageL / averages;
    for (int k = 0; k < averages; k++) {
      averageR += tempR[k];
    }
    averageR = averageR / averages;
#if defined debug
    //    Serial.print("Photodetector L = ");
    //    Serial.print(photoValueL);
    //    Serial.print("  Photodetector R = ");
    //    Serial.print(photoValueR);
    //    Serial.print("Background L = ");
    //    Serial.print(backgroundL);
    //    Serial.print("  Background R = ");
    //    Serial.print(backgroundR);
    //    Serial.print("  Corrected L = ");
    //    Serial.print(-photoValueL + backgroundL);
    //    Serial.print("  Corrected R = ");
    //    Serial.print(-photoValueR + backgroundR);
    Serial.print("Ecuation : A>B>C");
    Serial.print((photoState_Vacuum_L + Gauge_Read_Threshold));
    Serial.print("   > ");
    Serial.print(averageL);
    Serial.print("   > ");
    Serial.print((photoState_Vacuum_L - Gauge_Read_Threshold));
    Serial.print("Ecuation : A>B>C");
    Serial.print((photoState_Vacuum_R + Gauge_Read_Threshold));
    Serial.print("   > ");
    Serial.print(averageR);
    Serial.print("   > ");
    Serial.println((photoState_Vacuum_R - Gauge_Read_Threshold));
    //    Serial.println(millis());

#endif

    if (((photoState_Vacuum_L + Gauge_Read_Threshold) > (averageL)) && ((averageL) > (photoState_Vacuum_L - Gauge_Read_Threshold)) && ((photoState_Vacuum_R + Gauge_Read_Threshold) > (averageR)) && ((averageR) > (photoState_Vacuum_R - Gauge_Read_Threshold)))
    {
      Serial.println("Vacuum");
      if (calibration == 0) return Vacuum_position;  //vacuum position
    }
    else if (((photoState_Full_L + Gauge_Read_Threshold) > (averageL)) && ((averageL) > (photoState_Full_L - Gauge_Read_Threshold)) && ((photoState_Full_R + Gauge_Read_Threshold) > (averageR)) && ((averageR) > (photoState_Full_R - Gauge_Read_Threshold)))
    {
      Serial.println("Full");
      if (calibration == 0) return Full_position;  //full position
    }
    else if (timeout >= cycles)
    {
      if (calibration == Calibration_Vacuum) {
        photoState_Vacuum_L = averageL ;
        photoState_Vacuum_R = averageR ;
      }
      else if (calibration == Calibration_Full) {
        photoState_Full_L = averageL  ;
        photoState_Full_R = averageR ;
      }
      Serial.println("Timeout");
      return Unknown_position;  //unknown position
    }
    i++;
  }

}
