#include <Arduino.h>
#include <Servo.h>
#include "Config.h"
#include "Motor.h"
#include "Sensor.h"
#include "IBTMotor.h"
#include <TimerOne.h>


////////////////////////
// Global Variables
////////////////////////
int distance = 0;

// // motors
Motor leftMotor(8, 9 ,10);
Motor rightMotor(5, 7, 6);

// IBTMotor leftMotor(10, 9);
// IBTMotor rightMotor(6, 5);
// sensors
Sensor frontSensors[] = {
  Sensor(ANALOG, A4),
  Sensor(ANALOG, A6),
  Sensor(ANALOG, A3),
  Sensor(ANALOG, A7),
  Sensor(ANALOG, A5)
};

Sensor backSensors[] = {
  Sensor(ANALOG, A9),
  Sensor(ANALOG, A8),
  Sensor(ANALOG, A10),
  Sensor(ANALOG, A1),
  Sensor(ANALOG, A2)
};

Sensor leftMiddleSensor(DIGITAL, leftMiddleSensorPin);
Sensor rightMiddleSensor(DIGITAL, rightMiddleSensorPin);

// speed control
int leftSpeed = 25;
int rightSpeed = 25;

// turns speed
int leftTurnSpeed = 25;
int rightTurnSpeed = 25;

// turn speed
int turnSpeed = 35;
// int leftEncoderTurnSpeed = 130;
// int rightEncoderTurnSpeed = 150;
// int leftEncoderTurnSpeed = 150;
// int rightEncoderTurnSpeed = 130;

// Encoder
int leftEncoderTicks = 0;
int rightEncoderTicks = 0;
int leftEncoder90 = 320;
int rightEncoder90 = 300;

// Servo
int servoUpPoint = 150;
int servoPickPoint = 90;
int servoDownPoint = 7;

Servo myservo;

int readDipSwitch();

void printSensorValues();
// prototypes
void lineFollow(int &currentCounter, int targetCounter ,int lm, int l, int m, int r, int rm);
void forward(int untilCount);
void lineFollowUntilSensorsInMiddle();
void lineFollowBackwardUntilSensorsInMiddle();
void lineFollowBackwardUntilFrontArrayAllBlack();
void lineFollowForwardUntilBackArrayAllBlack();

void lineFollowBackward(int &currentCounter, int targetCounter, int lm, int l, int r, int rm);
void backward(int untilCount);

// Turns
void forwardWithoutSensors();
void forwardWithoutSensors(int);
void backwardWithoutSensors();
void backwardWithoutSensors(int speed);
void halt();
void leftWithoutSensors(int speed);
void rightWithoutSensors(int speed);
void right90WithoutSensors(int speed);
void left90WithoutSensors(int speed);
void left();
void right();
void rightBackward();
void leftBackward();
void forwardMiddleSensors();

// encoder functions
void LencodeFunc();
void RencodeFunc();
void encoderLeft(int value);
void encoderRight(int value);
void encoderForward(int value);
void encoderForward(int value, int speed);
void encoderBackward(int value);
void encoder180();

// Sonar
void detectObject(int detectionDistance);
void pickupObject();
void dropObject();
void triggerSonar();

// servo
void moveServo(int startAngle, int endAngle);
void downServo();
void downServoSlow();
void upServo();
void pickUpServo();


// Arena code
void grid1_blue();
void grid2_blue();
void grid3_blue();
void grid4_blue();
void grid5_blue();
void grid6_blue();
void grid7_blue();
void grid8_blue();
void grid9_blue();
void grid10_blue();

void grid1_red();
void grid2_red();
void grid3_red();
void grid4_red();
void grid5_red();
void grid6_red();
void grid7_red();
void grid8_red();
void grid9_red();
void grid10_red();

void blueArena();
void redArena();


void setup() {
  Serial.begin(9600);

  // attach encoder interrupts
  attachInterrupt(digitalPinToInterrupt(leftEncoderPin), LencodeFunc, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPin), RencodeFunc, RISING);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(dipSwitchPin1, INPUT_PULLUP);
  pinMode(dipSwitchPin2, INPUT_PULLUP);
  pinMode(dipSwitchPin4, INPUT_PULLUP);
  pinMode(dipSwitchPin8, INPUT_PULLUP);

  redArena();
  // blueArena();
}

void loop() {
  int val = readDipSwitch();
  Serial.println(val);
  // Serial.print(rightMiddleSensor.getValue());
  // Serial.print(" ");
  // Serial.print(leftMiddleSensor.getValue());
  // Serial.print(" -> ");
  
  // printSensorValues();
}

//////////////////////////////////////
//           Functions
//////////////////////////////////////

//////////////////
// blue arena
//////////////////

void blueArena() {
  int val = readDipSwitch();
  switch (val) {
    case 1:
      grid1_blue();
      break;
    case 2:
      grid2_blue();
      break;
    case 3:
      grid3_blue();
      break;
    case 4:
      grid4_blue();
      break;
    case 5:
      grid5_blue();
      break;
    case 6:
      grid6_blue();
      break;
    case 7:
      grid7_blue();
      break;
    case 8:
      grid8_blue();
      break;
    case 9:
      grid9_blue();
      break;
    case 10:
      grid10_blue();
      break;
    default:
      break;
  }
}

void redArena() {
  int val = readDipSwitch();
  switch (val) {
    case 1:
      grid1_red();
      break;
    case 2:
      grid2_red();
      break;
    case 3:
      grid3_red();
      break;
    case 4:
      grid4_red();
      break;
    case 5:
      grid5_red();
      break;
    case 6:
      grid6_red();
      break;
    case 7:
      grid7_red();
      break;
    case 8:
      grid8_red();
      break;
    case 9:
      grid9_red();
      break;
    case 10:
      grid10_red();
      break;
    default:
      break;
  }

}

void grid1_blue() {
  // 0 0 1
  // 0 1 0
  // 1 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();
  forward(3);
  left();

  // pick the rock
  pickupObject();
  
  right();
  forward(3);

  // place the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(4);
  lineFollowBackwardUntilFrontArrayAllBlack();
  dropObject();  

  // go to second rock
  left();
  
  forward(1);
  right();
  forward(1);

  // pick the 2nd rock
  pickupObject();

  // go to 2nd empty position
  lineFollowUntilSensorsInMiddle();
  forward(3);
  right();
  forward(1);
  left();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  // drop 2nd tree
  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();
  dropObject(); // front array all black

  // go to 3rd rock
  left();
  forward(1);
  right();
  forward(1);

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(2);
  right();
  forward(1);
  left();
  
  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();

  // pick the 3rd tree
  pickupObject();

  // drop 3rd tree
  left(); 
  encoderBackward(30);
  lineFollowUntilSensorsInMiddle();
  encoderLeft(290);  

  dropObject();

  // go to parking
  left();
  forward(4);
  encoderForward(400);
}

void grid2_blue() {
  // 1 0 0
  // 0 1 0
  // 0 0 1

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();  
  forward(3);
  left();
  forward(2);

  // pick the rock
  pickupObject();
  
  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // place the rock at 1st position
  right();
  forward(3);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  left();
  forward(2);
  left();
  forward(2);

  dropObject();  

  // go to second rock
  left();
  pickupObject();

  // go to 2nd empty position
  forward(1);
  left();
  forward(2);
  right();
  forward(1);
  left();

  
  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();
  forward(1);
  left();
  forward(1);

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  left();
  forward(1);
  right();
  forward(1);

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  pickupObject();

  // drop 3rd tree
  right();
  forward(2);
  right();

  dropObject();

  // go to parking
  left();
  forward(2);
  encoderForward(400);
}

void grid3_blue() {
  // 1 1 1
  // 0 0 0
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();  
  forward(5);
  left();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  right();
  forward(1);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(2);

  dropObject();  

  // go to second rock
  left();
  forward(1);
  right();

  pickupObject();

  // go to 2nd empty position
  forward(2);
  right();
  forward(1);
  left();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();
  forward(1);
  right();
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(2);
  right();
  forward(1);
  left();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  backward(2);
  
  dropObject();

  // go to parking
  left();
  forward(1);
  right();
  forward(2);
  right();
  forward(5);
  encoderForward(400); 
}

void grid4_blue() {
  // 0 1 0
  // 1 0 1
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();  
  forward(4);
  left();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  right();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);

  dropObject();  

  // go to second rock
  left();
  forward(1);
  right();
  forward(1);

  pickupObject();

  // go to 2nd empty position
  forward(2);
  right();
  forward(1);
  left();
  
  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  right();
  forward(2);
  right();
  forward(1);
  left();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  backward(3);
  
  dropObject();

  // go to parking
  left();
  forward(1);
  right();
  forward(3);
  right();
  forward(5);
  encoderForward(400);

}

void grid5_blue() {
  // 0 0 0
  // 0 1 0
  // 1 0 1

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();  
  forward(3);
  left();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  right();
  forward(3);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(4);

  dropObject();  

  // go to second rock
  left();
  forward(1);
  right();
  forward(1);

  pickupObject();

  // go to 2nd empty position
  forward(2);
  right();
  forward(1);
  left();
  forward(1);
  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  right();
  forward(2);
  right();
  forward(1);
  left();
  forward(1);

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  backward(4);
  
  dropObject();

  // go to parking
  left();
  forward(1);
  right();
  forward(4);
  right();
  forward(5);
  encoderForward(400); 
}

void grid6_blue() {
  // 0 0 0
  // 1 1 1
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();  
  forward(4);
  left();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  right();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);

  dropObject();  

  // go to second rock
  left();
  forward(1);
  right();

  pickupObject();

  // go to 2nd empty position
  forward(3);
  right();
  forward(1);
  left();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();
  forward(1);
  right();
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(3);
  right();
  forward(1);
  left();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  backward(3);
  
  dropObject();

  // go to parking
  left();
  forward(1);
  right();
  forward(3);
  right();
  forward(5);
  encoderForward(400); 
}

void grid7_blue() {
  // 0 1 0
  // 0 1 1
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();  
  forward(4);
  left();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  right();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);

  dropObject();  

  // go to second rock
  left();
  forward(1);
  right();

  pickupObject();

  // go to 2nd empty position
  right();
  forward(2);
  left();
  forward(3);
  left();
  forward(1);
  right();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  left();
  forward(1);
  left();
  forward(2);
  left();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();
  forward(1);
  right();
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  left();
  forward(1);
  right();
  forward(1);
  left();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  left();
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  left();

  dropObject();

  // go to parking
  left();
  forward(3);
  encoderForward(400); 
}

void grid8_blue() {
  // 1 0 1
  // 0 0 0
  // 0 1 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();  
  forward(5);
  left();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  right();
  forward(1);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(2);

  dropObject();  

  // go to second rock
  left();
  forward(1);
  left();

  pickupObject();

  // go to 2nd empty position
  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();
  left();
  forward(1);
  left();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(4);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();
  forward(1);
  right();
  forward(2);
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  right();
  forward(1);
  left();
  forward(1);
  
  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  backward(2);
  
  dropObject();

  // go to parking
  left();
  forward(1);
  right();
  forward(2);
  right();
  forward(5);
  encoderForward(400); 
}

void grid9_blue() {
  // 0 1 0
  // 0 0 0
  // 1 0 1

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();
  forward(3);
  left();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  right();
  forward(3);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(4);

  dropObject();  

  // go to second rock
  left();
  forward(1);
  right();
  forward(2);

  pickupObject();

  // go to 2nd empty position
  right();
  forward(1);
  left();
  forward(2);

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  left();

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  right();
  forward(3);
  right();
  forward(1);
  left();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  backward(4);
  
  dropObject();

  // go to parking
  left();
  forward(1);
  right();
  forward(4);
  right();
  forward(5);
  encoderForward(400); 
}

void grid10_blue() {
  // 0 1 0
  // 1 1 0
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  left();
  forward(4);
  left();
  forward(1);

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();

  right();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  left();
  forward(1);
  right();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();
  forward(1);
  left();

  dropObject();  

  // go to second rock
  right();
  forward(1);
  left();
  
  pickupObject();

  // go to 2nd empty position
  right();
  forward(1);

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  left();
  forward(1);
  right();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  encoder180();
  backward(1);
  // right();
  lineFollowBackwardUntilFrontArrayAllBlack();
  // right();
  forward(1);
  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();
  forward(1);
  left();
  forward(1);

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  left();
  forward(1);
  left();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  left();
  forward(1);
  right();
  
  pickupObject();

  // drop 3rd tree
  encoder180();
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  forward(2);

  // left();
  // lineFollowBackwardUntilFrontArrayAllBlack();
  // left();
  // forward(1);

  dropObject();

  // go to parking
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  left();
  forward(5);
  encoderForward(400); 
}

//////////////////
// red arena
//////////////////

void grid1_red() {
  // 1 0 0
  // 0 1 0
  // 0 0 1

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();  
  forward(3);
  right();
  forward(2);

  // pick the rock
  pickupObject();
  
  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // place the rock at 1st position
  left();
  forward(3);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  right();
  forward(2);
  right();
  forward(2);

  dropObject();  

  // go to second rock
  right();
  pickupObject();

  // go to 2nd empty position
  forward(1);
  right();
  forward(2);
  left();
  forward(1);
  right();

  
  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();
  forward(1);
  right();
  forward(1);

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  right();
  forward(1);
  left();
  forward(1);

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  pickupObject();

  // drop 3rd tree
  left();
  forward(2);
  left();

  dropObject();

  // go to parking
  right();
  forward(2);
  encoderForward(400);
}

void grid2_red() {
  // 0 0 1
  // 0 1 0
  // 1 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();
  forward(3);
  right();

  // pick the rock
  pickupObject();
  
  left();
  forward(3);

  // place the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(4);
  lineFollowBackwardUntilFrontArrayAllBlack();
  dropObject();  

  // go to second rock
  right();
  
  forward(1);
  left();
  forward(1);

  // pick the 2nd rock
  pickupObject();

  // go to 2nd empty position
  lineFollowUntilSensorsInMiddle();
  forward(3);
  left();
  forward(1);
  right();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  // drop 2nd tree
  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();
  dropObject(); // front array all black

  // go to 3rd rock
  right();
  forward(1);
  left();
  forward(1);

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(2);
  left();
  forward(1);
  right();
  
  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();

  // pick the 3rd tree
  pickupObject();

  // drop 3rd tree
  right(); 
  encoderBackward(30);
  lineFollowUntilSensorsInMiddle();
  encoderRight(290);  

  dropObject();

  // go to parking
  right();
  forward(4);
  encoderForward(400);
}


void grid3_red() {
  // 1 1 1
  // 0 0 0
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();  
  forward(5);
  right();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  left();
  forward(1);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(2);

  dropObject();  

  // go to second rock
  right();
  forward(1);
  left();

  pickupObject();

  // go to 2nd empty position
  forward(2);
  left();
  forward(1);
  right();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();
  forward(1);
  left();
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(2);
  left();
  forward(1);
  right();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  backward(2);
  
  dropObject();

  // go to parking
  right();
  forward(1);
  left();
  forward(2);
  left();
  forward(5);
  encoderForward(400); 
}

void grid4_red() {
  // 0 1 0
  // 1 0 1
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();  
  forward(4);
  right();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  left();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);

  dropObject();  

  // go to second rock
  right();
  forward(1);
  left();
  forward(1);

  pickupObject();

  // go to 2nd empty position
  forward(2);
  left();
  forward(1);
  right();
  
  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  left();
  forward(2);
  left();
  forward(1);
  right();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  backward(3);
  
  dropObject();

  // go to parking
  right();
  forward(1);
  left();
  forward(3);
  left();
  forward(5);
  encoderForward(400);
}

// not tested

void grid5_red() {
  // 0 0 0
  // 0 1 0
  // 1 0 1

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();  
  forward(3);
  right();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  left();
  forward(3);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(4);

  dropObject();  

  // go to second rock
  right();
  forward(1);
  left();
  forward(1);

  pickupObject();

  // go to 2nd empty position
  forward(2);
  left();
  forward(1);
  right();
  forward(1);
  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  left();
  forward(2);
  left();
  forward(1);
  right();
  forward(1);

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  backward(4);
  
  dropObject();

  // go to parking
  right();
  forward(1);
  left();
  forward(4);
  left();
  forward(5);
  encoderForward(400); 
}

void grid6_red() {
  // 0 0 0
  // 1 1 1
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();  
  forward(4);
  right();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  left();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);

  dropObject();  

  // go to second rock
  right();
  forward(1);
  left();

  pickupObject();

  // go to 2nd empty position
  forward(3);
  left();
  forward(1);
  right();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();
  forward(1);
  left();
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(3);
  left();
  forward(1);
  right();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  backward(3);
  
  dropObject();

  // go to parking
  right();
  forward(1);
  left();
  forward(3);
  left();
  forward(5);
  encoderForward(400); 
}

void grid7_red() {
  // 0 1 0
  // 1 1 0
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();
  forward(4);
  right();
  forward(1);

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();

  left();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);
  lineFollowBackwardUntilFrontArrayAllBlack();
  forward(1);
  right();

  dropObject();  

  // go to second rock
  left();
  forward(1);
  right();
  
  pickupObject();

  // go to 2nd empty position
  left();
  forward(1);

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  encoder180();
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  forward(1);

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  left();
  forward(1);
  right();
  forward(1);

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  right();
  forward(1);
  right();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  encoder180();
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  forward(2);

  dropObject();

  // go to parking
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  right();
  forward(5);
  encoderForward(400); 
}

void grid8_red() {
  // 1 0 1
  // 0 0 0
  // 0 1 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();  
  forward(5);
  right();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  left();
  forward(1);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(2);

  dropObject();  

  // go to second rock
  right();
  forward(1);
  right();

  pickupObject();

  // go to 2nd empty position
  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();
  right();
  forward(1);
  right();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(4);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();
  forward(1);
  left();
  forward(2);
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  left();
  forward(1);
  right();
  forward(1);
  
  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  backward(2);
  
  dropObject();

  // go to parking
  right();
  forward(1);
  left();
  forward(2);
  left();
  forward(5);
  encoderForward(400); 
}

void grid9_red() {
  // 0 1 0
  // 0 0 0
  // 1 0 1

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();
  forward(3);
  right();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  left();
  forward(3);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(4);

  dropObject();  

  // go to second rock
  right();
  forward(1);
  left();
  forward(2);

  pickupObject();

  // go to 2nd empty position
  left();
  forward(1);
  right();
  forward(2);

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  backward(2);
  lineFollowBackwardUntilFrontArrayAllBlack();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  right();

  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  forward(1);
  left();
  forward(3);
  left();
  forward(1);
  right();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  backward(4);
  
  dropObject();

  // go to parking
  right();
  forward(1);
  left();
  forward(4);
  left();
  forward(5);
  encoderForward(400); 
}

void grid10_red() {
  // 0 1 0
  // 0 1 1
  // 0 0 0

  // reset servo
  upServo();

  // go to first rock
  forward(4);
  right();  
  forward(4);
  right();

  // pick the rock
  pickupObject();

  // place the rock at 1st position
  left();
  forward(2);

  // drop the rock at 1st position
  dropObject();

  // go to 1st tree
  right();
  forward(1);
  left();

  // pick the first tree
  pickupObject();

  // drop 1st tree
  backward(3);

  dropObject();  

  // go to second rock
  right();
  forward(1);
  left();

  pickupObject();

  // go to 2nd empty position
  left();
  forward(2);
  right();
  forward(3);
  right();
  forward(1);
  left();

  // drop the rock at 2nd position
  dropObject();

  // go to 2nd tree
  right();
  forward(1);
  left();

  // pick the 2nd tree
  pickupObject(); // at end front array all black

  right();
  forward(1);
  right();
  forward(2);
  right();

  // drop 2nd tree
  dropObject(); // front array all black

  // go to 3rd rock
  right();
  forward(1);
  left();
  
  // pick the 3rd rock
  pickupObject(); // all front

  // go to 3rd empty position
  right();
  forward(1);
  left();
  forward(1);
  right();

  // drop the rock at 3rd position  
  dropObject();

  // go to 3rd tree
  right();
  forward(1);
  left();
  
  pickupObject();

  // drop 3rd tree
  right();
  backward(1);
  lineFollowBackwardUntilFrontArrayAllBlack();
  right();

  dropObject();

  // go to parking
  right();
  forward(3);
  encoderForward(400); 
}


void lineFollow(int &currentCounter, int targetCounter, int lm, int l, int m, int r, int rm) 
{
  if (lm==1 && l==1 && m==0 && r==1 && rm==1) {
    forwardWithoutSensors();
  } 
  else if (lm==1 && l==0 && m==0 && r==1 && rm==1) {
    leftWithoutSensors(turnSpeed);
  } 
  else if (lm==1 && l==1 && m==0 && r==0 && rm==1) {
    rightWithoutSensors(turnSpeed);
  } 
  else if (lm==1 && l==1 && m==1 && r==0 && rm==1) {
    rightWithoutSensors(turnSpeed);
  }
  else if (lm==1 && l==1 && m==1 && r==1 && rm==0) {
    right90WithoutSensors(turnSpeed);
  }
  else if (lm==1 && l==1 && m==1 && r==0 && rm==0) {
    right90WithoutSensors(turnSpeed);
  }
  else if (lm==1 && l==1 && m==0 && r==0 && rm==0) {
    right90WithoutSensors(turnSpeed);
  }
  else if (lm==1 && l==0 && m==1 && r==1 && rm==1) {
    leftWithoutSensors(turnSpeed);
  }
  else if (lm==0 && l==1 && m==1 && r==1 && rm==1) {
    left90WithoutSensors(turnSpeed);
  }
  else if (lm==0 && l==0 && m==1 && r==1 && rm==1) {
    left90WithoutSensors(turnSpeed);
  }
  else if (lm==0 && l==0 && m==0 && r==1 && rm==1) {
    left90WithoutSensors(turnSpeed);
  }
  else if (lm==1 && l==1 && m==1 && r==1 && rm==1) {
    forwardWithoutSensors();
  }
  else if (lm==0 && rm==0) {
    currentCounter++;
    if (currentCounter != targetCounter) {
      forwardWithoutSensors();
      delay(250);
    }
  }
}

void forward(int untilCount) {
  int counter = 0;

  delay(delayTime);
  encoderForward(50);
  
  while (counter < untilCount) {
    lineFollow(
      counter,
      untilCount,
      frontSensors[0].getValue(threshold),
      frontSensors[1].getValue(threshold),
      frontSensors[2].getValue(threshold),
      frontSensors[3].getValue(threshold),
      frontSensors[4].getValue(threshold)
    );
    if (counter == untilCount) {
      halt();
      delay(delayTime);
      break;
    }
  }
}
void lineFollowBackwardUntilSensorsInMiddle() {
  int leftMiddle, rightMiddle;

  delay(100);
  encoderBackward(30);

  do {
    int rm = backSensors[0].getValue(threshold);
    int r = backSensors[1].getValue(threshold);
    int l = backSensors[3].getValue(threshold);
    int lm = backSensors[4].getValue(threshold);

    if (lm==1 && l==1  && r==1 && rm==1) {
    backwardWithoutSensors();
    } 
    else if (lm==1 && l==0  && r==1 && rm==1) {
      leftWithoutSensors(turnSpeed);
    } 
    else if (lm==1 && l==1  && r==0 && rm==1) {
      rightWithoutSensors(turnSpeed);
    } 
    else if (lm==1 && l==1  && r==1 && rm==0) {
      right90WithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && r==0 && rm==0) {
      rightWithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==0 && r==1 && rm==1) {
      leftWithoutSensors(turnSpeed);
    }
    else if (lm==0 && l==1 && r==1 && rm==1) {
      left90WithoutSensors(turnSpeed);
    }
    else if (lm==0 && l==0 && r==1 && rm==1) {
      left90WithoutSensors(turnSpeed);
    }
    else if (lm==0 && l==0 && r==0 && rm==0) {
      backwardWithoutSensors();
      delay(200);
    }

    ///////////////////////////////////////////
    leftMiddle = leftMiddleSensor.getValue();
    rightMiddle = rightMiddleSensor.getValue();
  }
  while(leftMiddle == 1 && rightMiddle == 1);

  halt();
  delay(delayTime);
}
void lineFollowUntilSensorsInMiddle() {
  int leftMiddle, rightMiddle;

  delay(100);
  encoderForward(30);

  do {
    int lm = frontSensors[0].getValue(threshold);
    int l = frontSensors[1].getValue(threshold);
    int m = frontSensors[2].getValue(threshold);
    int r = frontSensors[3].getValue(threshold);
    int rm = frontSensors[4].getValue(threshold);

    if (lm==1 && l==1 && m==0 && r==1 && rm==1) {
      forwardWithoutSensors();
    } 
    else if (lm==1 && l==0 && m==0 && r==1 && rm==1) {
      forwardWithoutSensors();
    } 
    else if (lm==1 && l==1 && m==0 && r==0 && rm==1) {
      forwardWithoutSensors();
    } 
    else if (lm==1 && l==1 && m==1 && r==0 && rm==1) {
      rightWithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==0 && r==0 && rm==1) {
      rightWithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==1 && r==1 && rm==0) {
      right90WithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==1 && r==0 && rm==0) {
      right90WithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==0 && m==1 && r==1 && rm==1) {
      leftWithoutSensors(turnSpeed);
    }
    else if (lm==0 && l==1 && m==1 && r==1 && rm==1) {
      left90WithoutSensors(turnSpeed);
    }
    else if (lm==0 && l==0 && m==1 && r==1 && rm==1) {
      left90WithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==1 && r==1 && rm==1) {
      forwardWithoutSensors();
    }
    else if (lm==0 && rm==0) {
      forwardWithoutSensors();
    }

    leftMiddle = leftMiddleSensor.getValue();
    rightMiddle = rightMiddleSensor.getValue();
  }
  while(leftMiddle != 0 && rightMiddle != 0);

  halt();
  delay(200);
}
void lineFollowBackwardUntilFrontArrayAllBlack() {
  int frontLeftMost, frontRightMost;
  delay(100);
  encoderBackward(30);

  do {
    int rm = backSensors[0].getValue(threshold);
    int r = backSensors[1].getValue(threshold);
    int l = backSensors[3].getValue(threshold);
    int lm = backSensors[4].getValue(threshold);

    if (lm==1 && l==1  && r==1 && rm==1) {
    backwardWithoutSensors();
    } 
    else if (lm==1 && l==0  && r==1 && rm==1) {
      left90WithoutSensors(40);
    } 
    else if (lm==1 && l==1  && r==0 && rm==1) {
      right90WithoutSensors(40);
    } 
    else if (lm==1 && l==1  && r==1 && rm==0) {
      right90WithoutSensors(40);
    }
    else if (lm==1 && l==1 && r==0 && rm==0) {
      rightWithoutSensors(40);
    }
    else if (lm==1 && l==0 && r==1 && rm==1) {
      left90WithoutSensors(40);
    }
    else if (lm==0 && l==1 && r==1 && rm==1) {
      left90WithoutSensors(40);
    }
    else if (lm==0 && l==0 && r==1 && rm==1) {
      left90WithoutSensors(40);
    }
    else if (lm==0 && l==0 && r==0 && rm==0) {
      backwardWithoutSensors();
      delay(200);
    }

    frontLeftMost = frontSensors[0].getValue(threshold);
    frontRightMost = frontSensors[4].getValue(threshold);
  }
  while(frontLeftMost == 1 || frontRightMost == 1);

  halt();
  delay(200);
}
void lineFollowForwardUntilBackArrayAllBlack() {
  int backLeftMost, backRightMost;
  delay(100);
  encoderForward(30);

  do {
    int lm = frontSensors[0].getValue(threshold);
    int l = frontSensors[1].getValue(threshold);
    int m = frontSensors[2].getValue(threshold);
    int r = frontSensors[3].getValue(threshold);
    int rm = frontSensors[4].getValue(threshold);

    if (lm==1 && l==1 && m==0 && r==1 && rm==1) {
      forwardWithoutSensors();
    } 
    else if (lm==1 && l==0 && m==0 && r==1 && rm==1) {
      forwardWithoutSensors();
    } 
    else if (lm==1 && l==1 && m==0 && r==0 && rm==1) {
      forwardWithoutSensors();
    } 
    else if (lm==1 && l==1 && m==1 && r==0 && rm==1) {
      rightWithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==0 && r==0 && rm==1) {
      rightWithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==1 && r==1 && rm==0) {
      right90WithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==1 && r==0 && rm==0) {
      right90WithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==0 && m==1 && r==1 && rm==1) {
      leftWithoutSensors(turnSpeed);
    }
    else if (lm==0 && l==1 && m==1 && r==1 && rm==1) {
      left90WithoutSensors(turnSpeed);
    }
    else if (lm==0 && l==0 && m==1 && r==1 && rm==1) {
      left90WithoutSensors(turnSpeed);
    }
    else if (lm==1 && l==1 && m==1 && r==1 && rm==1) {
      forwardWithoutSensors();
    }
    else if (lm==0 && rm==0) {
      forwardWithoutSensors();
    }

    backLeftMost = backSensors[0].getValue(threshold);
    backRightMost = backSensors[4].getValue(threshold);
  }
  while(backLeftMost == 1 || backRightMost == 1);

  halt();
  delay(delayTime);
}

//////////////////////////////
// Backward LineFollow Logic
//////////////////////////////
void lineFollowBackward(int &currentCounter, int targetCounter, int lm, int l, int r, int rm) 
{
  if (lm==1 && l==1  && r==1 && rm==1) {
    backwardWithoutSensors();
  } 
  else if (lm==1 && l==0  && r==1 && rm==1) {
    leftWithoutSensors(turnSpeed);
  } 
  else if (lm==1 && l==1  && r==0 && rm==1) {
    rightWithoutSensors(turnSpeed);
  } 
  else if (lm==1 && l==1  && r==1 && rm==0) {
    right90WithoutSensors(turnSpeed);
  }
  else if (lm==1 && l==1 && r==0 && rm==0) {
    rightWithoutSensors(turnSpeed);
  }
  else if (lm==0 && l==1 && r==1 && rm==1) {
    left90WithoutSensors(turnSpeed);
  }
  else if (lm==0 && l==0 && r==1 && rm==1) {
    left90WithoutSensors(turnSpeed);
  }
  else if (lm==0 && l==0 && r==0 && rm==0) {
    currentCounter++;
    if (currentCounter != targetCounter) {
      backwardWithoutSensors();
      delay(250);
    }
  }
}
void backward(int untilCount) {
  int counter = 0;
  delay(100);
  encoderBackward(50);
  
  while (counter < untilCount) {
    lineFollowBackward(
      counter,
      untilCount,
      backSensors[4].getValue(threshold),
      backSensors[3].getValue(threshold),
      backSensors[1].getValue(threshold),
      backSensors[0].getValue(threshold)
    );
    if (counter == untilCount) {
      halt();
      delay(delayTime);
      break;
    }
  }
}

// Utilities
void forwardWithoutSensors() {
  leftMotor.forward(leftSpeed);
  rightMotor.forward(rightSpeed);
}
void forwardWithoutSensors(int speed) {
  leftMotor.forward(speed);
  rightMotor.forward(speed);
}
void backwardWithoutSensors() {
  leftMotor.backward(leftSpeed);
  rightMotor.backward(rightSpeed);
}
void backwardWithoutSensors(int speed) {
  leftMotor.backward(speed);
  rightMotor.backward(speed);
}
void leftWithoutSensors(int speed) {
  rightMotor.forward(speed);
  leftMotor.backward(0);
}
void rightWithoutSensors(int speed) {
  leftMotor.forward(speed);
  rightMotor.backward(0);
}
void right90WithoutSensors(int turnSpeed) { 
  leftMotor.forward(turnSpeed);
  rightMotor.backward(turnSpeed);
}
void right90WithoutSensors(int leftSpeed, int rightSpeed) { 
  leftMotor.forward(leftSpeed);
  rightMotor.backward(rightSpeed);
}
void left90WithoutSensors(int leftSpeed, int rightSpeed) {
  leftMotor.backward(leftSpeed);
  rightMotor.forward(rightSpeed);
}
void left90WithoutSensors(int turnSpeed) {
  leftMotor.backward(turnSpeed);
  rightMotor.forward(turnSpeed);
}
void halt() {
  leftMotor.stop();
  rightMotor.stop();
}
void left() {
  lineFollowUntilSensorsInMiddle();
  delay(delayTime / 2);

  encoderBackward(30);
  delay(delayTime);
  // turn left until middle sensor is on line
  encoderLeft(290);

  // while (frontSensors[2].getValue(threshold) != 0) {
  //   left90WithoutSensors(60, 60);
  // }
  halt();
  delay(delayTime);
}
void right() {
  lineFollowUntilSensorsInMiddle();
  delay(delayTime / 2);

  // turn left until middle sensor is on line
  encoderRight(290);

  // while (frontSensors[2].getValue(threshold) != 0) {
  //   right90WithoutSensors(70, 70);
  // }
  halt();
  delay(delayTime);
}
void rightBackward() {
  lineFollowBackwardUntilSensorsInMiddle();
  delay(300);
  // turn left until middle sensor is on line
  encoderRight(130);

  while (frontSensors[2].getValue(threshold) != 0) {
    right90WithoutSensors(40, 40); 
  }
  halt();
}
void leftBackward() {
  lineFollowBackwardUntilSensorsInMiddle();
  delay(300);
  // turn left until middle sensor is on line
  encoderLeft(130);

  while (frontSensors[2].getValue(threshold) != 0) {
    left90WithoutSensors(40, 40); 
  }
  halt();
}
void forwardMiddleSensors() {
  int m1 = leftMiddleSensor.getValue();
  int m2 = rightMiddleSensor.getValue();

  while(m1 -= 1 && m2 != 1) {
    forwardWithoutSensors();
    m1 = leftMiddleSensor.getValue();
    m2 = rightMiddleSensor.getValue();
  }
  halt();
}

// encoder functions
void LencodeFunc() {
    leftEncoderTicks++;
}
void RencodeFunc() {
    rightEncoderTicks++;
}

void encoderLeft(int value) {
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;

    while (leftEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        left90WithoutSensors(80,80);
    }

    halt();
}
void encoderForward(int value) {
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        forwardWithoutSensors();
    }

    halt();
}
void encoderBackward(int value) {
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        backwardWithoutSensors();
    }

    halt();
    delay(delayTime);
}

void encoderBackward(int value, int speed) {
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        backwardWithoutSensors(speed);
    }

    halt();
    delay(delayTime);
}

void encoderForward(int value, int speed) {
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        forwardWithoutSensors();
    }

    halt();
}

void encoderRight(int value)
{
    halt();
    delay(300);
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;

    while (rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        // left, right
        right90WithoutSensors(80, 80);
    }

    halt();
}

void encoder180() {
  delay(delayTime);
  encoderLeft(620);
}
void printSensorValues() {
  // front sensors
  for (int i = 0; i < 5; i++) {
    Serial.print(frontSensors[i].getValue());
    Serial.print(" ");
  }
  Serial.print(" -> ");
  // back sensors
  for (int i = 0; i < 5; i++) {
    Serial.print(backSensors[i].getValue());
    Serial.print(" ");
  }
  Serial.println();
}

void detectObject(int detectionDistance) {
  int _;  
  Timer1.attachInterrupt(triggerSonar);


  // follow the line until the object is detected
  while (distance > detectionDistance || distance == 0) {
    lineFollow(
      _,
      5,
      frontSensors[0].getValue(threshold),
      frontSensors[1].getValue(threshold),
      frontSensors[2].getValue(threshold),
      frontSensors[3].getValue(threshold),
      frontSensors[4].getValue(threshold)
    );
  }
  halt();
  Timer1.detachInterrupt();
}

void triggerSonar() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo pulse
  long duration = pulseIn(echoPin, HIGH);
  if (duration > 0) {  // Ensure a valid reading
    distance = duration / 29 / 2;
  }

  Serial.println(distance);
}

// servo
void moveServo(int startAngle, int endAngle) {
  myservo.attach(servoPin);

  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle++) {
      myservo.write(angle);
      delay(10);
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle--) {
      myservo.write(angle);
      delay(20);
    }
  }
}
void downServo() {
  myservo.attach(servoPin);
  myservo.write(servoDownPoint);
}
void downServoSlow() {
  moveServo(servoPickPoint, servoDownPoint);
}
void upServo() {
  // moveServo(servoDownPoint, servoUpPoint);
  myservo.attach(servoPin);
  myservo.write(servoUpPoint);
}
void pickUpServo() {
  moveServo(servoDownPoint, servoPickPoint);
}

// Pickup Mechanism
void pickupObject() {
  // old
  // encoderBackward(30);
  // downServoSlow();
  // delay(delayTime);

  lineFollowForwardUntilBackArrayAllBlack();
  lineFollowBackwardUntilFrontArrayAllBlack();
  delay(400);
  downServoSlow();
  delay(400);
  lineFollowForwardUntilBackArrayAllBlack();
  encoderForward(50);
  delay(delayTime);

  pickUpServo();
  lineFollowBackwardUntilFrontArrayAllBlack();
}

void dropObject() {
  encoderForward(30);
  forward(1);
  encoderBackward(180);
  downServoSlow();
  delay(400);
  encoderBackward(110); 
  lineFollowBackwardUntilFrontArrayAllBlack();
  upServo();
  delay(200);
}

int readDipSwitch() {
  int value = 0;

  // Read each DIP switch pin and combine into a single integer
  value |= digitalRead(dipSwitchPin1) << 0; // Read dipPin0 and shift 0 bits to the left
  value |= digitalRead(dipSwitchPin2) << 1; // Read dipPin1 and shift 1 bit to the left
  value |= digitalRead(dipSwitchPin4) << 2; // Read dipPin2 and shift 2 bits to the left
  value |= digitalRead(dipSwitchPin8) << 3; // Read dipPin3 and shift 3 bits to the left

  return value;
}