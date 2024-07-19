#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid5.h"

/*
 * Grid 5 according to the Red Arena
 *
 *  grid is 3x3 the points are (3,1), (2,1) and (3,3)
 */
void blue_grid5()
{
  // ============= first tree and rock start =============
  // move forward until 3 strips
  forwardWithEncoder(50, 80);
  linefollowFiveUntil(3);
  delay(500);
  // turn left after 3 strips
  left90(80);
  delay(500);
  // move back to center on line
  backwardWithEncoder(50, 100);
  delay(500);
  // move servo down for pickup
  frontServo.write(0);
  delay(500);
  // move until first tree
  linefollowEncoder(270);
  delay(500);
  // move servo up after pickup
  frontServoMove(0, 90); // rock pickup
  delay(500);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(500);
  // turn left for rock
  leftTurnEncoder(80, 240);
  backServo.write(0);
  delay(500);
  // move back 3 strips
  backwardWithEncoder(50, 80);
  backLinefollowFiveUntil(3);
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
  // linefollowEncoder(410);
  linefollowUntil(2);
  linefollowEncoder(105);
  delay(500);
  // drop tree
  frontServoMove(90, 0); // rock drop
  delay(200);
  // move back 3 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowFiveUntil(3);
  delay(500);
  backLinefollowEncoder(85);
  delay(500);
  // drop rock
  backServoMove(90, 0); // tree drop
  delay(200);
  // ============= first tree and rock end =============

  // ============= second tree and rock =============
  // move back to intersection after rock drop
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServo.write(95);
  delay(500);
  // turn left
  //   left90(80);
  leftTurnEncoder(80, 240);
  delay(500);
  // move forward away from tree to adjust for line
  backLinefollowEncoder(100);
  delay(500);
  // move front servo down for tree pickup
  frontServo.write(0);
  delay(500);
  // move forward to tree
  linefollowEncoder(200);
  delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  left90(80);
  delay(500);
  // move back 2 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(100);
  // delay(500);
  backServoMove(0, 90);
  delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  // adjust to line for tree drop
  backLinefollowFiveEncoder(350);
  backLinefollowFiveUntil(1);
  delay(500);
  // linefollowEncoder(420);
  linefollowUntil(2);
  linefollowEncoder(105);
  // delay(500);
  // drop tree
  frontServoMove(90, 0);
  delay(200);
  // move back 2 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(90);
  delay(500);
  // drop rock
  backServoMove(90, 0);
  delay(200);
  // ============= second tree and rock =============

  // ============== third tree and rock start ==============
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  backLinefollowEncoder(100);
  linefollowUntil(2);
  delay(500);
  //   left90(80);
  leftTurnEncoder(80, 240);
  delay(500);
  backLinefollowEncoder(150);
  linefollowUntil(2);
  linefollowEncoder(100);
  frontServoMove(0, 90); // rock pickup
  delay(500);
  backLinefollowUntil(3);
  delay(500);

  backLinefollowEncoder(100);
  backServoMove(0, 90); // tree pickup
  delay(500);
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  backLinefollowFiveEncoder(350);
  backLinefollowFiveUntil(1);
  delay(500);
  // linefollowEncoder(410);
  linefollowUntil(2);
  linefollowEncoder(105);
  delay(500);
  frontServoMove(90, 0); // rock drop
  delay(200);
  backwardWithEncoder(50, 80);
  backLinefollowUntil(3);
  delay(500);
  backLinefollowEncoder(90);
  backServoMove(90, 0); // tree drop
  delay(200);
  // ============== third tree and rock end ==============

  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(500);
  left90(80);
  delay(500);
  linefollowEncoder(80);
  delay(500);
  backLinefollowUntil(5);
  backLinefollowEncoder(300);
}