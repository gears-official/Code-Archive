int rightMotorForward = 9;
int rightMotorBackward = 10;
int leftMotorForward = 11;
int leftMotorBackward = 12;

int leftEncoderTicks = 0;
int rightEncoderTicks = 0;

int leftMostSensor = A0;
int leftSensor = A1;
int centerSensor = A2;
int rightSensor = A3;
int rightMostSensor = A4;

int rightSpeed = 255;
int leftSpeed = 255;

int leftTurn = 255;
int rightTurn = 255;

int turn = 0;

int threshold = 700;

int rightEncoderPin = 2;
int leftEncoderPin = 3;

int enc1_count = 0;
int enc2_count = 0;

int stripCount = 0;
bool onBlack = false;

void forward();
void backward();
void left();
void right();
void halt();
void stop();
void rightEncoder();
void leftEncoder();
void lineFollow();
void left90();
void leftUntilMiddle();
void right90();
void sensorValue();
int digitalValue(int);
void leftEncoderTurn(int);
void rightEncoderTurn(int);
void lineFollowUntil(int);

void setup()
{
  Serial.begin(9600);

  pinMode(leftEncoderPin, INPUT);
  pinMode(rightEncoderPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(leftEncoderPin), leftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPin), rightEncoder, RISING);

  pinMode(leftMostSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(rightMostSensor, INPUT);

  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);

 
}

void loop() {}

///////////////////
// Functions
///////////////////
void stop()
{
  analogWrite(rightMotorForward, 0);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, 0);
  analogWrite(leftMotorBackward, 0);
}
void halt()
{
  analogWrite(rightMotorForward, 255);
  analogWrite(rightMotorBackward, 255);
  analogWrite(leftMotorForward, 255);
  analogWrite(leftMotorBackward, 255);
}
void lineFollow()
{

  int ls = digitalValue(analogRead(leftSensor));
  int cs = digitalValue(analogRead(centerSensor));
  int rs = digitalValue(analogRead(rightSensor));

  if (ls == 1 && cs == 0 && rs == 1)
  {
    forward();
  }
  else if (ls == 0 && cs == 1 && rs == 1)
  {
    right();
  }
  else if (ls == 1 && cs == 1 && rs == 0)
  {
    left();
  }
  else if (ls == 0 && cs == 0 && rs == 1)
  {
    right();
  }
  else if (ls == 1 && cs == 0 && rs == 0)
  {
    left();
  }
}
void forward()
{
  analogWrite(rightMotorForward, speed);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, speed);
  analogWrite(leftMotorBackward, 0);
}
void backward()
{
  analogWrite(rightMotorForward, 0);
  analogWrite(rightMotorBackward, rightSpeed);
  analogWrite(leftMotorForward, 0);
  analogWrite(leftMotorBackward, leftSpeed);
}
void left()
{
  analogWrite(rightMotorForward, leftTurn);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, turn);
  analogWrite(leftMotorBackward, 0);
}
void left90()
{
  analogWrite(rightMotorForward, rightTurn);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, 0);
  analogWrite(leftMotorBackward, leftTurn);
}
void leftUntilMiddle() {
  leftEncoderTurn(100);
  while (digitalValue(analogRead(centerSensor)) != 0 && digitalValue(analogRead(leftSensor)) == 1)
  {
    right90();
  }
  halt();
  
}

void right()
{
  analogWrite(rightMotorForward, turn);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, rightTurn);
  analogWrite(leftMotorBackward, 0);
}
void right90()
{
  analogWrite(rightMotorForward, 0);
  analogWrite(rightMotorBackward, rightTurn);
  analogWrite(leftMotorForward, leftTurn);
  analogWrite(leftMotorBackward, 0);
}
void leftEncoder()
{
  leftEncoderTicks++;
}
void rightEncoder()
{
  rightEncoderTicks++;
}
int digitalValue(int sensorValue)
{
  return (sensorValue > threshold) ? 1 : 0;
}
void sensorValue()
{
  int lms = digitalValue(analogRead(leftMostSensor));
  int ls = digitalValue(analogRead(leftSensor));
  int cs = digitalValue(analogRead(centerSensor));
  int rs = digitalValue(analogRead(rightSensor));
  int rms = digitalValue(analogRead(rightMostSensor));

  Serial.print(lms);
  Serial.print(" ");
  Serial.print(ls);
  Serial.print(" ");
  Serial.print(cs);
  Serial.print(" ");
  Serial.print(rs);
  Serial.print(" ");
  Serial.print(rms);
  Serial.println(" ");
}
void leftEncoderTurn(int Ticks)
{
  leftEncoderTicks = 0;
  rightEncoderTicks = 0;
  while (rightEncoderTicks < Ticks)
  {
    Serial.println(rightEncoderTicks);
    right90();
  }

  halt();
}
void rightEncoderTurn(int Ticks)
{
  leftEncoderTicks = 0;
  rightEncoderTicks = 0;
  while (leftEncoderTicks < Ticks)
  {
    Serial.println(leftEncoderTicks);
    left90();
  }

  halt();
  delay(20);
}
void lineFollow(int &currentCounter, int targetCounter, int lm, int l, int m, int r, int rm)
{

  // Simple Logic for Line Folllow
  if (l == 1 && m == 0 && r == 1)
  {
    forward();
  }
  else if (l == 0 && m == 1 && r == 1)
  {
    right();
  }
  else if (l == 1 && m == 1 && r == 0)
  {
    left();
  }
  else if (l == 0 && m == 0 && r == 1)
  {
    right();
  }
  else if (l == 1 && m == 0 && r == 0)
  {
    left();
  }

  /// Extra Conditions for 5 Sensors line Follow
  else if (lm == 0 && l == 1 && m == 1 && r == 1 && rm == 1)
  {
    right();
  }
  else if (lm == 1 && l == 1 && m == 1 && r == 1 && rm == 0)
  {
    left();
  }
  else if (lm == 0 && l == 0 && m == 1 && r == 1 && rm == 1)
  {
    right();
  }
  else if (lm == 1 && l == 1 && m == 1 && r == 0 && rm == 0)
  {
    left();
  }

  else if (lm == 0 && l == 0 && m == 0 && r == 0 && rm == 0)
  {
    currentCounter++;
    if (currentCounter != targetCounter)
    {
      forward();
      delay(100);
    }
  }
}
void lineFollowUntil(int untilCount)
{
  int counter = 0;

  while (counter < untilCount)
  {
    int lms = digitalValue(analogRead(leftMostSensor));
    int ls = digitalValue(analogRead(leftSensor));
    int cs = digitalValue(analogRead(centerSensor));
    int rs = digitalValue(analogRead(rightSensor));
    int rms = digitalValue(analogRead(rightMostSensor));

    lineFollow(
        counter,
        untilCount,
        lms, ls, cs, rs, rms);
    if (counter >= untilCount)
    {

      backward();
      delay(150);
      halt();
      break;
    }
    Serial.print(lms);
    Serial.print(" ");
    Serial.print(ls);
    Serial.print(" ");
    Serial.print(cs);
    Serial.print(" ");
    Serial.print(rs);
    Serial.print(" ");
    Serial.print(rms);
    Serial.print(" ");
    Serial.println(counter);
  }
}
