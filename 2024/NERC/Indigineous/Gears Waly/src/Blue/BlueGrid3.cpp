#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid3.h"

/*
 * Grid 3 according to the Red Arena
 *
 *  grid is 3x3 the points are (1,1), (1,2) and (1,3)
 */

void blue_grid3()
{
  // ============= first tree and rock start =============
  // move forward until 5 strips
  linefollowFiveEncoder(100);
  linefollowFiveUntil(5);
  delay(500);
  // turn left after 5 strips
  left90(80);
  delay(500);
  // move back to center on line
  backLinefollowEncoder(110);
  delay(500);
  // move servo down for pickup
  frontServo.write(0);
  delay(500);
  // move until first tree
  linefollowEncoder(220);
  // delay(500);
  // move servo up after pickup
  frontServoMove(0, 90); // rock pickup
  // delay(500);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(500);
  // turn left for rock
  leftTurnEncoder(80, 240);
  backServo.write(0);
  delay(500);
  // move back 1 strips
  backLinefollowFiveEncoder(100);
  backLinefollowUntil(1);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(100);
  // delay(500);
  backServoMove(0, 90); // tree pickup
  delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  // adjust to line for tree drop
  backLinefollowFiveEncoder(350);
  backLinefollowFiveUntil(1);
  delay(500);
  // linefollowEncoder(400);
  linefollowUntil(2);
  linefollowEncoder(105);
  // delay(500);
  // drop tree
  frontServoMove(90, 0); // rock drop
  delay(200);
  // move back 1 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  backLinefollowEncoder(90);
  // delay(500);
  // drop rock
  backServoMove(90, 0); // tree drop
  // delay(200);
  // ============= first tree and rock end =============

  // ============= second tree and rock start =============
  frontServo.write(90);
  delay(500);
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  backLinefollowFiveEncoder(150);
  linefollowFiveUntil(2);
  delay(500);
  left90(80);
  delay(500);
  linefollowFiveEncoder(100);
  backLinefollowFiveEncoder(220);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(1);
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
  // delay(500);
  backServoMove(90, 0); // rock drop
  delay(200);
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(90, 0); // tree drop
  delay(200);
  // ============= second tree and rock end =============

  // ============= third tree and rock start ===========
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  frontServo.write(90);
  delay(500);
  backLinefollowFiveEncoder(150);
  linefollowFiveUntil(2);
  delay(500);
  left90(80);
  delay(500);
  linefollowFiveEncoder(100);
  backLinefollowFiveEncoder(220);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(1);
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
  // delay(500);
  backServoMove(90, 0); // rock drop
  delay(200);
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  linefollowEncoder(105);
  frontServoMove(90, 0); // tree drop
  delay(200);
  // ================ third tree and rock end =============

  backwardWithEncoder(50, 80);
  backLinefollowFiveUntil(1);
  delay(500);
  left90(80);
  delay(500);
  linefollowFiveEncoder(75);
  delay(500);
  backLinefollowFiveUntil(5);
  backLinefollowFiveEncoder(300);
}