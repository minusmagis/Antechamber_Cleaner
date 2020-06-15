#include "Header_file.h"

void relayActuate(bool state){
  if(state == true){
  digitalWrite(relayPin1,HIGH);
  digitalWrite(relayPin2,HIGH);
  digitalWrite(relayPin3,HIGH);
  }
  else{
  digitalWrite(relayPin1,LOW);
  digitalWrite(relayPin2,LOW);
  digitalWrite(relayPin3,LOW);
  }
}
