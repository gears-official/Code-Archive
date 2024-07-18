// #include <Arduino.h>
// #include "../include/IBTMotor.h"
// #include "../include/Sensor.h"

// /////////////////////////
// //        Motors
// /////////////////////////
// IBTMotor rightMotor(3, 2, 23, 25), leftMotor(5, 4, 24, 22);

// /////////////////////////
// //    Configuration
// /////////////////////////
// const float leftMotorAdjustment = 1.0f;
// const float rightMotorAdjustment = 2.0f;
// int count = 0;

// ///////////////////////////
// //       Sensors
// ///////////////////////////
// const int SENSOR_COUNT = 5;
// Sensor sensors[SENSOR_COUNT] = {
//   Sensor(DIGITAL, 8),
//   Sensor(DIGITAL, 9),
//   Sensor(DIGITAL, 10),
//   Sensor(DIGITAL, 11),
//   Sensor(DIGITAL, 12)
// };

// void test();
// void start();
// void forward(int speed);
// void backward(int speed);
// void right(int speed);
// void left(int speed);
// void stop();
// void printSensorValues(int sVals[]);
// void right90(int speed);
// void left90(int speed);
// void lineFollow();
// void lineFollow(int speed, int turnSpeed);
// void lineFollowUntilBlack();

// void setup() {
//   Serial.begin(9600);
  
//   start();
// }

// void loop() { }

// void start() {
//   int speed = 35;
//   int turnSpeed = 30;
//   int sVals[SENSOR_COUNT];
//   for (int i = 0; i < SENSOR_COUNT; i++) {
//     sVals[i] = sensors[i].getValue();
//   }

//   Serial.println("Start");
//   /////////////////////////////////////////////////////
//   // Keep moving forward until all sensors are black
//   /////////////////////////////////////////////////////
//   if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 0 && count == 0) {
//     bool prevAllBlack = true;
//     bool currentVals = true;
//     do {
//       if (count < 1) {
//         forward(speed);
//         for (int i = 0; i < SENSOR_COUNT; i++) {
//           sVals[i] = sensors[i].getValue();
//         }

//         currentVals = sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 0;
//         Serial.println(currentVals);

//       }
//     } while (prevAllBlack == currentVals);
//     count++;
//   }
//   stop();

//   /////////////////////////////////////////////////////
//   // follow line untill all sensors are black
//   /////////////////////////////////////////////////////
//   lineFollowUntilBlack();

//   forward(speed);
//   delay(3);
//   stop();

//   while (1) {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
//     if (sVals[2] == 0) {
//       break;
//     }
//     right90(speed);
//   }
//   stop();

//   // follow line untill 00011 or 00111
//   do {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
//     if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 1) {
//       break;
//     }
//     if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//       break;
//     }
//     lineFollow();
//   } while(1);
//   forward(speed);
//   delay(80);

//   stop();
//   delay(200);


//   // turn left untill middle sensor is black
//   while (1) {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
//     if (sVals[2] == 0) {
//       break;
//     }
//     left90(speed);
//   }
//   stop();
//   delay(100)

//   // follow line untill 00011 or 00111
//   do {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
//     if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 1) {
//       break;
//     }
//     if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//       break;
//     }
//     lineFollow();
//   } while(1);
//   forward(30);
//   delay(100);

//   stop();
//   delay(200);

//   // turn right untill middle sensor is black
//   while (1) {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
//     if (sVals[2] == 0) {
//       break;
//     }
//     left90(speed+20);
//   }
//   stop();
//   delay(100);

//   // follow line untill 11000 or 11100
//   do {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
//     if (sVals[4] == 0) {
//       break;
//     }
//     lineFollow();
//   } while(1);
//   stop();
//   delay(200);

//   // forward in arch
//   rightMotor.forward(30);
//   leftMotor.forward(50);
//   delay(200);
//   stop();
//   delay(200);
  
//   // turn right untill middle sensor on black
//   while (1) {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
//     if (sVals[2] == 0) {
//       break;
//     }
//     right90(turnSpeed+20);
//   }
//   stop();

//   while(1) {
//     lineFollow();
//   }
// }

// void forward(int speed) {
//   rightMotor.forward(speed * rightMotorAdjustment);
//   leftMotor.forward(speed * leftMotorAdjustment);
// }

// void backward(int speed) {
//   rightMotor.backward(speed * rightMotorAdjustment);
//   leftMotor.backward(speed * leftMotorAdjustment);
// }

// ///////////////////////////
// //    Sharp Turns
// ///////////////////////////
// void right90(int speed) {
//   rightMotor.backward(speed);
//   leftMotor.forward(speed);
// }
// void left90(int speed) {
//   rightMotor.forward(speed);
//   leftMotor.backward(speed);
// }

// ///////////////////////////
// //    Soft Turns
// ///////////////////////////
// void right(int speed) {
//   rightMotor.backward(0);
//   leftMotor.forward(speed);
// }

// void left(int speed) {
//   rightMotor.forward(speed);
//   leftMotor.backward(0);
// }

// ///////////////////////////
// //      Line Follow
// ///////////////////////////
// void lineFollow() {
//   int speed = 30;
//   int turnSpeed = 20;
//   int sVals[SENSOR_COUNT];
//   for (int i = 0; i < SENSOR_COUNT; i++) {
//     sVals[i] = sensors[i].getValue();
//   }

//   // 00000
//   if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 0) {
//     while(1) {
//       for (int i = 0; i < SENSOR_COUNT; i++) {
//         sVals[i] = sensors[i].getValue();
//       }

//       if ((sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 0)) {
//         forward(speed);
//       }
//       else {
//         break;
//       }
//     }
//   }
//   // 11011
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 1) {
//     forward(speed);
//   }
//   // 10111
//   else if (sVals[0] == 1  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//     left90(turnSpeed);
//   }
//   // 01111
//   else if (sVals[0] == 0  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//     left90(turnSpeed);
//   }
//   // 11101
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 0 && sVals[4] == 1) {
//     right90(turnSpeed);
//   }
//   // 11110
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 0) {
//     right90(turnSpeed);
//   }
//   // SPECIAL CASES
//   // 00011
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 1) {
//     stop();
//     left90(speed+10);
//   }
//   // 00111
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//     stop();
//     left90(speed+10);
//     delay(150);
//   }
//   // 11000
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 0) {
//     stop();
//     right90(speed+10);
//     delay(150);
//   }
//   // 11100
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 0 && sVals[4] == 0) {
//     stop();
//     right90(speed+10);
//     delay(150);
//   }
//   // 00001
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 1) {
//     stop();
//     left90(speed+10);
//     delay(150);
//   }
//   // 00010
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 0) {
//     forward(speed);
//   }
//    // 00110
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 0) {
//     forward(speed);
//   }
// }

// void lineFollow(int speed, int turnSpeed) {
//   int sVals[SENSOR_COUNT];
//   for (int i = 0; i < SENSOR_COUNT; i++) {
//     sVals[i] = sensors[i].getValue();
//   }

//   // 11011
//   if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 1) {
//     forward(speed);
//   }
//   // 10111
//   else if (sVals[0] == 1  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//     left90(turnSpeed);
//   }
//   // 01111
//   else if (sVals[0] == 0  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//     left90(turnSpeed);
//   }
//   // 11101
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 0 && sVals[4] == 1) {
//     right90(turnSpeed);
//   }
//   // 11110
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 0) {
//     right90(turnSpeed);
//   }
//   // SPECIAL CASES
//   // 00011
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 1) {
//     stop();
//     left90(speed+10);
//   }
//   // 00111
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//     stop();
//     left90(speed+10);
//     delay(150);
//   }
//   // 11000
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 0) {
//     stop();
//     right90(speed+10);
//     delay(150);
//   }
//   // 11100
//   else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 0 && sVals[4] == 0) {
//     stop();
//     right90(speed+10);
//     delay(150);
//   }
//   // 00001
//   else if (sVals[0] == 0  && sVals[1] == 0 && sVals[2] == 0 && sVals[3] == 0 && sVals[4] == 1) {
//     stop();
//     left90(speed+10);
//     delay(150);
//   }
// }

// // line follow untill black
// void lineFollowUntilBlack() {
//   int speed = 30;
//   int turnSpeed = 20;
//   int sVals[SENSOR_COUNT];

//   do {
//     for (int i = 0; i < SENSOR_COUNT; i++) {
//       sVals[i] = sensors[i].getValue();
//     }
    
//     // 11011
//     if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 0 && sVals[3] == 1 && sVals[4] == 1) {
//       forward(speed);
//     }
//     // 10111
//     else if (sVals[0] == 1  && sVals[1] == 0 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//       left90(turnSpeed);
//     }
//     // 01111
//     else if (sVals[0] == 0  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 1) {
//       left90(turnSpeed);
//     }
//     // 11101
//     else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 0 && sVals[4] == 1) {
//       right90(turnSpeed);
//     }
//     // 11110
//     else if (sVals[0] == 1  && sVals[1] == 1 && sVals[2] == 1 && sVals[3] == 1 && sVals[4] == 0) {
//       right90(turnSpeed);
//     }
//   } while(sVals[0] != 0  || sVals[1] != 0 || sVals[2] != 0 || sVals[3] != 0 || sVals[4] != 0);
//   stop();
// }
// void stop() {
//   rightMotor.stop();
//   leftMotor.stop();
// }

// void printSensorValues(int sVals[]) {
//   for (int i = 0; i < SENSOR_COUNT; i++) {
//     Serial.print(sVals[i]);
//     Serial.print(" ");
//   }
//   // Serial.println();
// }

// // test funciton
// void test() {
//   int speed = 50;

//   forward(speed);
//   delay(1000);
//   stop();
//   delay(1000);
//   backward(speed);
//   delay(1000);
//   stop();
//   delay(1000);
// }
