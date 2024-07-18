#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "LineFollow.h"
#include "ServoControl.h"

// Red Arena
#include "Red/RedGrid1.h"
#include "Red/RedGrid2.h"
#include "Red/RedGrid3.h"
#include "Red/RedGrid4.h"
#include "Red/RedGrid5.h"
#include "Red/RedGrid6.h"
#include "Red/RedGrid7.h"
#include "Red/RedGrid8.h"
#include "Red/RedGrid9.h"
#include "Red/RedGrid10.h"

// Blue Arena
#include "Blue/BlueGrid1.h"
#include "Blue/BlueGrid2.h"
#include "Blue/BlueGrid3.h"
#include "Blue/BlueGrid4.h"
#include "Blue/BlueGrid5.h"
#include "Blue/BlueGrid6.h"
#include "Blue/BlueGrid7.h"
#include "Blue/BlueGrid8.h"
#include "Blue/BlueGrid9.h"
#include "Blue/BlueGrid10.h"

#define ENC1 2
#define ENC2 3

#define ARENA 32

#define DIP1 13
#define DIP2 11
#define DIP3 10
#define DIP4 12

void readSensorValsDebugAnalog(int *sensors)
{
  for (int i = 0; i < 5; i++)
  {
    Serial.print(analogRead(sensors[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}

void readSensorValsDebugDigital(int *sensors)
{
  int leftm1 = analogRead(sensors[0]) > 800 ? 1 : 0;
  int left1 = analogRead(sensors[1]) > 800 ? 1 : 0;
  int middle1 = analogRead(sensors[2]) > 800 ? 1 : 0;
  int right1 = analogRead(sensors[3]) > 800 ? 1 : 0;
  int rightm1 = analogRead(sensors[4]) > 800 ? 1 : 0;

  Serial.print(leftm1);
  Serial.print("  ");
  Serial.print(left1);
  Serial.print("  ");
  Serial.print(middle1);
  Serial.print("  ");
  Serial.print(right1);
  Serial.print("  ");
  Serial.println(rightm1);
  delay(100);
}

void stripCountDebug(int strips)
{
  int leftm1 = analogRead(MID2) > 700 ? 1 : 0;
  unsigned long currentMillis = millis();

  if (leftm1 == 0 && !is_line)
  {
    strips_count++;
    is_line = true;
    previousMillis = currentMillis;
  }
  else if (currentMillis - previousMillis > intervalMillis)
  {
    is_line = false;
  }

  if (strips_count < strips)
  {
    Serial.println(strips_count);
  }
  else
  {
    // halt();
    Serial.print(strips_count);
    Serial.print(" ");
    Serial.println("End");
    strips_count = 0;
    return;
  }
}

void dipSwitchDebug()
{
  Serial.print(digitalRead(DIP1));
  Serial.print(" ");
  Serial.print(digitalRead(DIP2));
  Serial.print(" ");
  Serial.print(digitalRead(DIP3));
  Serial.print(" ");
  Serial.println(digitalRead(DIP4));
}

void forwardUntilMiddleSensors()
{
  int mid1_val = analogRead(MID1) > 800 ? 1 : 0;
  int mid2_val = analogRead(MID2) > 800 ? 1 : 0;

  while (mid1_val == 1 && mid2_val == 1)
  {
    forward(50);
    mid1_val = analogRead(MID1) > 800 ? 1 : 0;
    mid2_val = analogRead(MID2) > 800 ? 1 : 0;
  }
  halt();
}

void configurePins()
{
  pinMode(ENC1, INPUT);
  pinMode(ENC2, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENC1), enc1_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC2), enc2_isr, RISING);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  pinMode(ARENA, INPUT_PULLUP);

  pinMode(MID1, INPUT);
  pinMode(MID2, INPUT);

  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);

  frontServo.attach(F_SERVO);
  backServo.attach(B_SERVO);

  frontServo.write(95);
  backServo.write(95);

  for (size_t i = 0; i < sizeof(S1) / sizeof(int); i++)
  {
    pinMode(S1[i], INPUT);
  }

  for (size_t i = 0; i < sizeof(S2) / sizeof(int); i++)
  {
    pinMode(S2[i], INPUT);
  }

  delay(1000);
}

void red()
{
  int switch1 = digitalRead(DIP1);
  int switch2 = digitalRead(DIP2);
  int switch3 = digitalRead(DIP3);
  int switch4 = digitalRead(DIP4);

  // start
  linefollowUntil(4);
  delay(1000);
  // first right turn
  right90(80);
  delay(1000);

  if (!switch1 && !switch2 && !switch3 && !switch4)
  { // 0000
    red_grid1();
  }
  else if (switch1 && !switch2 && !switch3 && !switch4)
  { // 0001
    red_grid2();
  }
  else if (!switch1 && switch2 && !switch3 && !switch4)
  { // 0010
    red_grid3();
  }
  else if (switch1 && switch2 && !switch3 && !switch4)
  { // 0011
    red_grid4();
  }
  else if (!switch1 && !switch2 && switch3 && !switch4)
  { // 0100
    red_grid5();
  }
  else if (switch1 && !switch2 && switch3 && !switch4) 
  { // 0101
    red_grid6();
  }
  else if (!switch1 && switch2 && switch3 && !switch4)
  { // 0110
    red_grid7();
  }
  else if (switch1 && switch2 && switch3 && !switch4)
  { // 0111
    red_grid8();
  }
  else if (!switch1 && !switch2 && !switch3 && switch4)
  { // 1000
    red_grid9();
  }
  else if (switch1 && !switch2 && !switch3 && switch4)
  {
    //1001  
    red_grid10();
  }

  // ============= third tree and rock =============
  while (1)
  {
    Serial.println("END");
  }
}

void blue()
{
  int switch1 = digitalRead(DIP1);
  int switch2 = digitalRead(DIP2);
  int switch3 = digitalRead(DIP3);
  int switch4 = digitalRead(DIP4);

  // start
  linefollowUntil(4);
  delay(1000);
  // first right turn
  left90(80);
  delay(1000);

  if (!switch1 && !switch2 && !switch3 && !switch4)
  { // 0000
    blue_grid1();
  }
  else if (switch1 && !switch2 && !switch3 && !switch4)
  { // 0001
    blue_grid2();
  }
  else if (!switch1 && switch2 && !switch3 && !switch4)
  { // 0010
    blue_grid3();
  }
  else if (switch1 && switch2 && !switch3 && !switch4)
  { // 0011
    blue_grid4();
  }
  else if (!switch1 && !switch2 && switch3 && !switch4)
  { // 0100
    blue_grid5();
  }
  else if (switch1 && !switch2 && switch3 && !switch4)
  { // 0101
    blue_grid6();
  }
  else if (!switch1 && switch2 && switch3 && !switch4)
  { // 0110
    blue_grid7();
  }
  else if (switch1 && switch2 && switch3 && !switch4)
  { // 0111
    blue_grid8();
  }
  else if (!switch1 && !switch2 && !switch3 && switch4)
  { // 1000
    blue_grid9();
  }
  else if (switch1 && !switch2 && !switch3 && switch4)
  { // 1001
    blue_grid10();
  }

  // ============= third tree and rock =============
  while (1)
  {
    Serial.println("END");
  }
}

void setup()
{
  Serial.begin(9600);
  configurePins();
}

void loop()
{
  if (digitalRead(ARENA))
  {
    // RED ARENA
    red();
  }
  else
  {
    // BLUE ARENA
    blue();
  }
}