#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid1.h"

/*
 * Grid 1
 *
 *  grid is 3x3 the points are (1,1), (2,2) and (3,3)
 */

void blue_grid1()
{
  // move forward until 3 strips
  forwardWithEncoder(50, 80);
  linefollowFiveUntil(3);
  delay(500);
  // turn right after 3 strips
  left90(80);
  delay(500);
  // move back to center on line
  backLinefollowFiveEncoder(150);
  delay(500);
  // move servo down for pickup
  // frontServoMove(95, 0);
  frontServo.write(0);

  delay(500);

  // ============= first tree and rock =============
  // move until first tree
  linefollowFiveEncoder(305);
  // delay(500);
  // move servo up after pickup
  frontServoMove(0, 90);
  delay(200);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(500);
  // turn left for rock
  left90(80);
  backServo.write(0);
  // backServoMove(95, 0);
  delay(500);
  // move back 3 strips
  backLinefollowFiveEncoder(80);
  backLinefollowFiveUntil(3);
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
  // move back 3 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowUntil(3);
  delay(500);
  backLinefollowEncoder(105);
  // delay(500);
  // drop rock
  backServoMove(90, 0);
  delay(200);
  //============= first tree and rock =============

  // ============= second tree and rock =============
  // move back to intersection after rock drop
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServo.write(95);
  delay(500);
  // turn right
  left90(80);
  delay(500);
  // move forward away from tree to adjust for line
  backLinefollowFiveEncoder(100);
  delay(500);
  // move front servo down for tree pickup
  frontServo.write(0);
  delay(500);
  // move forward to tree
  linefollowFiveEncoder(200);
  // delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  // delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  left90(80);
  delay(500);
  // move back 2 strips
  backLinefollowFiveEncoder(80);
  backLinefollowUntil(2);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(110);
  // delay(500);
  backServoMove(0, 90);
  delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2), 150);
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
  backLinefollowEncoder(105);
  // delay(500);
  // drop rock
  backServoMove(90, 0);
  delay(200);
  // ============= second tree and rock =============

  // ============= third tree and rock =============
  // move back to intersection after rock drop
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServo.write(95);
  delay(500);
  // turn right
  left90(80);
  delay(500);
  // move forward away from tree to adjust for line
  backLinefollowEncoder(100);
  delay(500);
  // move front servo down for tree pickup
  frontServo.write(0);
  delay(500);
  // move forward to tree
  linefollowEncoder(185);
  // delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  // delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  left90(80);
  delay(500);
  // move back 1 strips
  backLinefollowFiveEncoder(80);
  backLinefollowUntil(1);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(100);
  // delay(500);
  backServoMove(0, 90);
  delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2), 150);
  // adjust to line for tree drop
  backLinefollowFiveEncoder(350);
  backLinefollowFiveUntil(1);
  delay(500);
  // linefollowEncoder(420);
  linefollowUntil(2);
  linefollowEncoder(105);
  delay(500);
  // drop tree
  frontServoMove(90, 0);
  delay(200);
  // move back 1 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  backLinefollowEncoder(105);
  // delay(500);
  // drop rock
  backServoMove(90, 0);
  delay(200);

  /// waqas code
  frontServo.write(100);
  delay(500);
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  linefollowEncoder(10);

  delay(500);
  right90(80);
  delay(500);
  linefollowFiveEncoder(60);
  linefollowFiveUntil(5);
  linefollowFiveEncoder(300);
  delay(500);
}
