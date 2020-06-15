#include "Header_file.h"

#define full_cycles_number 3
#define half_cycles_number 8
#define half_cycles_delay 5000;
extern int air_state;
extern int antechamber_state;

boolean Cleaning_routine(boolean half_cycles = false) {
  if (door_open == false) {
    door_has_open = false;
    if (half_cycles == false) {
      if (door_has_open == true) return false;
      if (antechamber_state != 1) {
        if (Move_and_Wait(Full_Vacuum_1) == false) return false;
      }
      if (door_has_open == true) return false;
      if (Move_and_Wait(Atmosphere) == false) return false;
      if (door_has_open == true) return false;
      for (int i = 0; i < (full_cycles_number - 1); i++) {
        if (Move_and_Wait(Full_Vacuum_1) == false) return false;
        if (door_has_open == true) return false;
        if (Move_and_Wait(Atmosphere) == false) return false;
        if (door_has_open == true) return false;
      }
      if (door_has_open == false) return true;              //The cleaning cycle has finished without the door being open so we can return true
    }
    else if (half_cycles == true) {
      if (door_has_open == true) return false;
      for (int i = 0; i < half_cycles_number; i++) {
        if (Move_and_Wait(Half_Vacuum_05) == false) return false;
        if (door_has_open == true) return false;
        if (Move_and_Wait(Atmosphere) == false) return false;
        if (door_has_open == true) return false;
      }
      if (door_has_open == false) return true;              //The cleaning cycle has finished without the door being open so we can return true
    }
  }
  else {
    return false;
  }


}

boolean Short_Cleaning_routine() {
  if (door_open == false) {
    door_has_open = false;
    if (Move_and_Wait(Full_Vacuum_1) == false) return false;
    if (door_has_open == true) return false;
    if (Move_and_Wait(Atmosphere) == false) return false;
    if (door_has_open == true) return false;
    if (door_has_open == false) return true;              //The cleaning cycle has finished without the door being open so we can return true

  }
  else {
    return false;
  }
}

//---------------------------Old Cleaning routine---------------------
//boolean Cleaning_routine(boolean half_cycles = false) {
//  if (door_open == false) {
//    door_has_open = false;
//    if (half_cycles == false) {
//      if (door_has_open == true) return false;
//      if (antechamber_state != 1) {
//        servo_move(1);
//        if (door_has_open == true) return false;            //If the door is opened at any time return false to state that the cleaning routine has been unsuccesful
//        //photoread();
//        if (door_has_open == true) return false;
//        delay(2000);
//      }
//      servo_move(2);
//      if (door_has_open == true) return false;
//      //photoread();
//      if (door_has_open == true) return false;
//      delay(2000);
//      for (int i = 0; i < 2; i++) {
//        servo_move(1);
//        if (door_has_open == true) return false;
//        //photoread();
//        if (door_has_open == true) return false;
//        delay(2000);
//        servo_move(2);
//        if (door_has_open == true) return false;
//        //photoread();
//        if (door_has_open == true) return false;
//        delay(2000);
//      }
//      servo_move(0);
//      if (door_has_open == false) return true;              //The cleaning cycle has finished without the door being open so we can return true
//    }
////    else if (half_cycles == true) {
////      if (door_has_open == true) return false;
////      if (photoRead() != Full_Position) {                                        //Check if the a air state is full
////        servo_move(2);
////      }
////      if (door_has_open == true) return false;
////      delay(2000);
////      for (int i = 0; i < 2; i++) {
////        servo_move(1);
////        if (door_has_open == true) return false;
////        //photoread();
////        if (door_has_open == true) return false;
////        delay(2000);
////        servo_move(2);
////        if (door_has_open == true) return false;
////        //photoread();
////        if (door_has_open == true) return false;
////        delay(2000);
////      }
////      servo_move(0);
////      if (door_has_open == false) return true;
////    }
//  }
//  else {
//    return false;
//  }
//
//
//}
