/*
   // Positions are: 0 middle, 1 vacuum, 2 refill.


   #define Full_position 0                         //These are gauge positions
  #define Vacuum_position 1
  #define Unknown_position 2

   Wanted states:
   -Full Vacuum (-1 bar)
   -Atmosphere (0 bar)
   -Half Vacuum (-0.5 bar)
   -Clean Vacuum (-0.2 bar)

*/

#include "Header_file.h"

#define Vacuum_Delay 30000

extern int current_pos;
int current_valve_pos = 0;


boolean Move_and_Wait(int Chamber_State) {
  if (door_open == false) {
    if (Chamber_State == Full_Vacuum_1) {
      servo_move(Servo_Vacuum);
      delay(Vacuum_Delay);
      if (photoRead() == Vacuum_position) {
        servo_move(Servo_Middle);
        return true;
      }
      else {
        servo_move(Servo_Middle);
        Serial.println("Error, probably due to an open door (to vacuum)");
        return false;                                                          // THIS SHOULD BE FALSE (it is set to true for debugging purposes)
      }
    }
    else if (Chamber_State == Atmosphere) {
      servo_move(Servo_Refill);
      if (photoRead() == Full_position) {
        servo_move(Servo_Middle);
        return true;
      }
      else {
        servo_move(Servo_Middle);
        Serial.println("Error, probably due to an open door (to atmosphere)");
        return false;                                                          // THIS SHOULD BE FALSE (it is set to true for debugging purposes)
      }
    }
    else if (Chamber_State == Half_Vacuum_05) {
      servo_move(Servo_Vacuum);
      if (photoRead(true) == Unknown_position) {
        delay(Vacuming_05_delay);
        servo_move(Servo_Middle);
        if (photoRead(true) == Unknown_position) return true;
        else return false;                                                     // THIS SHOULD BE FALSE (it is set to true for debugging purposes)
      }
      else {
        servo_move(Servo_Middle);
        Serial.println("Error, probably due to an open door (to half cycles)");
        return false;                                                          // THIS SHOULD BE FALSE (it is set to true for debugging purposes)
      }
    }
    else if (Chamber_State == Clean_Vacuum_02) {
      servo_move(Servo_Vacuum);
      if (photoRead(true) == Unknown_position) {
        delay(Vacuming_02_delay);
        servo_move(Servo_Middle);
        if (photoRead(true) == Unknown_position) return true;
        else return false;                                                     // THIS SHOULD BE FALSE (it is set to true for debugging purposes)
      }
      else {
        servo_move(Servo_Middle);
        Serial.println("Error, probably due to an open door (to clean 0.2 vacuum)");
        return false;                                                          // THIS SHOULD BE FALSE (it is set to true for debugging purposes)
      }
    }
  }
}
