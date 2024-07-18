#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/RedGrid2.h"

/*
 * Grid 2
 *
 *  grid is 3x3 the points are (1,3), (2,2) and (3,1)
 */

void red_grid2()
{
  linefollowEncoder(80);
  linefollowUntil(5);
  delay(500);
  right90(80);
  delay(500);

  // ============== first tree and rock start ==============
  backLinefollowEncoder(80);
  frontServo.write(0); // front servo
  delay(500);
  linefollowEncoder(150);
  // delay(500);
  frontServoMove(0, 90); // tree pick up
  linefollowUntil(1);
  delay(500);
  right90(80);
  backServo.write(0); // back servo down for pick up
  delay(500);
  backLinefollowEncoder(60);
  backLinefollowUntil(1);
  delay(200);
  backLinefollowEncoder(100);
  backServoMove(0, 90); // rock pick up
  delay(500);
  rightTurnEncoder(170, (220 * 2), 150); // 180 turn
  // delay(500);
  backLinefollowFiveEncoder(350);
  backLinefollowUntil(1);
  delay(500);
  linefollowUntil(2);
  linefollowEncoder(105);
  // delay(500);
  frontServoMove(90, 0); // rock drop
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  backLinefollowEncoder(80);
  backServoMove(90, 0); // tree drop
  // delay(500);
  // ============== first tree and rock end ==============

  // ============== second tree and rock start ==============
  frontServo.write(90);
  delay(500);
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  delay(500);
  linefollowFiveUntil(2);
  delay(500);
  right90(80);
  delay(500);
  linefollowFiveEncoder(150);
  delay(200);
  backLinefollowFiveEncoder(280);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(2);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  delay(500);
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  delay(500);
  // backLinefollowEncoder(410);
  backLinefollowUntil(2);
  backLinefollowEncoder(105);
  delay(500);
  backServoMove(90, 0); // rock drop
  // delay(500);
  forwardWithEncoder(50, 80);
  linefollowUntil(2);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(90, 0); // tree drop
  // ============== second tree and rock end ==============

  // ============== third tree and rock start ==============
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  delay(200);
  linefollowFiveUntil(2);
  delay(500);
  right90(80);
  delay(500);
  linefollowFiveEncoder(150);
  delay(200);
  backLinefollowFiveEncoder(280);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(3);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  delay(500);
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  delay(500);
  // backLinefollowEncoder(420);
  backLinefollowUntil(2);
  backLinefollowEncoder(105);
  delay(500);
  backServoMove(90, 0); // rock drop
  delay(500);
  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(500);
  linefollowEncoder(90);
  frontServoMove(90, 0); // tree drop
  backwardWithEncoder(50, 80);
  // ============== third tree and rock end ==============

  backLinefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  linefollowEncoder(80);
  delay(500);
  backLinefollowUntil(5);
  backLinefollowEncoder(300);
}