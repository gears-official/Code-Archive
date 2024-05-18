#include "../include/motor.h"
#include <Arduino.h>
////////////////////////////////////
//           Constructor
////////////////////////////////////

Motor::Motor(int positive, int negative, int speed) 
{
       // Assigning pins
    this->pos = positive;
    this->neg = negative;
    this->speedControl = speed;
    this->error = 1.0;

    // Setting pins as output
    pinMode(neg, OUTPUT);
    pinMode(pos, OUTPUT);
    pinMode(speedControl, OUTPUT); 

    // Making negtive pin as ground
    digitalWrite(neg, LOW);
}
Motor::Motor(int positive, int negative, int speed, float error) 
{
    // Assigning pins
    this->pos = positive;
    this->neg = negative;
    this->speedControl = speed;
    this->error = error;

    // Setting pins as output
    pinMode(neg, OUTPUT);
    pinMode(pos, OUTPUT);
    pinMode(speedControl, OUTPUT); 

    // Making negtive pin as ground
    digitalWrite(neg, LOW);
}

////////////////////////////////////
//           forward()
////////////////////////////////////
void Motor::forward()
{
    digitalWrite(pos, HIGH);
    digitalWrite(neg, LOW); 
}

////////////////////////////////////
//           backward()
////////////////////////////////////
void Motor::

backward()
{
    digitalWrite(pos, LOW);
    digitalWrite(neg, HIGH); 
}

////////////////////////////////////
//           speed()
////////////////////////////////////
void Motor::setSpeed(short int speed)
{
    analogWrite(speedControl, (speed * this->error)); 

}