#ifndef CONFIG_H
#define CONFIG_H

//////////////////////////
// Sonar Configurations
//////////////////////////
int trigPin = 22;
int echoPin = 24;

//////////////////////////
// Servo Configurations
//////////////////////////
int servoPin = 32;

//////////////////////////
// Encoder Configurations
//////////////////////////
int leftEncoderPin = 2;
int rightEncoderPin = 3;

///////////////////////////
// Sensor Configurations
///////////////////////////
int threshold = 800;

// Middle sensors
int leftMiddleSensorPin = 28;
int rightMiddleSensorPin = 30;  


////////////////////////////////
//  Delay Between Instructions
////////////////////////////////
int delayTime = 400;

// dip switch
int dipSwitchPin1 = 46;
int dipSwitchPin2 = 40;
int dipSwitchPin4 = 42;
int dipSwitchPin8 = 44;
#endif