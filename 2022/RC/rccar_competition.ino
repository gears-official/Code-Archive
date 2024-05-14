#include "Remote.h"
#include "RaceCar.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // r motor 
  pinMode(RMPWM, OUTPUT); // pwm
  pinMode(RMP, OUTPUT);
  pinMode(RMN, OUTPUT);
  // l motor
  pinMode(LMPWM, OUTPUT); // pwm
  pinMode(LMP, OUTPUT);
  pinMode(LMN, OUTPUT);
  startRemote();
}

void loop() {
//  // Setting remote for different channels 
//  Serial.print(getChannel(CH1));
//  Serial.print(" ");
//  Serial.println(getChannel(CH2));
//
//  Serial.println("-----------------------");
//  1493 1510 CH2 Rest pos
//  f: 994 CH2
//  b: 1988 CH2
// 1497 1510 CH1 Rest pos
// r: 1988 CH1
// l: 994 CH1
  int c2Val = getChannel(CH2);
  int c4Val = getChannel(CH4);
  
  if (c2Val < 1490 ) {
   Serial.println("Straight");
   straight();
  }
  
  else if (c2Val > 1515) {
    Serial.println("Backward");
     backward();
  }
  else if (c4Val < 1490) {
    Serial.println("Left");
    left(); 
  }
  
  else if (c4Val > 1515) {
    Serial.println("Right");
    right();
  }
  else {
    halt();  
  }
//  delay(1000);
}
