#include <Arduino.h>
#include <Servo.h>

// encoders
int EncoderRight = 3;
int EncoderLeft = 2;

int leftEncoderTicks = 0;
int rightEncoderTicks = 0;
int pos = 0;

Servo myservo;
unsigned long startTime = millis();

// threshold values for line detection
const int threshold = 800;

//front line follow IR array pins
int array_FML = A0;
int array_FL = A15;
int array_FC = A14;
int array_FR = A13;
int array_FMR = A12;

//back line follow IR array pins 
int array_BML = A8;
int array_BL = A9;
int array_BC = A10;
int array_BR = A11;
int array_BMR = A2;

// 9x9 IR sensor grid for map reading
// (1,1), (1,2), (1,3)
// (2,1), (2,2), (2,3)
// (3,1), (3,2), (3,3)

int map_reader_1_1 = A4;  // (1,1) connected to pin A4
int map_reader_1_2 = A5;  // (1,2) connected to pin A5
int map_reader_2_2 = A6;  // (2,2) connected to pin A6
int map_reader_3_1 = A7;  // (3,1) connected to pin A7

// motors 8,9,10,11
int moter_L_LPWM = 8;
int moter_L_RPWM = 9;

int moter_R_LPWM = 10;
int moter_R_RPWM = 11;

// ultrasonic sonar sensor
int trigger_pin = 44;
int echo_pin = 45;

// servo motor pin
int servo_pin = 15;

// middle IR sensors that are connected on both sides of robot in center right and center left
int rightIR = 22;
int leftIR = 41;

// moter speeds
int lspeed = 45;
int rspeed = 50;

// function for testing sensor values 
void sensorTest(int ML,int L,int C,int R,int MR)
{
  int leftmost = analogRead(ML);
  int left = analogRead(L);
  int middle = analogRead(C);
  int right = analogRead(R);
  int rightmost = analogRead(MR);


  Serial.print("Most Left = ");
  Serial.print(leftmost);
  Serial.print("\t\t");

  Serial.print("Left = ");
  Serial.print(left);
  Serial.print("\t");

  Serial.print("Center = ");
  Serial.print(middle);
  Serial.print("\t");

  Serial.print("Right = ");
  Serial.print(right);
  Serial.print("\t");

  Serial.print("Most Right = ");
  Serial.print(rightmost);
  Serial.print("\t");

  Serial.println();
  delay(100);
}

void MAP_READER(int map_reader_1_1,int map_reader_1_2,int map_reader_2_2,int map_reader_3_1)
{
  int _1_1 = analogRead(map_reader_1_1);
  int _1_2 = analogRead(map_reader_1_2);
  int _2_2 = analogRead(map_reader_2_2);
  int _3_1 = analogRead(map_reader_3_1);


  Serial.print("(1,1) = ");
  Serial.print(_1_1);
  Serial.print("\t\t");

  Serial.print("(1,2) = ");
  Serial.print(_1_2);
  Serial.print("\t");

  Serial.print("(2,2) = ");
  Serial.print(_2_2);
  Serial.print("\t");

  Serial.print("(3,1) = ");
  Serial.print(_3_1);
  Serial.print("\t");

  Serial.println();

  delay(100);
}

// function to print encoder values for both motors
void ticksValues(){
  Serial.print("Left ticks = ");
  Serial.print(leftEncoderTicks);
  Serial.print("\t");
  Serial.print(" Right ticks = ");
  Serial.print(rightEncoderTicks);
  Serial.println();
}
 
void middleIR(){
  int right_ir = digitalRead(rightIR);
  int left_ir = digitalRead(leftIR);

  Serial.print("right senssor = ");
  Serial.print(right_ir);
  Serial.print("\t");
  Serial.print("left senssor = ");
  Serial.print(left_ir);
  Serial.println();
}

void arraysValues(){
  // MAP_READER(map_reader_1_1,map_reader_1_2,map_reader_2_2,map_reader_3_1);
  // sensorTest(array_FML,array_FL,array_FC,array_FR,array_FMR);
  sensorTest(array_BML,array_BL,array_BC,array_BR,array_BMR);
  // middleIR();
}

// move the both motors forward
void bothForward(int lspeed,int rspeed) {
  analogWrite(moter_L_LPWM, lspeed);
  analogWrite(moter_L_RPWM, 0);
  analogWrite(moter_R_LPWM, rspeed);
  analogWrite(moter_R_RPWM, 0);
}

// move the both motors backward
void bothBackward() {
  analogWrite(moter_L_LPWM, 0);
  analogWrite(moter_L_RPWM, 50);
  analogWrite(moter_R_LPWM, 0);
  analogWrite(moter_R_RPWM, 48);
}
// stop motors
void halt() {
  analogWrite(moter_L_LPWM, 0);
  analogWrite(moter_L_RPWM, 0);
  analogWrite(moter_R_LPWM, 0);
  analogWrite(moter_R_RPWM, 0);
}

// turn right smooth
void rightTurn()
{
  analogWrite(moter_L_LPWM, 50);
  analogWrite(moter_L_RPWM, 0);
  analogWrite(moter_R_LPWM, 0);
  analogWrite(moter_R_RPWM, 0);
}

void rightTurnBack()
{
  analogWrite(moter_L_LPWM, 0);
  analogWrite(moter_L_RPWM, 0);
  analogWrite(moter_R_LPWM, 0);
  analogWrite(moter_R_RPWM, 50);
}

void sharpRightTurn()
{
  analogWrite(moter_L_LPWM, 150);
  analogWrite(moter_L_RPWM, 0);
  analogWrite(moter_R_LPWM, 0);
  analogWrite(moter_R_RPWM, 150);
}

// turn left smooth
void leftTurn()
{
  analogWrite(moter_L_LPWM, 0);
  analogWrite(moter_L_RPWM, 0);
  analogWrite(moter_R_LPWM, rspeed);
  analogWrite(moter_R_RPWM, 0);
}

void leftTurnBack()
{
  analogWrite(moter_L_LPWM, 0);
  analogWrite(moter_L_RPWM, rspeed);
  analogWrite(moter_R_LPWM, 0);
  analogWrite(moter_R_RPWM, 0);
}

void sharpLeftTurn()
{
  analogWrite(moter_L_LPWM, 0);
  analogWrite(moter_L_RPWM, 150);
  analogWrite(moter_R_LPWM, 150);
  analogWrite(moter_R_RPWM, 0);
}

// simple line follow for front side of robot
void justLineFollowFront()
{
    int  leftmost = analogRead(array_FML);
    int  left = analogRead(array_FL);
    int  middle = analogRead(array_FC);
    int  right = analogRead(array_FR);
    int  rightmost = analogRead(array_FMR);

  if(left >= threshold && middle <= threshold && right >=threshold)
  {
    bothForward(lspeed,rspeed);
  }
  else if(left <= threshold  && right >=threshold)
  {
    leftTurn();
  }
  else if(left >= threshold && right <=threshold)
  {
    rightTurn();
  }
   else if(leftmost <= threshold && rightmost >=threshold)
  {
    leftTurn();
  }
  else if(leftmost >= threshold && rightmost <=threshold)
  {
    rightTurn();
  }
  else{
    bothForward(lspeed,rspeed);
  }
}

// simple back line follow
void justLineFollowBack()
{
  int  leftmost = analogRead(array_BML);
  int  left = analogRead(array_BL);
  int  middle = analogRead(array_BC);
  int  right = analogRead(array_BR);
  int  rightmost = analogRead(array_BMR);

  if(left >= threshold && middle <= threshold && right >=threshold)
  {
    bothBackward();
  }
  else if(left <= threshold  && right >=threshold)
  {
    rightTurnBack();
  }

  else if(leftmost <= threshold  && rightmost >=threshold)
  {
    rightTurnBack();
  }
  else if(left >= threshold && right <=threshold)
  {
    leftTurnBack();
  }

  else if(leftmost >= threshold && rightmost <=threshold)
  {
    leftTurnBack();
  }
  else{
    bothBackward();
  }
}

void LencodeFunc()
{
    leftEncoderTicks++;
}

void RencodeFunc()
{
    rightEncoderTicks++;
}

void rightEncoder(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        sharpRightTurn();
    }
    halt();
}

void leftEncoder(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        sharpLeftTurn();
 
    }
    halt();
}

void forwardEncoder(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        bothForward(35,40);
    }
    halt();
}

// function to linefollow based on encoder value
void lineFollowEncoderFront(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (rightEncoderTicks < value)
    {
        Serial.print(rightEncoderTicks);
        Serial.print(" ");
        justLineFollowFront();
    }
    halt();
}

void lineFollowEncoderBack(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (rightEncoderTicks < value)
    {
        Serial.print(rightEncoderTicks);
        Serial.print(" ");
        justLineFollowBack();
    }
    halt();
}

void backEncoder(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        bothBackward();
    }
    halt();

}

//  front lineFollow based on currentCounter  - currentCounter means to count black intersections
void lineFollowFront(int &currentCounter, int targetCounter,int leftmost, int left,int  middle,int right,int rightmost,int lspeed,int rspeed)
{
  if(left >= threshold && middle <= threshold && right >=threshold)
  {
    bothForward(lspeed,rspeed);
  }
  else if(left <= threshold  && right >=threshold)
  {
    leftTurn();
  }
  else if(left >= threshold && right <=threshold)
  {
    rightTurn();
  }
   else if(leftmost <= threshold && rightmost >=threshold)
  {
    leftTurn();
  }
  else if(leftmost >= threshold && rightmost <=threshold)
  {
    rightTurn();
  }
  else if (leftmost < threshold  && rightmost < threshold)
  {
    currentCounter++;
    if (currentCounter != targetCounter)
    {
      bothForward(lspeed,rspeed);
      lineFollowEncoderFront(60);
    }
  }
  else{
    bothForward(lspeed,rspeed);
  }
}

//  back lineFollow based on currentCounter  - currentCounter means to count black intersections
void lineFollowBack(int &currentCounter, int targetCounter, int leftmost, int left, int middle, int right, int rightmost)
{
  if(left >= threshold && middle <= threshold && right >=threshold)
  {
    bothBackward();
  }
  else if(left <= threshold  && right >=threshold)
  {
    rightTurnBack();
  }
  else if(left >= threshold && right <=threshold)
  {
    leftTurnBack();
  }
    else if(leftmost <= threshold  && rightmost >=threshold)
  {
    rightTurnBack();
  }
  else if(leftmost >= threshold && rightmost <=threshold)
  {
    leftTurnBack();
  }
  else if (leftmost < threshold &&  rightmost < threshold)
  {
    currentCounter++;
    if (currentCounter != targetCounter)
    {
      bothBackward();
      lineFollowEncoderBack(120);
    }
  }
  else{
    bothBackward();
  }
}

void lineFollowUntil(int untilCount,bool frontArray=false,bool backArray=false,int lspeed=45,int rspeed=50)
{
  int counter = 0;

  while (counter < untilCount)
  {
    int leftmost;
    int left;
    int middle;
    int right;
    int rightmost;

    if(frontArray){
      leftmost = analogRead(array_FML);
      left = analogRead(array_FL);
      middle = analogRead(array_FC);
      right = analogRead(array_FR);
      rightmost = analogRead(array_FMR);
      lineFollowFront(
        counter,
        untilCount,
        leftmost, left, middle, right, rightmost,lspeed,rspeed);
    }
    else if(backArray){
      leftmost = analogRead(array_BML);
      left = analogRead(array_BL);
      middle = analogRead(array_BC);
      right = analogRead(array_BR);
      rightmost = analogRead(array_BMR);
      lineFollowBack(
        counter,
        untilCount,
        leftmost, left, middle, right, rightmost);
    }

    if (counter >= untilCount)
    {
      halt();
      break;
    }
  }
}

// when the front linefollow IR array reaches the line (intersection), 
// then we will call this function to move the robot until the middle sensors on both right and left side reaches the line.
void checkPoint(){
  while (true){
    int right_ir = digitalRead(rightIR);
    int left_ir = digitalRead(leftIR);

    if(right_ir == 0 && left_ir == 0){
      bothForward(45,50);
    }
    else{
      halt();
      delay(500);
      break;
     
    }
  }
}

// when the back linefollow IR array reaches the target line (intersection), 
// then we will call this function to move the robot until the middle sensors on both right and left side reaches the line.
void centered(){
  while (true){
    int right_ir = digitalRead(rightIR);
    int left_ir = digitalRead(leftIR);

    if(right_ir == 0 && left_ir == 0){
      bothBackward();
    }
    else{
      halt();
      delay(500);
      break;
    }
  }
}

// rotate servo arm down, ready to pick tree
void treePicInit(){

    for (pos = 80; pos >= 12; pos -= 1) {
      myservo.write(pos);          
      delay(15);                      
  }
}

// rotate servo arm up, ready to pick tree up
void treePic(){
    for (pos = 12; pos <= 50; pos += 1) {
      myservo.write(pos);          
      delay(15);                      
  }
  
}

// drop thee tree
void treeDrop(){

    for (pos = 50; pos >= 12; pos -= 1) {
      myservo.write(pos);          
      delay(15);                     
  }

  halt();

}

void grid2Blue(){
  //#################################################
  // blue
  // 1,0,0
  // 0,1,0
  // 0,0,1

  // rock drop 1 (3,3)
  lineFollowUntil(4,true,false);
  checkPoint();
  leftEncoder(210);
  halt();
  delay(500);
  lineFollowUntil(3,true,false);
  checkPoint();
  leftEncoder(220);
  halt();
  delay(500);
  lineFollowEncoderFront(40);
  halt();
  delay(100);
  lineFollowEncoderBack(100+100);
  bothBackward();
  delay(200);
  halt();
  treePicInit();
  checkPoint();
  lineFollowEncoderFront(160);
  halt();
  treePic();
  centered();
  rightEncoder(210);
  halt();
  delay(1000);
  lineFollowUntil(3,true,false);
  checkPoint();
  delay(1000);
  lineFollowEncoderFront(145);
  halt();
  delay(500);
  treeDrop();

  // tree drop 1 (3,3)
  delay(500);
  lineFollowUntil(2,false,true);
  centered();
  leftEncoder(210);
  lineFollowUntil(1,true,false);
  checkPoint();
  rightEncoder(210);
  delay(1000);
  lineFollowUntil(1,true,false);
  checkPoint();
  lineFollowEncoderFront(140);
  treePic();
  delay(500);
  lineFollowUntil(4,false,true);
  centered();
  delay(500);
  lineFollowEncoderBack(200-50);
  delay(500);
  treeDrop();
  delay(500);
// rock drop 2 (2,2)
  centered();
  leftEncoder(210);
  lineFollowUntil(1,true,false);
  checkPoint();
  rightEncoder(210);
  lineFollowUntil(1,true,false);
  checkPoint();
  lineFollowEncoderFront(145);
  delay(500);
  treePic();
  delay(500);
  lineFollowUntil(2,true,false);
  checkPoint();
  rightEncoder(210);
  lineFollowUntil(1,true,false);
  checkPoint();
  leftEncoder(210);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  lineFollowEncoderFront(145);
  delay(500);
  treeDrop();
  delay(500);

// tree drop 2 (2,2)
  lineFollowUntil(2,false,true);
  centered();
  rightEncoder(210);
  lineFollowUntil(1,false,true);
  centered();
  leftEncoder(210);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  lineFollowEncoderFront(145);
  treePic();
  delay(500);
  lineFollowUntil(3,false,true);
  centered();
  delay(500);
  lineFollowEncoderBack(200-50);
  delay(500);
  treeDrop();
  delay(500);

// rock drop 3 (1,1)
  centered();
  delay(500);
  leftEncoder(210);
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  rightEncoder(210);
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  lineFollowEncoderFront(145);
  delay(500);
  treePic();
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  rightEncoder(210);
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  leftEncoder(210);
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  lineFollowEncoderFront(145);
  delay(500);
  treeDrop();
  delay(500);

// tree drop 3 (1,1)
  lineFollowUntil(2,false,true);
  centered();
  delay(500);
  leftEncoder(210);
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  rightEncoder(210);
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();
  delay(500);
  lineFollowEncoderFront(150);
  delay(500);
  treePic();
  delay(500);
  centered();
  delay(500);
  leftEncoder(470);
  delay(500);
  lineFollowEncoderBack(100);
  delay(500);
  checkPoint();
  delay(500);
  lineFollowEncoderFront(110+40);
  delay(500);
  treeDrop();
  delay(500);
  centered();
  // parking
  delay(500);
  leftEncoder(210);
  delay(500);
  lineFollowUntil(4,true,false);
  checkPoint();
  lineFollowEncoderFront(300);
}

void grid3blue()
{
  //#################################################
  // blue
  // 1,1,1
  // 0,0,0
  // 0,0,0

  // Step 1: Move to first intersection (4 intersections forward)
  lineFollowUntil(4, true, false);
  checkPoint();
  // Step 2: Turn left
  leftEncoder(210);
  halt();
  delay(500);
  // Step 3: Move forward
  lineFollowUntil(4, true, false);
  checkPoint();
  // Step 4: Turn left
  leftEncoder(210);
  halt();
  delay(500);
  // Step 5: Forward 1 step
  lineFollowUntil(1, true, false);
  checkPoint();
  // Step 6: Turn right
  rightEncoder(210);
  halt();
  delay(500);
}

void grid9Blue(){
  // blue
  // 0,1,0
  // 0,0,0
  // 1,0,1
  


  // // rock drop 2 (3,1)
  // lineFollowUntil(4,true,false);
  // checkPoint();
  // leftEncoder(210);
  // halt();
  // delay(500);
  // lineFollowUntil(2,true,false);
  // checkPoint();
  // leftEncoder(220);
  // halt();
  // delay(500);
  // lineFollowUntil(3,true,false);
  // checkPoint();
  // lineFollowEncoderFront(60);
  // delay(500);
  // rightEncoder(225);
  // delay(500);
  // lineFollowEncoderBack(200);
  // delay(500);
  // treePicInit();
  // delay(500);
  // checkPoint();
  // lineFollowEncoderFront(145);
  // delay(500);
  // treePic();
  // delay(500);

  // lineFollowUntil(2,true,false);
  // checkPoint();
  // rightEncoder(215);
  // delay(500);
  // lineFollowUntil(3,true,false);
  // checkPoint();
  // leftEncoder(215);
  // delay(500);
  // lineFollowUntil(2,true,false);
  // checkPoint();
  // delay(500);
  // lineFollowEncoderFront(145);
  // delay(500);
  // treeDrop();
  // delay(500);

  // // tree drop 2 (3,1)
  // lineFollowUntil(2,false,true);
  // centered();
  // rightEncoder(210);
  // delay(500);
  // lineFollowUntil(1,false,true);
  // centered();
  // leftEncoder(210);
  // delay(500);
  // lineFollowUntil(1,true,false);
  // checkPoint();
  // delay(500);
  // lineFollowEncoderFront(145);
  // delay(500);
  // treePic();
  // delay(500);
  // centered();
  // rightEncoder(235);
  // delay(500);
  // lineFollowUntil(2,false,true);
  // centered();
  // rightEncoder(210);

  // delay(500);
  // lineFollowUntil(2,true,false);
  // checkPoint();
  // delay(500);
  // lineFollowEncoderFront(145);
  // delay(500);
  // treeDrop();
  // delay(500);
  // centered();
  // leftEncoder(210);
  // // myservo.write(12);
  // delay(500);
  // lineFollowUntil(2,true,false);
  // checkPoint();
  // lineFollowEncoderFront(30);
  // delay(500);
  // rightEncoder(235);
  // delay(500);
  // centered();
  // lineFollowEncoderFront(140);
  // delay(500);
  // treePic();
  // delay(500);
  // lineFollowUntil(4,false,true);
  // centered();
  // delay(500);
  // lineFollowEncoderBack(160);
  // delay(500);
  // treeDrop();
  // delay(500);


  // // tree drop (3,3)
  // centered();
  // rightEncoder(220);
  // delay(500);
  // lineFollowUntil(1,true,false);
  // checkPoint();
  // lineFollowEncoderFront(30);
  // delay(500);
  // leftEncoder(235);
  // delay(500);
  // centered();
  // lineFollowEncoderFront(140);
  // delay(500);
  // treePic();
  // delay(500);
  // lineFollowUntil(2,true,false);
  // checkPoint();
  // leftEncoder(235);
  // delay(500);
  // lineFollowUntil(1,true,false);
  // checkPoint();
  // rightEncoder(210);
  // delay(500);
  // lineFollowUntil(2,true,false);
  // checkPoint();
  // lineFollowEncoderFront(140);
  // delay(500);
  // treeDrop();
  // delay(500);

  // rock drop 3 (1,2)
  
  lineFollowUntil(2,false,true);
  centered();
  myservo.write(50);
  delay(200);
  rightEncoder(235);
  delay(500);
  treePicInit();
  delay(500);
  centered();
  lineFollowEncoderFront(140);
  delay(500);
  treePic();
  delay(500);
  checkPoint();
  leftEncoder(235);
  delay(500);
  lineFollowUntil(2,false,true);
  centered();
  lineFollowEncoderBack(160);
  delay(500);
  treeDrop();
  delay(500);
  centered();
  rightEncoder(235);
  delay(500);
  lineFollowUntil(1,true,false);
  checkPoint();

  leftEncoder(235);
  delay(500);
  centered();
  lineFollowEncoderFront(145);
  delay(500);

  treePic();
  delay(500);
  lineFollowUntil(3,true,false);
  checkPoint();
  rightEncoder(235);
  delay(500);

  lineFollowUntil(1,false,true);
  centered();
  lineFollowEncoderBack(160);
  delay(500);
  treeDrop();
  delay(500);
  centered();
  lineFollowUntil(1,false,true);
  rightEncoder(235);
  lineFollowUntil(1,true,false);
  checkPoint();
  rightEncoder(235);
  lineFollowUntil(1,true,false);
  checkPoint();
  lineFollowEncoderFront(300);

}


void setup() {
  Serial.begin(9600);

  leftEncoderTicks = 0;
  rightEncoderTicks = 0;

  attachInterrupt(digitalPinToInterrupt(EncoderLeft), LencodeFunc, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderRight), RencodeFunc, RISING);


  pinMode(moter_L_LPWM, OUTPUT); 
  pinMode(moter_L_RPWM, OUTPUT);
  pinMode(moter_R_LPWM, OUTPUT);
  pinMode(moter_R_RPWM, OUTPUT);

  pinMode(array_BC, INPUT);
  pinMode(array_BL, INPUT);
  pinMode(array_BML, INPUT);
  pinMode(array_BMR, INPUT);
  pinMode(array_BR, INPUT);

  pinMode(array_FC, INPUT);
  pinMode(array_FL, INPUT);
  pinMode(array_FML, INPUT);
  pinMode(array_FMR, INPUT);
  pinMode(array_FR, INPUT);

  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, OUTPUT);


  pinMode(rightIR, INPUT);
  pinMode(leftIR, INPUT);


  pinMode(map_reader_1_1, INPUT);
  pinMode(map_reader_1_2, INPUT);
  pinMode(map_reader_2_2, INPUT);
  pinMode(map_reader_3_1, INPUT);

  myservo.attach(servo_pin);
  myservo.write(90);



// ###############################################
// map reading

  // // map reading array
  // lineFollowUntil(2,true,false);
  // checkPoint();
  // leftEncoder(250);
  // delay(100);
  // bothBackward();
  // delay(100);
  // halt();


  // grid2();
  myservo.write(12);
  grid9Blue();

}


void loop(){

  // bothForward();
  // bothBackward();
  // treePic();
  // arraysValues();
  // ticksValues();
  // middleIR();
  // justLineFollowBack();

}




