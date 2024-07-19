// Motor Left
#define leftForward 5 //orange //1
#define leftBackward 6 //red //2

// Motor Right
#define rightForward 10 //black // 2
#define rightBackward 11 //orange //1

#define lm 7
#define l 8
#define cen 9
#define r 12
#define rm 13

int lSpeed = 250;//250; //205
int rSpeed = 245;//245; //200

int slightTurnSpeed = 60;  // Increased slight turn speed for faster turns
int sharpleft = 200; // Increased sharp turn speed for faster and smoother turns
int sharpright = 160; //200 // Increased sharp turn speed for faster and smoother turns

void setup() {
  // Motor Left
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);

  // Motor Right
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(lm, INPUT);
  pinMode(l, INPUT);
  pinMode(cen, INPUT);
  pinMode(r, INPUT);
  pinMode(rm, INPUT);

  Serial.begin(9600);

  lineFollowUntil(4);
  delay(250);   //delay(50)
  SharpRight();

  lineFollowUntil(4);
  delay(250);
  SharpRight();
  
  lineFollowUntil(4);
  delay(250);
  SharpLeft();

  lineFollowUntil(3);
  delay(250);
  SharpLeft();

  lineFollowUntil(3);
  delay(250);
  Slightleft();
  delay(200);
  
  moveForward();
  delay(1200);
  stop();
}

void loop() {
}

////////////////////////////////////////////
void moveForward() {
  //left motor
  analogWrite(leftForward, lSpeed);
  analogWrite(leftBackward, 0);

  //Right Motor
  analogWrite(rightForward, rSpeed);
  analogWrite(rightBackward, 0);
}

void backward() {
  //Left motor
  analogWrite(leftForward, 0);
  analogWrite(leftBackward, lSpeed);

  //Right motor
  analogWrite(rightForward, 0);
  analogWrite(rightBackward, rSpeed);
}

void stop() {
  analogWrite(leftForward, 0);
  analogWrite(leftBackward, 0);

  analogWrite(rightForward, 0);
  analogWrite(rightBackward, 0);
}

void halt(){
  analogWrite(leftForward, 255);
  analogWrite(leftBackward, 255);

  analogWrite(rightForward, 255);
  analogWrite(rightBackward, 255);
}

//*Slight**
void Slightright() {
  // Left motor
  analogWrite(leftForward, lSpeed);
  analogWrite(leftBackward, 0);

  // Right motor
  analogWrite(rightForward, slightTurnSpeed);
  analogWrite(rightBackward, 0);
}

void Slightleft() {
  // Left motor
  analogWrite(leftForward, slightTurnSpeed);
  analogWrite(leftBackward, 0);

  // Right motor
  analogWrite(rightForward, rSpeed);
  analogWrite(rightBackward,  0);
}

//*Sharp**
void SharpRight(){
  //left
  analogWrite(leftForward, sharpleft);
  analogWrite(leftBackward, 0);

  //Right
  analogWrite(rightForward, 0);
  analogWrite(rightBackward, sharpright);

  delay(240); // Reduced delay for faster turn
}

void SharpLeft(){
  //left
  analogWrite(leftForward, 0);
  analogWrite(leftBackward, sharpleft);

  //Right
  analogWrite(rightForward, sharpright);
  analogWrite(rightBackward, 0);

  delay(260); // Reduced delay for faster turn
}

/////////////////////////////////////////////////////////

void lineFollow(int &currentCounter, int targetCounter, int leftMost, int left, int center, int right, int rightMost)
{
  // Simple Logic for Line Folllow
  if (left == 1 && center == 0 && right == 1 )
  {
    moveForward();
  }
  else if (left == 0 && center == 1 && right == 1)
  {
    Slightleft();
  }
  else if (left == 1 && center == 1 && right == 0)
  {
    Slightright();
  }
  else if (left == 0 && center == 0 && right == 1)
  {
    Slightleft();
  }
  else if (left == 1 && center == 0 && right == 0)
  {
    Slightright();
  }
  else if (leftMost == 0 && left == 0 && center == 0 && right == 0 && rightMost == 0)
  {
    currentCounter++;
    if (currentCounter != targetCounter)
    {
      moveForward();
      delay(100);
    }
  }
}

void lineFollowUntil(int untilCount)
{
  int counter = 0;

  while (counter < untilCount)
  {
    Serial.print(counter);
    Serial.println(" ");

    bool leftMost = digitalRead(lm); // left most
    bool left = digitalRead(l); // left
    bool center = digitalRead(cen); // center
    bool right = digitalRead(r); //right
    bool rightMost = digitalRead(rm); // right most

    lineFollow(counter, untilCount, leftMost, left, center, right, rightMost);

    if (counter >= untilCount)
    {
      stop();
      break;
    }
  }
}