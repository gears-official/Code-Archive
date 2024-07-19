
#include <Arduino.h>
#include <Servo.h>

int changeArena = 45;
int dir1 = 33;
int dir2 = 32;
int dir3 = 31;
int dir4 = 30;

int lFSpeed = 10;
int lBSpeed = 11;

int rFSpeed = 8;
int rBSpeed = 9;

int rMotor1 = 26;
int rMotor2 = 27;
int rPwm = 8;

int blackMaxValue = 600;

int motorSpeed = 80;
int turnSpeed = 140;

int slightTurnSpeed = 60;
int backwardSpeed = 70;

int motorDifference = 5;
// float percentage = 15;
//  MidSensors

int rightMiddle = 18;
int leftMiddle = 25;

int servoRotation = 0;

// Front Sensors
int fMostLeftSensor = A3;
int fLeftSensor = A2;
int fMiddleSensor = A1;
int fRightSensor = A0;
int fMostRightSensor = A4;

// Back Sensor
int bMostLeftSensor = A7;
int bLeftSensor = A11;
int bMiddleSensor = A10;
int bRightSensor = A9;
int bMostRightSensor = A8;

// Map Read Sensor

int sensor1 = 17;
int sensor2 = 16;
int sensor3 = 15;
int sensor4 = A13; // Analog pin
int sensor5 = A12; // Analog pin
int sensor6 = 14;
int sensor7 = A15; // Analog pin
int sensor8 = A14; // Analog pin
int sensor9 = 12;
// Sonar Pins
int trigerPin = 50;
int echopin = 51;

// Servo pin
Servo myServo;
int servoPin = 46;

int l_Ticks;
int r_Ticks;

#define r_Encoder 3
#define l_Encoder 2

void ServoRotation(int, int);
void NewLineFolowing();


// For Arena Case
int arenaDirection()
{
  int p1 = digitalRead(dir1);
  int p2 = digitalRead(dir2);
  int p3 = digitalRead(dir3);
  int p4 = digitalRead(dir4);
  if (p1 == 0 && p2 == 1 && p3 == 1 && p4 == 1)
  {
    // Case 1
    return 1;
  }
  else if (p1 == 1 && p2 == 0 && p3 == 1 && p4 == 1)
  {
    return 2;
    // Case 2
  }
  else if (p1 == 1 && p2 == 1 && p3 == 0 && p4 == 1)
  {
    return 3;
    // case 3
  }
  else if (p1 == 1 && p2 == 1 && p3 == 1 && p4 == 0)
  {
    return 4;
    // case 4
  }
  else if (p1 == 0 && p2 == 1 && p3 == 1 && p4 == 0)
  {
    return 5;
    // case 5
  }
  else if (p1 == 1 && p2 == 0 && p3 == 1 && p4 == 0)
  {
    return 6;
    // case 6
  }
  else if (p1 == 1 && p2 == 1 && p3 == 0 && p4 == 0)
  {
    return 7;
    // case 7
  }
  else if (p1 == 0 && p2 == 1 && p3 == 0 && p4 == 0)
  {
    return 8;
    // case 8
  }
  else if (p1 == 1 && p2 == 0 && p3 == 0 && p4 == 0)
  {
    return 9;
    // case 9
  }
  else if (p1 == 0 && p2 == 0 && p3 == 0 && p4 == 0)
  {
    return 10;
    // case 10
  }
  else
    return -1;
}

void FsensorTest()
{
  int fLeftMost = analogRead(fMostLeftSensor);
  int fLeft = analogRead(fLeftSensor);
  int fMiddle = analogRead(fMiddleSensor);
  int fRight = analogRead(fRightSensor);
  int fRightMost = analogRead(fMostRightSensor);

  Serial.print(fLeftMost);
  Serial.print("   ");
  Serial.print(fLeft);
  Serial.print("   ");
  Serial.print(fMiddle);
  Serial.print("   ");
  Serial.print(fRight);
  Serial.print("   ");
  Serial.println(fRightMost);

  delay(100);
}
void BsensorTest()
{
  int bMostLeft = analogRead(bMostLeftSensor);
  int bLeft = analogRead(bLeftSensor);
  int bMiddle = analogRead(bMiddleSensor);
  int bRight = analogRead(bRightSensor);
  int bMostRight = analogRead(bMostRightSensor);

  Serial.print(bMostLeft);
  Serial.print("   ");
  Serial.print(bLeft);
  Serial.print("   ");
  Serial.print(bMiddle);
  Serial.print("   ");
  Serial.print(bRight);
  Serial.print("   ");
  Serial.println(bMostRight);

  delay(100);
}

// Define the base speed for the motors
const int baseSpeed = 150;

// Define the maximum speed for the motors
const int maxSpeed = 255;

// Threshold value for detecting the line
const int threshold = 500;

void LineFollowByChatGPT()
{
  int sensorValues[5];
  sensorValues[0] = analogRead(fMostLeftSensor);
  sensorValues[1] = analogRead(fLeftSensor);
  sensorValues[2] = analogRead(fMiddleSensor);
  sensorValues[3] = analogRead(fRightSensor);
  sensorValues[4] = analogRead(fMostRightSensor);

  // Calculate the error
  int error = 0;
  if (sensorValues[0] > threshold)
    error = -2;
  else if (sensorValues[1] > threshold)
    error = -1;
  else if (sensorValues[2] > threshold)
    error = 0;
  else if (sensorValues[3] > threshold)
    error = 1;
  else if (sensorValues[4] > threshold)
    error = 2;

  // Calculate the motor speeds
  int leftMotorSpeed = baseSpeed + error * 50;
  int rightMotorSpeed = baseSpeed - error * 50;

  // Ensure the motor speeds are within the allowable range
  leftMotorSpeed = constrain(leftMotorSpeed, 0, maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, maxSpeed);

  // Set the motor speeds
  analogWrite(lFSpeed, leftMotorSpeed);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, rightMotorSpeed);
  analogWrite(rBSpeed, 0);
}


int ConvertToDigital(int sensor)
{
  if (analogRead(sensor) < blackMaxValue)
    return sensor = 0;
  else
    return sensor = 1;
}
void MapSensorTest()
{

  Serial.print(!digitalRead(sensor1));
  Serial.print("  ");
  Serial.print(!digitalRead(sensor2));
  Serial.print("  ");
  Serial.print(!digitalRead(sensor3));
  Serial.print("  ");
  Serial.print(!ConvertToDigital(sensor4));
  Serial.print("  ");
  Serial.print(!ConvertToDigital(sensor5));
  Serial.print("  ");
  Serial.print(!digitalRead(sensor6));
  Serial.print("  ");
  Serial.print(!ConvertToDigital(sensor7));
  Serial.print("  ");
  Serial.print(!ConvertToDigital(sensor8));
  Serial.print("  ");
  Serial.print(!digitalRead(sensor9));
  Serial.print("  ");
  Serial.println("");

  delay(100);
}

void Halt()
{
  analogWrite(lBSpeed, 255);
  analogWrite(lFSpeed, 255);

  analogWrite(rFSpeed, 255);
  analogWrite(rBSpeed, 255);
}

void RightTurn()
{
  analogWrite(lBSpeed, turnSpeed);
  analogWrite(lFSpeed, 0);

  analogWrite(rFSpeed, turnSpeed-25);
  analogWrite(rBSpeed, 0);
}

void LeftTurn()
{
  analogWrite(lBSpeed, 0);
  analogWrite(lFSpeed, turnSpeed);

  analogWrite(rFSpeed, 0);
  analogWrite(rBSpeed, turnSpeed);
}
void BRightTurn()
{
  analogWrite(lBSpeed, 0);
  analogWrite(lFSpeed, turnSpeed);

  analogWrite(rFSpeed, 0);
  analogWrite(rBSpeed, turnSpeed);
}

void BLeftTurn()
{
  analogWrite(lBSpeed, turnSpeed);
  analogWrite(lFSpeed, 0);

  analogWrite(rFSpeed, turnSpeed);
  analogWrite(rBSpeed, 0);
  Serial.println(turnSpeed);
}
void Forward()
{

  analogWrite(lFSpeed, motorSpeed);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, motorSpeed);
  analogWrite(rBSpeed, 0);
}

void SlowForward()
{
  analogWrite(lFSpeed, 60);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, 60);
  analogWrite(rBSpeed, 0);
}
void Backward()
{
  analogWrite(lBSpeed, backwardSpeed);
  analogWrite(lFSpeed, 0);

  analogWrite(rBSpeed, backwardSpeed);
  analogWrite(rFSpeed, 0);
}
void SlowBackword(){
   analogWrite(lBSpeed, 0);
  analogWrite(lFSpeed, backwardSpeed);

  analogWrite(rBSpeed, backwardSpeed);
  analogWrite(rFSpeed, 0);
}

bool isBlack(int iSensor)
{
  if (analogRead(iSensor) < blackMaxValue)
    return true;
  return false;
}

bool isWhite(int iSensor)
{
  if (analogRead(iSensor) > blackMaxValue)
    return true;
  return false;
}

bool MapSensorsAreCloseToWall()
{

  if (digitalRead(sensor1) == 0 && ConvertToDigital(sensor4) == 0 && ConvertToDigital(sensor7) == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool AllBlack()
{
  if (isBlack(fMostLeftSensor) && isBlack(fLeftSensor) && isBlack(fMiddleSensor) && isBlack(fRightSensor) && isBlack(fMostRightSensor))
    return true;
  return false;
}

bool AllWhite()
{
  if (isWhite(fMostLeftSensor) && isWhite(fLeftSensor) && isWhite(fMiddleSensor) && isWhite(fRightSensor) && isWhite(fMostRightSensor))
    return true;
  return false;
}

bool BackAllBlack()
{
  if (isBlack(bMostLeftSensor) && isBlack(bLeftSensor) && isBlack(bMiddleSensor) && isBlack(bRightSensor) && isBlack(bMostRightSensor))
    return true;
  return false;
}

void Stop()
{
  Backward();
  delay(50);
  Halt();
}

void SlightRight()
{

  analogWrite(lFSpeed, 0);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, slightTurnSpeed);
  analogWrite(rBSpeed, 0);
}

void SlightLeft()
{
  analogWrite(lFSpeed, slightTurnSpeed);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, 0);
  analogWrite(rBSpeed, 0);
}
void SlightRight2()
{

  analogWrite(lFSpeed, 0);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, slightTurnSpeed);
  analogWrite(rBSpeed, 0);
}

void SlightLeft2()
{
  analogWrite(lFSpeed, slightTurnSpeed);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, 0);
  analogWrite(rBSpeed, 0);
}

void BSlightRight()
{

  analogWrite(lFSpeed, 0);
  analogWrite(lBSpeed, 0);

  analogWrite(rFSpeed, 0);
  analogWrite(rBSpeed, slightTurnSpeed);
}

void BSlightLeft()
{
  analogWrite(lFSpeed, 0);
  analogWrite(lBSpeed, slightTurnSpeed);

  analogWrite(rFSpeed, 0);
  analogWrite(rBSpeed, 0);
}

//============

void ResetTicks()
{
  r_Ticks = 0;
  l_Ticks = 0;
}

void L_EncoderTicks()
{

  l_Ticks++;
  // Serial.print("Left= ");
  // Serial.println(l_Ticks);
}

void R_EncoderTicks()
{
  r_Ticks++;
  // Serial.print("Right= ");
  //  Serial.println(r_Ticks);
}


void LineFolowing()
{
  if (AllBlack())
  {
    Forward();
  }

  if (isWhite(fLeftSensor) && isBlack(fMiddleSensor))
  {
    Forward();
  }

  if (isWhite(fRightSensor) && isBlack(fMiddleSensor))
  {
    Forward();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fRightSensor) && !AllBlack())
  {
    // RightTurn();

    SlightRight();
  }
  else if (isBlack(fRightSensor) && isWhite(fMiddleSensor) && !AllBlack())
  {
    // RightTurn();

    SlightRight();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fLeftSensor) && !AllBlack())
  {
    SlightLeft();
    // LeftTurn();
  }

  else if (isBlack(fLeftSensor) && isWhite(fMiddleSensor) && !AllBlack())
  {
    // LeftTurn();
    SlightLeft();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fLeftSensor))
  {
    SlightLeft();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fRightSensor))
  {
    SlightRight();
  }
  else if (isBlack(fLeftSensor))
  {
    SlightLeft();
  }
  else if (isBlack(fRightSensor))
  {
    SlightRight();
  }

  else if (isBlack(fMostRightSensor))
  {
    SlightRight();
  }

  else if (isBlack(fMostLeftSensor))
  {
    SlightLeft();
  }
  else if (isBlack(fMiddleSensor))
  {
    SlowForward();
  }
  else
  {
    SlowForward();
  }
}

void LineFolowingSlow()
{
  if (AllBlack())
  {
    SlowForward();
  }

  if (isWhite(fLeftSensor) && isBlack(fMiddleSensor))
  {
    SlowForward();
  }

  if (isWhite(fRightSensor) && isBlack(fMiddleSensor))
  {
    SlowForward();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fRightSensor) && !AllBlack())
  {
    // RightTurn();

    SlightRight();
  }
  else if (isBlack(fRightSensor) && isWhite(fMiddleSensor) && !AllBlack())
  {
    // RightTurn();

    SlightRight();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fLeftSensor) && !AllBlack())
  {
    SlightLeft();
    // LeftTurn();
  }

  else if (isBlack(fLeftSensor) && isWhite(fMiddleSensor) && !AllBlack())
  {
    // LeftTurn();
    SlightLeft();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fRightSensor))
  {
    SlightRight();
  }

  else if (isBlack(fMiddleSensor) && isBlack(fLeftSensor))
  {
    SlightLeft();
  }

  else if (isBlack(fRightSensor))
  {
    SlightRight();
  }

  else if (isBlack(fLeftSensor))
  {
    SlightLeft();
  }

  else if (isBlack(fMiddleSensor))
  {
    SlowForward();
  }
}

void BackLineFolowing()
{
  if (BackAllBlack())
  {
    Backward();
  }

  else if (isWhite(bLeftSensor) && isBlack(bMiddleSensor))
  {
    Backward();
  }
  else if(isWhite(bRightSensor)&& isBlack(bMiddleSensor)){
    Backward();

  }

 



  else if (isWhite(bLeftSensor) && isBlack(bMiddleSensor) && isBlack(bRightSensor))
  {
    BSlightRight();
  }

  else if (isBlack(bMiddleSensor) && isBlack(bRightSensor) && !BackAllBlack())
  {
    // RightTurn();
    BSlightRight();
    //    BSlight=Left();
  }
  else if (isBlack(bRightSensor) && isWhite(bMiddleSensor) && !BackAllBlack())
  {

    BSlightRight();
  }

  else if (isBlack(bMiddleSensor) && isBlack(bLeftSensor) && !BackAllBlack())
  {
    BSlightLeft();
    // LeftTurn();
  }

  else if (isBlack(bMostLeftSensor) || isBlack(bLeftSensor))
  {
    BSlightLeft();
  }

  else if (isBlack(bMostRightSensor) || isBlack(bRightSensor))
  {
    BSlightRight();
  }

  else if (isBlack(bLeftSensor))
  {
    BSlightLeft();
  }
  else if (isBlack(bRightSensor))
  {
    BSlightRight();
  }

  else if (isBlack(bMostLeftSensor))
  {
    BSlightLeft();
  }
  else if (isBlack(bMostRightSensor))
  {
    BSlightRight();
  }
}
void SlowBackLineFolowing()
{
  if (BackAllBlack())
  {
    SlowBackword();
  }

  else if (isWhite(bLeftSensor) && isBlack(bMiddleSensor) && isWhite(bRightSensor))
  {
    SlowBackword();
  }

  else if (isBlack(bRightSensor) && isWhite(bMiddleSensor))
  {

    BSlightRight();
  }

  else if (isBlack(bMiddleSensor) && isBlack(bLeftSensor))
  {
    BSlightLeft();
    // LeftTurn();
  }

  else if (isBlack(bMostLeftSensor) || isBlack(bLeftSensor))
  {
    BSlightLeft();
  }

  else if (isBlack(bMostRightSensor) || isBlack(bRightSensor))
  {
    BSlightRight();
  }
}


void NewSlowLineFollowing()
{

if(AllBlack()){
  SlowForward();
}
else if (isBlack(fMiddleSensor) && isWhite(fLeftSensor) && isWhite(fRightSensor))
  {
    SlowForward();
  }
  else if (isWhite(fMiddleSensor) && isBlack(fLeftSensor))
  {
  SlightLeft();
  }
  else if (isBlack(fMiddleSensor) && isBlack(fLeftSensor))
  {
    SlightLeft();
  }
  else if (isBlack(fLeftSensor))
  {
    SlightLeft();
  }
  else if (isBlack(fMostLeftSensor))
  {
    SlightLeft();
  }

  else if (isWhite(fMiddleSensor) && isBlack(fRightSensor))
  {
    SlightRight();
  }
  else if (isBlack(fMiddleSensor) && isBlack(fRightSensor))
  {
    SlightRight();
  }
  else if (isBlack(fRightSensor))
  {
    SlightRight();
  }
  else if (isBlack(fMostRightSensor))
  {
   SlightRight();
  }
  else
  {
    SlowForward();
  }
}
// Case 1: Maybe both left and right middle sensor are on white or black
// If both on black -> move little forward because bot is aligned straght.
// If both on white -> move little forward because bot is aligned straght.
// Case 2: Maybe left-sensor is on black and it has two cases:
// right-middle is on white and (front-left or front-most-left) is on black -> move right motor forward while right-middle reach black line because bot has little angle toward right side
// right-middle is on white and (front-right or front-most-right) is on black move righ motor backword while right-middle reach black line because bot has little angle toward left side
// Case 3: Maybe right-sensor is on black and it has two cases:
// left-middle is on white and (front-left or front-most-left) is on black -> move left-motor backword while left-middle reach black line
// left-middle is on white and (front-right or front-monst-right) is on black -> move left-motor forward while left-middle sensor reach black line
void TurnAdjustment()
{

  while (digitalRead(rightMiddle) == 0 || digitalRead(leftMiddle) == 0)
  {

    if ((digitalRead(rightMiddle) == 0 && digitalRead(leftMiddle) == 0))
    {
      // Both middle sensors are either on white or black
      // Move forward as the bot is aligned straight
      NewSlowLineFollowing();
    }

    else if (digitalRead(rightMiddle) == 0 && digitalRead(leftMiddle) == 1) {
      // Right middle sensor is on white
   if (isBlack(fLeftSensor) || isBlack(fMostLeftSensor)) {
        // Front left sensors are on black
        // Move right motor backward to correct the angle
        analogWrite(lFSpeed, 0);
        analogWrite(lBSpeed, 0);
        analogWrite(rFSpeed, 0);
        analogWrite(rBSpeed, 60);
      }
    } else if (digitalRead(rightMiddle) == 1 && digitalRead(leftMiddle) == 0) {
      // Left middle sensor is on white
      if (isBlack(fRightSensor) || isBlack(fMostRightSensor)) {
        // Front right sensors are on black
        // Move left motor backward to correct the angle
        analogWrite(lFSpeed, 0);
        analogWrite(lBSpeed, 60);
        analogWrite(rFSpeed, 0);
        analogWrite(rBSpeed, 0);
      
      } 
      }     
  }
}
  

void EncoderLeftTurn()
{
  ResetTicks();
  while (l_Ticks < 235)
  {
    LeftTurn();
    Serial.println(l_Ticks);
  }

  while (digitalRead(leftMiddle) != 0 && digitalRead(rightMiddle) != 0)
  {
    LeftTurn();
  }
  while (isWhite(fMiddleSensor) && !isWhite(fRightSensor) && !isWhite(fLeftSensor))
  {

    LeftTurn();
  }

  while (digitalRead(rightMiddle) == 0 && digitalRead(leftMiddle) == 0 && isWhite(fMiddleSensor) && isWhite(bMiddleSensor) && isWhite(fLeftSensor))
  {
    LeftTurn();
  }

  TurnAdjustment();
Halt();
delay(50);

}
void EncoderRightTurn()
{
  ResetTicks();
  while (l_Ticks < 235)
  {
    RightTurn();
    Serial.println(l_Ticks);
  }
  Serial.println("Exit From Left Encoder");

  while (digitalRead(leftMiddle) != 0 && digitalRead(rightMiddle) != 0)
  {
    RightTurn();
  }
  while (digitalRead(rightMiddle) == 0 && digitalRead(leftMiddle) == 0 && isWhite(fMiddleSensor) && isWhite(bMiddleSensor) && isWhite(fRightSensor))
  {
    RightTurn();
  }

  TurnAdjustment();
  Halt();
  delay(1000);
}

void EncoderTurnAround()
{
  ResetTicks();
  while (l_Ticks < 470)
  {
    LeftTurn();
    Serial.println(l_Ticks);
  }

  while (digitalRead(leftMiddle) != 0 && digitalRead(rightMiddle) != 0)
  {
    LeftTurn();
  }
  while (isWhite(fMiddleSensor) && !isWhite(fRightSensor) && !isWhite(fLeftSensor))
  {

    LeftTurn();
  }

  while (digitalRead(rightMiddle) == 0 && digitalRead(leftMiddle) == 0 && isWhite(fMiddleSensor) && isWhite(bMiddleSensor) && isWhite(fLeftSensor))
  {
    LeftTurn();
  }

  TurnAdjustment();
}

void EncoderLeftTurn_Adjust()
{

  ResetTicks();
  while (l_Ticks < 235)
  {
    LeftTurn();
    Serial.println(l_Ticks);
  }

  while (digitalRead(leftMiddle) != 0 && digitalRead(rightMiddle) != 0)
  {
    LeftTurn();
  }
  while (isWhite(fMiddleSensor) && !isWhite(fRightSensor) && !isWhite(fLeftSensor))
  {

    LeftTurn();
  }

  while (digitalRead(rightMiddle) == 0 && digitalRead(leftMiddle) == 0 && isWhite(fMiddleSensor) && isWhite(bMiddleSensor) && isWhite(fLeftSensor))
  {
    LeftTurn();
  }

  Halt();
  delay(200);

  TurnAdjustment();
}

void Align()
{
}

void ightTurn()
{
  ResetTicks();
  while (l_Ticks < 235)
  {
    RightTurn();
    Serial.println(l_Ticks);
  }

  while (digitalRead(leftMiddle) != 0 && digitalRead(rightMiddle) != 0)
  {
    RightTurn();
  }
  while (isWhite(fMiddleSensor) && !isWhite(fRightSensor) && !isWhite(fLeftSensor))
  {
    RightTurn();
  }
  while (digitalRead(rightMiddle) == 0 && digitalRead(leftMiddle) == 0 && isWhite(fMiddleSensor) && isWhite(bMiddleSensor) && isWhite(fRightSensor))
  {
    RightTurn();
  }

  Halt();
}

void SensorRead()
{
  Serial.print(analogRead(fMostLeftSensor));
  Serial.print("  ");
  Serial.print(analogRead(fLeftSensor));
  Serial.print("  ");

  Serial.print(analogRead(fMiddleSensor));
  Serial.print("  ");

  Serial.print(analogRead(fRightSensor));
  Serial.print("  ");

  Serial.println(analogRead(fMostRightSensor));
}

bool DigitalIsBlack(int iSensor)
{
  if (digitalRead(iSensor) == 1)
    return true;
  return false;
}

void PrintMiddleSensorValues()
{
  Serial.print("Left");
  Serial.print(DigitalIsBlack(leftMiddle));

  Serial.print("Right");
  Serial.print(DigitalIsBlack(rightMiddle));

  Serial.println("");
}

void StripForward(int iCount, bool useHalt = false)
{
  int stripCount = 0;

  while (stripCount < iCount)
  {

    if (!DigitalIsBlack(leftMiddle || !DigitalIsBlack(rightMiddle)))
    {
      while (!DigitalIsBlack(leftMiddle) || !DigitalIsBlack(rightMiddle))
      {
        NewLineFolowing();
      }

      while (DigitalIsBlack(leftMiddle) || DigitalIsBlack(rightMiddle))
      {
        NewLineFolowing();
      }
    }

    else if (DigitalIsBlack(leftMiddle) || DigitalIsBlack(rightMiddle))
    {
      while (DigitalIsBlack(leftMiddle) || DigitalIsBlack(rightMiddle))
      {
        NewLineFolowing();
      }
      while (!DigitalIsBlack(leftMiddle) || !DigitalIsBlack(rightMiddle))
      {
        NewLineFolowing();
      }
    }

    stripCount++;
  }

  if (useHalt)
  {
    Serial.println("Using halt becuase second next step is turn");
    Halt();
    delay(1000);
  }
}

void StripBackward(int iCount, bool useHalt)
{
  int stripCount = 0;

  while (stripCount < iCount)
  {

    while (!DigitalIsBlack(leftMiddle) || !DigitalIsBlack(rightMiddle))
    {
      BackLineFolowing();
    }

    while (DigitalIsBlack(leftMiddle) || DigitalIsBlack(rightMiddle))
    {
      BackLineFolowing();
    }

    stripCount++;
  }

  if (useHalt)
  {
    Halt();
    delay(1000);
  }
}

void Code()
{
}

int xPos = 0, yPos = 0;
enum Orientation
{
  ForwardLooking,
  LeftLooking,
  RightLooking,
  BackwordLooking
};

Orientation _orientation = ForwardLooking;

// int myPos[1][2]= {0,0};
// int targetPos[1][2] = {0,0};

int nextX, nextY;
int secondNextX, secondNextY;
int myPosX = 0, myPosY = 0;

int currentPathPointIndex = 1; // for find path should be reset to 1 after use

int currentPickupItemIndex = 0; // which  pickup item to pick

bool isSecondNextNodeIsTurn()
{
  bool result = false;
  if (_orientation == ForwardLooking)
  {

    if (secondNextY == 1)
    {
      result = true;
    }
    else if (secondNextY == -1)
    {
      result = true;
    }
  }

  else if (_orientation == LeftLooking)
  {
    if (secondNextX == 1)
    {

      result = true;
    }

    else if (secondNextX == -1)
    {
      result = true;
    }
  }

  else if (_orientation == RightLooking)
  {
    if (secondNextX == 1)
    {

      result = true;
    }

    else if (secondNextX == -1)
    {
      result = true;
    }
  }

  return result;
}



void ServoRotation(int iStart, int iTarget, int Idelay)
{
  if (iStart < iTarget)
  {

    for (int i = iStart; i <= iTarget; i++)
    {

      myServo.write(i);
      servoRotation = i;
      delay(Idelay);
    }
  }
  else
  {

    for (int i = iStart; i >= iTarget; i--)
    {

      myServo.write(i);
      servoRotation = i;
      delay(Idelay);
    }
  }


  // ResetTicks();
  // while (l_Ticks < 170)
  // {
  //   Serial.println(l_Ticks);
  //   LineFolowing();
  // }
  // while (DigitalIsBlack(rightMiddle) == 1)
  // {
  //   LineFolowing();
  // }
}

void ReadMapAndGotoGridStart()
{
  delay(1000);
  StripForward(2);
  Halt();
  delay(2000);
  EncoderLeftTurn();
  delay(1000);
  while (!MapSensorsAreCloseToWall())
  {
    BackLineFolowing();
  }
  Halt();
  delay(500);
  
  delay(1000);

  MapSensorTest();
  // ReadMapAndGotoGridStart();

  delay(1000);
  StripForward(1, false);
  Halt();
  delay(1000);
  ightTurn();
  delay(1000);
  StripForward(2);
  Halt();
  delay(1000);
  EncoderLeftTurn();
  Halt();
}


void PickTree()
{

  while (isWhite(fLeftSensor) || isWhite(fRightSensor))
  {
    SlowBackLineFolowing();
  }
  Halt();

  // ServoRotation(servoRotation, 20);
  delay(500);

  while (isWhite(bLeftSensor) || isWhite(bRightSensor))
  {
    NewSlowLineFollowing();
  }
  Halt();
  // ServoRotation(servoRotation, 90);
}

void LineFollowBackWithTicks(int ticks)
{
  ResetTicks();
  while (l_Ticks < ticks)
  {
    BackLineFolowing();
  }
  Halt();
}

void LineFollowkWithTicks(int ticks)
{
  ResetTicks();
  while (l_Ticks < ticks)
  {
    LineFolowing();
  }
  Halt();
}

void NewLineFolowing()
{
  if (AllBlack())
  {
    Forward();
  }
  else if (isBlack(fMiddleSensor))
  {
    Forward();
  }
  else if (isWhite(fLeftSensor) && isBlack(fMiddleSensor))
  {
    Forward();
  }
  else if (isWhite(fRightSensor) && isBlack(fMiddleSensor))
  {
    Forward();
  }
  else if (isWhite(fMiddleSensor) && isBlack(fLeftSensor))
  {
    SlightLeft();
  }
  else if (isBlack(fMiddleSensor) && isBlack(fLeftSensor))
  {
    SlightLeft();
  }
  else if (isBlack(fLeftSensor))
  {
    SlightLeft();
  }
  else if (isBlack(fMostLeftSensor))
  {
    SlightLeft();
  }

  else if (isWhite(fMiddleSensor) && isBlack(fRightSensor))
  {
    SlightRight();
  }
  else if (isBlack(fMiddleSensor) && isBlack(fRightSensor))
  {
    SlightRight();
  }
  else if (isBlack(fRightSensor))
  {
    SlightRight();
  }
  else if (isBlack(fMostRightSensor))
  {
    SlightRight();
  }
}

void treePickup()
{  
  while(!AllBlack()){
    if((isBlack(leftMiddle) && isBlack(rightMiddle)) || (isBlack(fMiddleSensor) && isBlack(bMiddleSensor))){
return;
    }
    SlowBackLineFolowing();
  }
   Halt();
  delay(300);
  if(myServo.read()!=0){
  ServoRotation(75, 0, 5); // Pickup
  }
  Halt();
  delay(300);

  while (!BackAllBlack())
  {
    NewSlowLineFollowing();
  }

  Halt();
  delay(100);
  ServoRotation(0, 75, 5); // Pickup
  Halt();
  delay(100);
}

void treeDrop()
{
  while (!BackAllBlack())
  {
    NewSlowLineFollowing();
  }
  Halt();
  delay(100);
  ServoRotation(75, 0, 20); // Drop
  delay(100);
}

void setup()
{

  // motorDifference = (percentage / 100) * motorSpeed;

  pinMode(l_Encoder, INPUT_PULLUP);

  pinMode(r_Encoder, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(l_Encoder), L_EncoderTicks, RISING);
  attachInterrupt(digitalPinToInterrupt(r_Encoder), R_EncoderTicks, RISING);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
  pinMode(sensor7, INPUT);
  pinMode(sensor8, INPUT);
  pinMode(sensor9, INPUT);
  pinMode(lFSpeed, OUTPUT);
  pinMode(lBSpeed, OUTPUT);
  pinMode(rFSpeed, OUTPUT);
  pinMode(rBSpeed, OUTPUT);
  pinMode(fMostLeftSensor, INPUT);
  pinMode(fLeftSensor, INPUT);
  pinMode(fMiddleSensor, INPUT);
  pinMode(fRightSensor, INPUT);
  pinMode(fMostRightSensor, INPUT);
  pinMode(bMostLeftSensor, INPUT);
  pinMode(bLeftSensor, INPUT);
  pinMode(bMiddleSensor, INPUT);
  pinMode(bRightSensor, INPUT);
  pinMode(bMostRightSensor, INPUT);
  pinMode(rightMiddle, INPUT);
  pinMode(leftMiddle, INPUT);
  pinMode(dir1, INPUT_PULLUP);
  pinMode(dir2, INPUT_PULLUP);
  pinMode(dir3, INPUT_PULLUP);
  pinMode(dir4, INPUT_PULLUP);
  pinMode(changeArena, INPUT_PULLUP);

  Serial.begin(9600);

  myServo.write(0);
  myServo.attach(servoPin);
  myServo.write(180);

  int arenaColor = digitalRead(changeArena);

  int mapnumber = 2;
  // for storing map no

  if (arenaColor == 0)
  {
    // ForBlueSide of Arena

    switch (arenaDirection())
    {
    case 1:
    {
      //   0   0   1
      //   0   1   0
      //   1   0   0

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(5, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 5 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treeDrop();

      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (5,1) drop

      StripBackward(3, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (5,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderLeftTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (3,3)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(2, true);

      treeDrop();

      //======= Reach Point (3,3)

      //======= Going Towards (final)

      StripBackward(3, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }

    case 2:
    {
      //   1   0   0
      //   0   1   0
      //   0   0   1

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(3, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      //======= Reach Point (3,1)
      //======= Going Towards (7,0)
      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(3, true);
      treeDrop();

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (3,1)

      StripBackward(5, true);

      treeDrop(); // drop
      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      Forward();
      delay(100);
      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (5,3)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop();

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop();

      //======= Reach Point (7,3)

      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }

    case 3:
    {
      //   1   1   1
      //   0   0   0
      //   0   0   0

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(5, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 5 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (5,1) drop

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (5,1)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (5,2)

      //======= Going Towards (7,1)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop(); // drop

      //======= Reach Point (5,2)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (5,3)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderLeftTurn();

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop();

      //======= Reach Point (5,3)

      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }

    case 4:
    {
      //   0   1   0
      //   1   0   1
      //   0   0   0

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(4, true);
      EncoderLeftTurn();

   
      Halt();
      delay(1000);
      treePickup();
      // Reaching at point 4 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(2, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,1) drop

      StripBackward(4, true);
      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (4,1)

      //======= Going Towards (5,2)

      StripBackward(1, true); // change
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (5,2)

      //======= Going Towards (7,1)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (5,2)

      StripBackward(3, true);
      treeDrop(); // drop

      //======= Reach Point (5,2)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (4,3)

      //======= Going Towards (7,2)
      StripForward(1, true); // changed
      EncoderRightTurn();
      StripForward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(1, true);

      treeDrop();

      //======= Reach Point (5,3)

      //======= Going Towards (final)
      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }
    case 5:
    {
      //   0   0   0
      //   0   1   0
      //   1   0   1
      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(3, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 3 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(3, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (3,1) drop

      StripBackward(5, true);
      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      // StripForward(1, true);
      treePickup(); // pickup

      //======= Reach Point (3,3)

      //======= Going Towards (7,2)
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(3, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(2, true);

      treeDrop();

      //======= Reach Point (3,3)

      //======= Going Towards (final)
      StripBackward(3, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }

    case 6:
    {
      //   0   0   0
      //   1   1   1
      //   0   0   0

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(4, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 4 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(2, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,1)

      StripBackward(4, true);
      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (4,2)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      Forward();
      delay(100);

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (4,3)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (4,3)

      //======= Going Towards (7,2)

      StripForward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      StripForward(1, true);
      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(1, true);

      treeDrop();

      //======= Reach Point (4,3)

      //======= Going Towards (final)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }

    case 7:
    {
      //   0   1   0
      //   0   1   1
      //   0   0   0

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(4, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 4 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(2, true);
      treeDrop();

      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,1) drop

      StripBackward(4, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (4,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(2, true);
      EncoderRightTurn();
      StripForward(2, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup();

      //======= Reach Point (5,2)

      //======= Going Towards (7,2)
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treeDrop();

      //======= Reach Point (5,2)
      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(4, true);
      break;
    }

    case 8:
    {
      //   1   0   1
      //   0   0   0
      //   0   1   0

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(5, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 3 , 2
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treeDrop();

      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (5,1) drop

      StripBackward(3, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (5,1)

      //======= Going Towards (3,2)

      StripBackward(2, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (3,2)

      //======= Going Towards (7,1)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(3, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (3,2)

      StripBackward(5, true);
      treeDrop(); // drop

      //======= Reach Point (3,2)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(2, true);
      treePickup();

      //======= Reach Point (5,3)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();
      treeDrop();

      //======= Reach Point (5,3)
      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }

    case 9:
    {
      //   0   1   0
      //   0   0   0
      //   1   0   1

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(3, true);
      EncoderLeftTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 3 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(3, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (3,1) drop

      StripBackward(5, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripBackward(2, true);
      EncoderRightTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (3,2)

      //======= Going Towards (7,1)

      StripForward(2, true);
      EncoderRightTurn();
      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(2, true);
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);

      treeDrop(); // drop

      //======= Reach Point (3,3)

      //======= Going Towards (5,2)

      StripBackward(2, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (5,2)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treeDrop();

      //======= Reach Point (5,2)

      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(4, true);
      break;
    }

    case 10:
    {
      //   0   1   0
      //   1   1   0
      //   0   0   0

      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(4, true);
      EncoderLeftTurn();
      StripForward(1, true);

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 4 , 2
      // going towards point 7, 0

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(2, true);
      treeDrop();

      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,2) drop

      StripBackward(3, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (4,2)

      //======= Going Towards (5,2)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup(); // pickup

      //======= Reach Point (5,2)

      //======= Going Towards (7,1)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderTurnAround();
      treeDrop(); // drop

      //======= Reach Point (5,2)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (4,3)

      //======= Going Towards (7,2)
      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(1, true);
      treeDrop();

      //======= Reach Point (4,3)
      //======= Going Towards (final)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(5, true);
      break;
    }
    default:
      break;
    }
  }
  else // ForRedSide
  {
    switch (arenaDirection())
    {
    case 1:
    {
      //   0   0   1
      //   0   1   0
      //   1   0   0
      StripForward(4, true);
      EncoderRightTurn();
      StripForward(5, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 5 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (5,1) drop

      StripBackward(3, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (5,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (3,3)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(2, true);

      treeDrop();

      //======= Reach Point (3,3)

      //======= Going Towards (final)

      StripBackward(3, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
    }

    case 2:
    {
      //   1   0   0
      //   0   1   0
      //   0   0   1

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(3, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 5 , 0
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(3, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,5)

      //======= Going Towards (7,4)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,0)

      //======= Going Towards (3,1)

      StripBackward(5, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      Forward();
      delay(100);

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();

      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (5,3)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();
      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop();

      //======= Reach Point (7,3)

      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
    }

    case 3:
    {
      //   1   1   1
      //   0   0   0
      //   0   0   0

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(5, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 5 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (5,1) drop

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (5,1)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (5,2)

      //======= Going Towards (7,1)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop(); // drop

      //======= Reach Point (5,2)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treePickup(); // pickup

      //======= Reach Point (5,3)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderRightTurn();

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();

      treeDrop();

      //======= Reach Point (5,3)

      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
    }

    case 4:
    {
      //   0   1   0
      //   1   0   1
      //   0   0   0

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(4, true);
      EncoderRightTurn();

      Halt();
      delay(1000);
      treePickup();
      // Reaching at point 4 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,1) drop

      StripBackward(4, true);
      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (4,1)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (5,2)

      //======= Going Towards (7,1)
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (5,2)

      StripBackward(3, true);
      treeDrop(); // drop

      //======= Reach Point (5,2)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (4,3)

      //======= Going Towards (7,2)
      StripForward(1, true);

      EncoderLeftTurn();
      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(1, true);

      treeDrop();

      //======= Reach Point (5,3)

      //======= Going Towards (final)
      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
      
    }
    case 5:
    {
      //   0   0   0
      //   0   1   0
      //   1   0   1
      StripForward(4, true);
      EncoderRightTurn();
      StripForward(3, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 3 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(3, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (3,1) drop

      StripBackward(5, true);
      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)
      StripForward(1, true);

      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(2, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup(); // pickup

      //======= Reach Point (3,3)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(3, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(2, true);

      treeDrop();

      //======= Reach Point (3,3)

      //======= Going Towards (final)
      StripBackward(3, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
    }

    case 6:
    {
      //   0   0   0
      //   1   1   1
      //   0   0   0

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(4, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 4 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,1)

      StripBackward(4, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (4,2)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      Forward();
      delay(100);

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripBackward(4, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (4,3)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();

      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (4,3)

      //======= Going Towards (7,2)

      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();
      StripForward(1, true);

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(1, true);

      treeDrop();

      //======= Reach Point (4,3)

      //======= Going Towards (final)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
    }

    case 7:
    {
      //   0   1   0
      //   0   1   1
      //   0   0   0

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(4, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 4 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);
      treeDrop();

      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,1) drop

      StripBackward(4, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (4,1)

      //======= Going Towards (4,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (4,2)

      //======= Going Towards (7,1)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(2, true);
      EncoderRightTurn();
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (4,2)

      StripForward(2, true);
      EncoderRightTurn();
      StripForward(2, true);
      EncoderRightTurn();
      StripForward(4, true);
      EncoderRightTurn();
      StripForward(1, true);
      treeDrop(); // drop

      //======= Reach Point (4,2)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup();

      //======= Reach Point (5,2)

      //======= Going Towards (7,2)
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treeDrop();

      //======= Reach Point (5,2)
      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(4, true);
      break;
    }

    case 8:
    {
      //   1   0   1
      //   0   0   0
      //   0   1   0

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(5, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 3 , 2
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treeDrop();

      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (5,1) drop

      StripBackward(3, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (5,1)

      //======= Going Towards (3,2)

      StripBackward(2, true);
      EncoderRightTurn();
      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (3,2)

      //======= Going Towards (7,1)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(3, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (3,2)

      StripBackward(5, true);
      treeDrop(); // drop

      //======= Reach Point (3,2)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(2, true);
      treePickup();

      //======= Reach Point (5,3)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,3)

      StripBackward(1, true);
      EncoderTurnAround();
      treeDrop();

      //======= Reach Point (5,3)
      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
    }

    case 9:
    {
      //   0   1   0
      //   0   0   0
      //   1   0   1

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(3, true);
      EncoderRightTurn();

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 3 , 1
      // going towards point 7, 0

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(3, true);
      treeDrop();
      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (3,1) drop

      StripBackward(5, true);

      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (3,1)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripBackward(2, true);
      EncoderLeftTurn();

      treePickup(); // pickup

      // second tree picked
      //======= Reach Point (3,2)

      //======= Going Towards (7,1)

      StripForward(2, true);
      EncoderLeftTurn();
      StripForward(2, true);
      EncoderRightTurn();
      StripForward(2, true);
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (3,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(2, true);

      treeDrop(); // drop

      //======= Reach Point (3,3)

      //======= Going Towards (5,2)

      StripBackward(2, true);
      EncoderRightTurn();
      treePickup(); // pickup

      //======= Reach Point (5,2)

      //======= Going Towards (7,2)

      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderLeftTurn();

      treeDrop();

      //======= Reach Point (5,2)

      //======= Going Towards (final)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(4, true);
      break;
    }

    case 10:
    {
      //   0   1   0
      //   1   1   0
      //   0   0   0

      StripForward(4, true);
      EncoderRightTurn();
      StripForward(4, true);
      EncoderRightTurn();
      StripForward(1, true);

      while (isWhite(fLeftSensor) || isWhite(fRightSensor))
      {
        Backward();
      }
      Halt();
      delay(100);
      ServoRotation(180, 0, 5);
      delay(100);
      treePickup();
      // Reaching at point 4 , 2
      // going towards point 7, 0

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(2, true);
      treeDrop();

      //=======tree 1 dropped

      //======= Reach Point (7,0)

      //======= Going Towards (7,1)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (7,1)

      //======= Going Towards (4,2) drop

      StripBackward(3, true);
      EncoderRightTurn();
      treeDrop(); // drop

      // towards second tree
      //======= Reach Point (4,2)

      //======= Going Towards (5,2)

      StripBackward(2, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup(); // pickup

      //======= Reach Point (5,2)

      //======= Going Towards (7,1)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treeDrop(); // drop

      //======= Reach Point (7,1)

      //======= Going Towards (7,2)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      treePickup(); // pickup

      //======= Reach Point (7,2)

      //======= Going Towards (5,2)

      StripBackward(1, true);
      EncoderTurnAround();
      treeDrop(); // drop

      //======= Reach Point (5,2)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderLeftTurn();
      StripForward(1, true);
      EncoderRightTurn();
      StripForward(1, true);
      treePickup();

      //======= Reach Point (4,3)

      //======= Going Towards (7,2)
      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(1, true);
      EncoderRightTurn();
      treeDrop(); // drop

      //======= Reach Point (7,2)

      //======= Going Towards (7,3)

      StripBackward(1, true);
      EncoderRightTurn();
      StripForward(1, true);

      EncoderLeftTurn();

      treePickup(); // pickup

      //======= Reach Point (7,3)

      //======= Going Towards (4,3)

      StripBackward(1, true);
      EncoderTurnAround();
      StripForward(1, true);
      treeDrop();

      //======= Reach Point (4,3)
      //======= Going Towards (final)

      StripBackward(2, true);
      EncoderRightTurn();
      StripForward(5, true);
      break;
    }
    default:
      break;
    }
  }
}

void SwitchValue_Test()
{
  Serial.print(digitalRead(dir1));
  Serial.print("  ");
  Serial.print(digitalRead(dir2));
  Serial.print("  ");
  Serial.print(digitalRead(dir3));
  Serial.print("  ");
  Serial.print(digitalRead(dir4));
  Serial.print("  ");
  Serial.print(digitalRead(dir4));
  Serial.print("   Arena Switch       ");
  Serial.println(digitalRead(changeArena));
}
void loop()
{
  // SwitchValue_Test();
  //  NewLineFolowing();

  // SwitchValue_Test();
  // Serial.print("Arena Number is: ");

  // Serial.println(arenaDirection());
  // Serial.print(digitalRead(leftMiddle));   // 1 on bla
}
