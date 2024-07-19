#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/RedGrid1.h"

/*
 * Grid 1
 *
 *  grid is 3x3 the points are (1,1), (2,2) and (3,3)
 */

void red_grid1()
{
  // move forward until 3 strips
  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(500);
  // turn right after 3 strips
  right90(80);
  delay(500);
  // move back to center on line
  backwardWithEncoder(50, 150);
  delay(500);
  // move servo down for pickup
  frontServo.write(0);
  delay(500);

  // ============= first tree and rock =============
  // move until first tree
  linefollowEncoder(280);
  // delay(500);
  // move servo up after pickup
  frontServoMove(0, 90);
  // delay(500);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  right90(80);
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
  // adjust to line for tree drop
  backLinefollowFiveEncoder(350);
  backLinefollowUntil(1);
  delay(500);
  linefollowFiveUntil(2);
  linefollowEncoder(105);
  delay(500);
  // drop tree
  frontServoMove(90, 0);
  delay(500);
  backwardWithEncoder(50, 80);
  // move back 3 strip to drop rock at original tree position
  backLinefollowUntil(3);
  delay(200);
  backLinefollowEncoder(90);
  // delay(300);
  // drop rock
  backServoMove(90, 0);
  delay(200);
  forwardWithEncoder(50, 80);
  // ============= first tree and rock =============

  // ============= second tree and rock =============
  // move back to intersection after rock drop
  linefollowUntil(1);
  // delay(500);
  // move front servo up for the turn
  frontServo.write(95);
  delay(500);
  // turn right
  right90(80);
  delay(500);
  // move forward away from tree to adjust for line
  backLinefollowFiveEncoder(100);
  delay(500);
  // move front servo down for tree pickup
  frontServo.write(0);
  delay(500);
  // move forward to tree
  linefollowFiveEncoder(250);
  delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  right90(80);
  delay(500);
  // move back 2 strips
  backLinefollowFiveEncoder(80);
  backLinefollowFiveUntil(2);
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
  backLinefollowUntil(1);
  delay(500);
  linefollowFiveUntil(2);
  linefollowEncoder(105);
  delay(300);
  // drop tree
  frontServoMove(90, 0);
  delay(500);
  // move back 2 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(90);
  delay(500);
  // drop rock
  backServoMove(90, 0);
  delay(500);
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
  right90(80);
  delay(500);
  // move forward away from tree to adjust for line
  backLinefollowFiveEncoder(100);
  delay(500);
  // move front servo down for tree pickup
  frontServo.write(0);
  delay(500);
  // move forward to tree
  linefollowFiveEncoder(230);
  delay(300);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  // delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  right90(80);
  delay(500);
  // move back 1 strips
  backLinefollowFiveEncoder(80);
  backLinefollowUntil(1);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(105);
  // delay(500);
  backServoMove(0, 90);
  delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  // adjust to line for tree drop
  backLinefollowFiveEncoder(350);
  backLinefollowUntil(1);
  delay(500);
  linefollowFiveUntil(2);
  linefollowEncoder(105);
  delay(300);
  // drop tree
  frontServoMove(90, 0);
  delay(500);
  // move back 1 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(500);
  backLinefollowEncoder(90);
  delay(500);
  // drop rock
  backServoMove(90, 0);
  delay(500);

  /// waqas code
  frontServo.write(100);
  delay(500);
  forwardWithEncoder(50, 80);
  linefollowUntil(1);
  linefollowEncoder(10);

  delay(500);
  left90(80);
  delay(500);
  linefollowEncoder(100);
  linefollowUntil(4);
  linefollowEncoder(300);
  delay(500);
}
