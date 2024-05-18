#include <Arduino.h>
#include <PID_v1.h>
#include "../include/motor.h"
#include "../include/SensorArray.h"
#include "../include/sensor.h"
#include "../include/colorsensor.h"
#include <Servo.h>

// const int M1_ENCODER_A = 26;
const int M1_ENCODER_B = 2;

// const int M2_ENCODER_A = 22;
const int M2_ENCODER_B = 3;

// Ticks counter for Motors
int m1Ticks = 0;
int m2Ticks = 0;


Servo rightServo, leftServo, leftSmallServo, rightSmallServo;

// Define Variables we'll be connecting to
double Setpoint, Input, Output, prevOutput;

// bias
int setSpeed = 30; 
int bias = setSpeed;

// Specify the links and initial tuning parameters
double Kp = 2500, Ki = 0, Kd = 30; // sir ny krwai thi tunning
// double Kp = 1.8, Ki = 0, Kd = 0;
// double Kp = 3.5, Ki = 0.4, Kd = 2;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int rs0 = 48, rs1 = 46, rs2 = 42, rs3 = 44, routSensor = 6;
int ls0 = 32, ls1 = 34, ls2 = 36, ls3 = 38, loutSensor = 7;
    
ColorSensor leftColorSensor(rs0, rs1, rs2, rs3, routSensor);
ColorSensor rightColorSensor(ls0, ls1, ls2, ls3, loutSensor);

Motor leftMotor(24, 26, 10), rightMotor(11, 12, 13);
int frontSensors[] = {A8, A11, A10, A9, A12};
SensorArray sensorArray(frontSensors, 5);
Sensor sensor1 = sensorArray.sensors[0],
       sensor2 = sensorArray.sensors[1],
       sensor3 = sensorArray.sensors[2],
       sensor4 = sensorArray.sensors[3],
       sensor5 = sensorArray.sensors[4];

int backSensor[] = {14, 15, 16, 17, 18};
SensorArray backSensorArray(backSensor, 5);
Sensor bSensor1 = backSensorArray.sensors[0],
       bSensor2 = backSensorArray.sensors[1],
       bSensor3 = backSensorArray.sensors[2],
       bSensor4 = backSensorArray.sensors[3],
       bSensor5 = backSensorArray.sensors[4];

int speed = 0;

void servoBakward();
void leftServoBakward();
void rightServoBakward();
void resetServo();
void servoForward();
void leftServoForward();
void rightServoForward();
void drive(int speed);
void driveBack(int speed);
void forward(int speed);
void backward(int speed);
void right(int speed);
void right90();
void right90(int);
void left90();
void left90(int);
void encoderLeft90();
void encoderRight90();
void left(int speed);
void halt();
void haltBack();
void resetTicks();
void countM1EncoderTicks();
void countM2EncoderTicks();
bool followLine();
bool followLine3Sensors();
void encoderRight180();
void encoderLeft180();
void redSideCode();
void blueSideCode();
void encoderBackwardArcForRed();
void encoderBackwardArcForBlue();
void encoderLeft90(int speed);

void setup()
{
    Serial.begin(9200);

    // Encoder
    pinMode(M1_ENCODER_B, INPUT_PULLUP);
    pinMode(M2_ENCODER_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(M1_ENCODER_B), countM1EncoderTicks, RISING);
    attachInterrupt(digitalPinToInterrupt(M2_ENCODER_B), countM2EncoderTicks, RISING);

    // set the goal position
    Setpoint = 30;

    // turn the PID on
    myPID.SetMode(AUTOMATIC);
    // lower, upper limits
    myPID.SetOutputLimits((-1) * setSpeed, setSpeed);

    // Servo Setup
    rightServo.attach(4);
    leftServo.attach(5);
    // leftSmallServo.attach(8);
    // rightSmallServo.attach(9);

    resetServo();

    // red team
    redSideCode();
    // blueSideCode();
}

void loop()
{
}

void encoderLeft90() {
    resetTicks();
    while(m1Ticks < 300 || m2Ticks < 300) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        left90();
    }
    halt();
}
void encoderLeft90(int speed) {
    resetTicks();
    while(m1Ticks < 300 || m2Ticks < 300) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        left90(speed);
    }
    halt();
}
void encoderRight90() {
    resetTicks();
    while(m1Ticks < 300 || m2Ticks < 300) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        right90();
    }
    halt();
}

void encoderRight180() {
    resetTicks();
    while(m1Ticks < 660 || m2Ticks < 660) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        right90();
    }
    halt();
}
void encoderLeft180() {
    resetTicks();
    while(m1Ticks < 660 || m2Ticks < 660) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        left90();
    }
    halt();
}
void encoderBackwardArcForRed() {
    rightMotor.setSpeed(30);
    leftMotor.setSpeed(140);
    
    rightMotor.backward();
    leftMotor.backward();
    delay(1000);
    halt();
}
void encoderBackwardArcForBlue() {
    rightMotor.setSpeed(140);
    leftMotor.setSpeed(30);
    
    rightMotor.backward();
    leftMotor.backward();
    delay(1300);
    halt();
}
void resetTicks() {
    m1Ticks = 0;
    m2Ticks = 0;
}
// drive the robot
void drive(int speed)
{
    if (speed < 0)
    {
        speed = (-1) * speed;

        // leftMotor.setSpeed(0);
        rightMotor.setSpeed(bias + speed);
        leftMotor.setSpeed(bias - speed);
        rightMotor.forward();
        // Serial.println("right");
    }
    else if (speed > 0)
    {
        rightMotor.setSpeed(bias - speed);
        // rightMotor.setSpeed(0);
        leftMotor.setSpeed(bias + speed);
        leftMotor.forward();
        // Serial.println("left");
    }
    else
    {
        leftMotor.setSpeed(bias);
        rightMotor.setSpeed(bias);
        leftMotor.forward();
        rightMotor.forward();
        // Serial.println("forward");
    }
}
void driveBack(int speed)
{
    if (speed < 0)
    {
        speed = (-1) * speed;

        // leftMotor.setSpeed(0);
        rightMotor.setSpeed(bias + speed);
        leftMotor.setSpeed(bias - speed);
        rightMotor.backward();
        // Serial.println("right");
    }
    else if (speed > 0)
    {
        rightMotor.setSpeed(bias - speed);
        // rightMotor.setSpeed(0);
        leftMotor.setSpeed(bias + speed);
        leftMotor.backward();
        // Serial.println("left");
    }
    else
    {
        leftMotor.setSpeed(bias);
        rightMotor.setSpeed(bias);
        leftMotor.backward();
        rightMotor.backward();
        // Serial.println("forward");
    }
}
void forward(int speed) {
    rightMotor.setSpeed(speed*1.2);
    leftMotor.setSpeed(speed);

    rightMotor.forward();
    leftMotor.forward();
}
void backward(int speed) {
    rightMotor.setSpeed(speed);
    leftMotor.setSpeed(speed);
    
    rightMotor.backward();
    leftMotor.backward();
}
void right(int speed) {
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(0);
    
    leftMotor.forward();
}
void right90() {
    rightMotor.setSpeed(35);
    leftMotor.setSpeed(35);
    
    rightMotor.backward();
    leftMotor.forward();
}
void right90(int speed) {
    rightMotor.setSpeed(speed);
    leftMotor.setSpeed(speed);
    
    rightMotor.backward();
    leftMotor.forward();
}
void left(int speed) {
    rightMotor.setSpeed(speed);
    leftMotor.setSpeed(0);
    
    rightMotor.forward();
}
void left90() {
    rightMotor.setSpeed(35);
    leftMotor.setSpeed(35);
    
    rightMotor.forward();
    leftMotor.backward();
}
void left90(int speed) {
    rightMotor.setSpeed(speed);
    leftMotor.setSpeed(speed);
    
    rightMotor.forward();
    leftMotor.backward();
}
void halt() {
    rightMotor.halt();
    leftMotor.halt();
}
void haltBack() {
    backward(80);
    delay(20);
    rightMotor.halt();
    leftMotor.halt();
}
void resetServo() {
    leftServo.write(180);
    rightServo.write(0);
    leftSmallServo.write(0);
    rightSmallServo.write(0);
}
void servoForward() {
    for (int i = 0; i <= 180; i++) {
        leftServo.write(180-i);
        if (i <= 173) {
            rightServo.write(i);
        }
        delay(5);
    }
}
void leftServoForward() {
    for (int i = 0; i <= 180; i++) {
        leftServo.write(180-i);
        delay(5);
    }
}
void rightServoForward() {
    for (int i = 0; i <= 173; i++) {
        rightServo.write(i);
        delay(5);
    }
}
void servoBakward() {
    for (int i = 180; i >= 0; i--) {
        leftServo.write(180-i);
        rightServo.write(i);
        delay(5);
    }
}
void leftServoBakward() {
    for (int i = 180; i >= 0; i--) {
        leftServo.write(180-i);
        delay(5);
    }
}
void rightServoBakward() {
    for (int i = 180; i >= 0; i--) {
        rightServo.write(i);
        delay(5);
    }
}
void countM1EncoderTicks() {
    m1Ticks++;
}
void countM2EncoderTicks() {
    m2Ticks++;
}
bool followLine() {
    // write code for line follow using sensor and motors
    int s1 = sensor1.getValue();
    int s2 = sensor2.getValue();
    int s3 = sensor3.getValue();
    int s4 = sensor4.getValue();
    int s5 = sensor5.getValue();

    // write code of line following robot with all 5 sensors
    // 00000
    if (s1 == BLACK && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == BLACK) {
        haltBack();
        return 1;
    } 
    // 11111
    else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == WHITE && s5 == WHITE) {
        forward(40);
    } 
    // 11110
    else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == WHITE && s5 == BLACK) {
        right90();
    } 
    // 11101
    else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == BLACK && s5 == WHITE) {
        right90();
    } 
    // 11100
    else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == BLACK && s5 == BLACK) {
        right90();
    } 
    // 11001
    else if (s1 == WHITE && s2 == WHITE && s3 == BLACK && s4 == BLACK && s5 == WHITE) {
        right90();
    } 
    // 11011
    else if (s1 == WHITE && s2 == WHITE && s3 == BLACK && s4 == WHITE && s5 == WHITE) {
        forward(40);
    } 
    // 11000
    else if (s1 == WHITE && s2 == WHITE && s3 == BLACK && s4 == BLACK && s5 == BLACK) {
        right90();
    } 
    // 10111
    else if (s1 == WHITE && s2 == BLACK && s3 == WHITE && s4 == WHITE && s5 == WHITE) {
        left90();
    }
    // 10011
    else if (s1 == WHITE && s2 == BLACK && s3 == BLACK && s4 == WHITE && s5 == WHITE) {
        left90();
    }  else if (s1 == WHITE && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == WHITE) {
        forward(40);
    } else if (s1 == BLACK && s2 == WHITE && s3 == WHITE && s4 == WHITE && s5 == WHITE) {
        left90();
    } else if (s1 == BLACK && s2 == BLACK && s3 == WHITE  && s4 == WHITE && s5 == WHITE) {
        left90();
    } else if (s1 == BLACK && s2 == BLACK && s3 == BLACK  && s4 == WHITE && s5 == WHITE) {
        left90();
    }

    return 0;
}
bool followLine3Sensors() {
    // write code for line follow using sensor and motors
    int s2 = sensor2.getValue();
    int s3 = sensor3.getValue();
    int s4 = sensor4.getValue();

    // write code of line following robot with all 5 sensors
    // 00000

    if (s2 == WHITE && s3 == WHITE && s4 == BLACK) {
        right90(30);
    } 
    else if (s2 == WHITE && s3 == BLACK && s4 == BLACK) {
        right90(30);
    } 
    else if (s2 == BLACK && s3 == WHITE && s4 == WHITE) {
        left90(30);
    } 
    else if (s2 == BLACK && s3 == BLACK && s4 == WHITE) {
        left90(30);
    } 
    else {
        forward(30);
    }
    
    return 0;
}
void blueSideCode() {
    /**************************
     *          T1
    **************************/
    // start forward
    forward(30);
    int counter = 0;
    while(1) {
        int s1 = sensor1.getValue();
        int s2 = sensor2.getValue();
        int s3 = sensor3.getValue();
        int s4 = sensor4.getValue();
        int s5 = sensor5.getValue();
        
        if (s1 == BLACK && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == BLACK) {
            if (counter != 0) {
                haltBack();
                break;
            } else {
                forward(40);
                delay(500);
                counter++;
            }
        } 
    }

    delay(500);
    resetTicks();
    while(m1Ticks < 140 || m2Ticks < 140) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        forward(40);
    }
    haltBack();
    delay(500);

    // turn right
    encoderRight90();
    delay(500);

    for(int i = 0; i < 7000; i++) {
        followLine3Sensors();
    }
    halt();

    // predict colors
    String leftColor = leftColorSensor.predict();
    String rightColor = rightColorSensor.predict();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoForward();
        }
        else if (leftColor == "Orange") {
            leftServoForward();
        }

        else if (rightColor == "Orange") {
            rightServoForward();
        }
    }
    delay(200);

    // // backward after picking balls
    resetTicks();
    while(m1Ticks < 100 || m2Ticks < 100) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        backward(15);
    }
    resetTicks();
    while(m1Ticks < 240 || m2Ticks < 240) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        backward(20);
    }
    halt();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoBakward();
        }
        else if (leftColor == "Orange") {
            leftServoBakward();
        }
        else if (rightColor == "Orange") {
            rightServoBakward();
        }
    }

    resetTicks();
    while(m1Ticks < 460 || m2Ticks < 460) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        left90();
    }
    halt();
    
    delay(300);
    // line follow
    while(1) {
        bool isBlackFound = followLine();

        if (isBlackFound) {
            break;
        }
    }
    delay(200);

    /************************
     *        Tree 2
    *************************/
    resetTicks();
    while(m1Ticks < 100 || m2Ticks < 100) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        forward(40);
    }
    haltBack();

    delay(200);

    // // turn right
    resetTicks();
    while(m1Ticks < 300 || m2Ticks < 300) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        right90();
    }
    halt();

    delay(200);

    // // forward after turn
    for(int i = 0; i < 7000; i++) {
        followLine3Sensors();
    }
    halt();

    delay(1000);

    // predict colors
    leftColor = leftColorSensor.predict();
    rightColor = rightColorSensor.predict();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoForward();
        }
        else if (leftColor == "Orange") {
            leftServoForward();
        }
        else if (rightColor == "Orange") {
            rightServoForward();
        }
    }
    delay(500);

    // // backward after picking balls
    resetTicks();
    while(m1Ticks < 200 || m2Ticks < 200) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        backward(20);
    }
    halt();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoBakward();
        }
        else if (leftColor == "Orange") {
            leftServoBakward();
        }
        else if (rightColor == "Orange") {
            rightServoBakward();
        }
    }

    delay(500);

    // turn right
    resetTicks();
    while(m1Ticks < 280 || m2Ticks < 280) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        left90();
    }
    halt();

    delay(1000);

    // line follow
    while(1) {
        bool isBlackFound = followLine();

        if (isBlackFound) {
            break;
        }
    }
    halt();
    delay(500);

    /************************
     *        Tree 3
    *************************/
    resetTicks();
    while(m1Ticks < 140 || m2Ticks < 140) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        forward(40);
    }
    haltBack();
    delay(800);

    // turn right
    encoderRight90();

    // resetTicks();
    // while(m1Ticks < 150 || m2Ticks < 150) {
    //     Serial.print(m1Ticks);
    //     Serial.print(" ");
    //     Serial.println(m2Ticks);
    //     followLine3Sensors();
    // }
    for(int i = 0; i < 7000; i++) {
        followLine3Sensors();
    }
    halt();
    delay(800);

    // predict colors
    leftColor = leftColorSensor.predict();
    rightColor = rightColorSensor.predict();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoForward();
        }
        else if (leftColor == "Orange") {
            leftServoForward();
        }

        else if (rightColor == "Orange") {
            rightServoForward();
        }
    }
    delay(500);

    // // backward after picking balls
    resetTicks();
    while(m1Ticks < 350 || m2Ticks < 350) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        backward(30);
    }
    halt();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoBakward();
        }
        else if (leftColor == "Orange") {
            leftServoBakward();
        }
        else if (rightColor == "Orange") {
            rightServoBakward();
        }
    }

    /**********************
     *       Parking
    ***********************/ 
    encoderLeft90();

    delay(500);

    resetTicks();
    for (int i = 0; i < 5000; i++) {
        forward(40);
    }

    rightSmallServo.attach(8);
    leftSmallServo.attach(9);

    leftSmallServo.write(0);
    rightSmallServo.write(60);
    delay(1000);

    encoderBackwardArcForBlue();
}
void redSideCode() {
    /**************************
     *          T1
    **************************/
    // start forward
    forward(30);
    int counter = 0;
    while(1) {
        int s1 = sensor1.getValue();
        int s2 = sensor2.getValue();
        int s3 = sensor3.getValue();
        int s4 = sensor4.getValue();
        int s5 = sensor5.getValue();
        
        if (s1 == BLACK && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == BLACK) {
            if (counter != 0) {
                halt();
                break;
            } else {
                forward(50);
                delay(500);
                counter++;
            }
        } 
    }

    delay(100);
    resetTicks();
    while(m1Ticks < 120 || m2Ticks < 120) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        forward(40);
    }
    haltBack();
    delay(500);

    // turn right
    encoderLeft90();
    delay(200);

    // resetTicks();
    // while(m1Ticks < 150 || m2Ticks < 150) {
    //     Serial.print(m1Ticks);
    //     Serial.print(" ");
    //     Serial.println(m2Ticks);
    //     followLine3Sensors();
    // }
    for(int i = 0; i < 7000; i++) {
        followLine3Sensors();
    }
    halt();
    delay(200);

    // predict colors
    String leftColor = leftColorSensor.predict();
    String rightColor = rightColorSensor.predict();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoForward();
        }
        else if (leftColor == "Orange") {
            leftServoForward();
        }

        else if (rightColor == "Orange") {
            rightServoForward();
        }
    }
    delay(200);

    // // backward after picking balls
    resetTicks();
    while(m1Ticks < 405 || m2Ticks < 405) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        backward(30);
    }
    halt();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoBakward();
        }
        else if (leftColor == "Orange") {
            leftServoBakward();
        }
        else if (rightColor == "Orange") {
            rightServoBakward();
        }
    }

    encoderRight180();
    
    delay(200);
    // line follow
    while(1) {
        bool isBlackFound = followLine();

        if (isBlackFound) {
            break;
        }
    }
    delay(200);

    /************************
     *        Tree 2
    *************************/
    resetTicks();
    while(m1Ticks < 120 || m2Ticks < 120) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        forward(40);
    }
    haltBack();

    delay(200);

    // // turn right
    resetTicks();
    while(m1Ticks < 300 || m2Ticks < 300) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        left90();
    }
    halt();

    delay(200);

    // // forward after turn
    for(int i = 0; i < 7000; i++) {
        followLine3Sensors();
    }
    halt();

    delay(200);

    // predict colors
    leftColor = leftColorSensor.predict();
    rightColor = rightColorSensor.predict();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoForward();
        }
        else if (leftColor == "Orange") {
            leftServoForward();
        }
        else if (rightColor == "Orange") {
            rightServoForward();
        }
    }
    delay(200);

    // // backward after picking balls
    resetTicks();
    while(m1Ticks < 200 || m2Ticks < 200) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        backward(30);
    }
    halt();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoBakward();
        }
        else if (leftColor == "Orange") {
            leftServoBakward();
        }
        else if (rightColor == "Orange") {
            rightServoBakward();
        }
    }

    delay(200);

    // turn right
    resetTicks();
    while(m1Ticks < 280 || m2Ticks < 280) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        right90();
    }
    halt();

    delay(200);

    // line follow
    while(1) {
        bool isBlackFound = followLine();

        if (isBlackFound) {
            break;
        }
    }
    halt();
    delay(1000);

    /************************
     *        Tree 3
    *************************/
    resetTicks();
    while(m1Ticks < 140 || m2Ticks < 140) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        forward(40);
    }
    haltBack();
    delay(200);

    // turn right
    encoderLeft90();
    delay(200);

    // resetTicks();
    // while(m1Ticks < 150 || m2Ticks < 150) {
    //     Serial.print(m1Ticks);
    //     Serial.print(" ");
    //     Serial.println(m2Ticks);
    //     followLine3Sensors();
    // }
    for(int i = 0; i < 7000; i++) {
        followLine3Sensors();
    }
    halt();
    delay(200);

    // predict colors
    leftColor = leftColorSensor.predict();
    rightColor = rightColorSensor.predict();

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoForward();
        }
        else if (leftColor == "Orange") {
            leftServoForward();
        }

        else if (rightColor == "Orange") {
            rightServoForward();
        }
    }
    delay(200);

    // // backward after picking balls
    resetTicks();
    while(m1Ticks < 250 || m2Ticks < 250) {
        Serial.print(m1Ticks);
        Serial.print(" ");
        Serial.println(m2Ticks);
        backward(30);
    }
    halt();
    delay(200);

    if (leftColor != "\0" || rightColor != "\0") { 
        if (rightColor == "Orange" && leftColor == "Orange") {
            servoBakward();
        }
        else if (leftColor == "Orange") {
            leftServoBakward();
        }
        else if (rightColor == "Orange") {
            rightServoBakward();
        }
    }

    /**********************
     *       Parking
    ***********************/
    encoderRight90();

    delay(500);

    rightSmallServo.attach(8);
    leftSmallServo.attach(9);

    leftSmallServo.write(00);
    rightSmallServo.write(60);

    resetTicks();
    for (int i = 0; i < 7000; i++) {
        forward(60);
    }


    encoderBackwardArcForRed();
}