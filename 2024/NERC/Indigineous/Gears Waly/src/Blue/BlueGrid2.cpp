#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid2.h"

/*
 * Grid 2 According to the Blue Arena
 *
 *  grid is 3x3 the points are (1,3), (2,2) and (3,1)
 */

void blue_grid2()
{
  // ============== first tree and rock start ==============
  linefollowFiveEncoder(80);
  linefollowFiveUntil(5);
  delay(500);
  left90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  frontServo.write(0); // front servo
  delay(500);
  linefollowFiveEncoder(150);
  // delay(500);
  frontServoMove(0, 90); // tree pick up
  linefollowUntil(1);
  delay(500);
  left90(80);
  backServo.write(0); // back servo down for pick up
  delay(500);
  backLinefollowFiveEncoder(60);
  backLinefollowFiveUntil(1);
  delay(500);
  backLinefollowEncoder(100);
  backServoMove(0, 90); // rock pick up
  delay(500);
  rightTurnEncoder(170, (220 * 2), 150); // 180 turn
  // delay(500);
  backLinefollowFiveEncoder(350);
  backLinefollowUntil(1);
  delay(500);
  // linefollowEncoder(410);
  linefollowUntil(2);
  linefollowEncoder(105);
  // delay(500);
  frontServoMove(90, 0); // rock drop
  delay(200);
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  backLinefollowEncoder(80);
  backServoMove(90, 0); // tree drop
  // delay(200);
  // ============== first tree and rock end ==============

  // ============== second tree and rock start ==============
  frontServo.write(90);
  delay(500);
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  delay(500);
  linefollowFiveUntil(2);
  delay(500);
  left90(80);
  delay(500);
  linefollowFiveEncoder(150);
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
  linefollowUntil(1);
  delay(500);
  // backLinefollowEncoder(420);
  backLinefollowUntil(2);
  backLinefollowEncoder(105);
  // delay(500);
  backServoMove(90, 0); // rock drop
  delay(200);
  forwardWithEncoder(50, 80);
  linefollowUntil(2);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(90, 0); // tree drop
  // ============== second tree and rock end ==============

  // ============== third tree and rock start ==============
  delay(200);
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  linefollowFiveUntil(2);
  delay(500);
  left90(80);
  delay(500);
  linefollowFiveEncoder(150);
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
  linefollowUntil(1);
  delay(500);
  // backLinefollowEncoder(420);
  backLinefollowUntil(2);
  backLinefollowEncoder(105);
  // delay(500);
  backServoMove(90, 0); // rock drop
  delay(200);
  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(500);
  linefollowEncoder(90);
  frontServoMove(90, 0); // tree drop
  // ============== third tree and rock end ==============
  delay(200);
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  linefollowEncoder(80);
  delay(500);
  backLinefollowUntil(5);
  backLinefollowEncoder(300);
}