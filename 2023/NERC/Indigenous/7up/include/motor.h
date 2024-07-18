/**
 * @file motor.h
 * @brief This file contains the definition of the class Motor.
 * @author Zafeer Hafeez (IIvexII)
 * @version 0.1
 */
// add include guard
#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
private:
  int pos;
  int neg;
  int speedControl;
  float error;
  
public:
  // Constructor
  Motor(int positive, int negative, int speed, float error);
  Motor(int positive, int negative, int speed);

  /**
   * @brief This function is used to move the motor forward.
   * @param None
   * @return None
   */
  void forward();
  /**
   * @brief This function is used to move the motor backward.
   * @param None
   * @return None
   */
  void backward();

  /**
   * @brief This function is used to set the speed of the motor.
   * @param speed The speed of the motor.
   * @return None
   */
  void setSpeed(short int speed);

  /**
   * @brief This function is used to stop the motor.
   *
   * @param None
   */
  void halt()
  {
    digitalWrite(pos, LOW);
    digitalWrite(neg, LOW);
  }
};

#include "../lib/motor.cpp"

#endif