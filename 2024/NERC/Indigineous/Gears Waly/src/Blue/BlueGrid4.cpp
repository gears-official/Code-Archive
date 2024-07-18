#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid4.h"

/*
 * Grid 4 according to the Red Arena
 *
 *  grid is 3x3 the points are (2,1), (2,2) and (2,3)
 */

void blue_grid4()
{
  // ============= first tree and rock start =============
  // move forward until 4 strips
  linefollowFiveEncoder(100);
  linefollowFiveUntil(4);
  delay(500);
  // turn left after 4 strips
  left90(80);
  delay(500);
  // move back to center on line
  backLinefollowFiveEncoder(90);
  // delay(500);
  // move servo down for pickup
  frontServo.write(0);
  delay(500);
  // move until first tree
  linefollowEncoder(200);
  // delay(500);
  // move servo up after pickup
  frontServoMove(0, 90); // rock pickup
  // delay(500);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  left90(80);
  backServo.write(0);
  delay(500);
  // move back 2 strips
  backLinefollowFiveEncoder(100);
  backLinefollowFiveUntil(2);
  delay(500);
  // move to pick up rock
  backLinefollowFiveEncoder(100);
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
  // linefollowEncoder(420);
  linefollowUntil(2);
  linefollowEncoder(105);
  // delay(500);
  // drop tree
  frontServoMove(90, 0); // rock drop
  delay(200);
  // move back 2 strip to drop rock at original tree position
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(90);
  // delay(500);
  // drop rock
  backServoMove(90, 0); // tree drop
  // delay(500);
  // ============= first tree and rock end =============

  // ============= second tree and rock start =============
  frontServo.write(0);
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
  backLinefollowFiveEncoder(100);
  linefollowFiveEncoder(230);
  frontServoMove(0, 90); // rock pickup
  backServo.write(0);
  delay(500);
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(100);
  backServoMove(0, 90); // tree pickup
  delay(500);
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  backLinefollowFiveEncoder(350);
  backLinefollowFiveUntil(1);
  delay(500);
  // linefollowEncoder(420);
  linefollowUntil(2);
  linefollowEncoder(105);
  // delay(500);
  frontServoMove(90, 0); // rock drop
  delay(200);
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(90);
  backServoMove(90, 0); // tree drop
  delay(200);
  // ============= second tree and rock end =============

  // ============= third tree and rock start ===========
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
  backLinefollowFiveEncoder(100);
  linefollowFiveEncoder(230);
  frontServoMove(0, 90); // rock pickup
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(100);
  backServoMove(0, 90); // tree pickup
  delay(500);
  rightTurnEncoder(170, (220 * 2), 150);
  // delay(500);
  backLinefollowFiveEncoder(350);
  backLinefollowFiveUntil(1);
  delay(500);
  // linefollowEncoder(420);
  linefollowUntil(2);
  linefollowEncoder(105);
  // delay(500);
  frontServoMove(90, 0); // rock drop
  delay(200);
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(90);
  delay(200);
  backServoMove(90, 0); // tree drop
  delay(200);
  // ================ third tree and rock end =============

  forwardWithEncoder(50, 80);
  linefollowUntil(2);
  delay(500);
  left90(80);
  delay(500);
  linefollowEncoder(100);
  delay(500);
  backLinefollowUntil(5);
  backLinefollowEncoder(300);
}
