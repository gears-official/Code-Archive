#define leftEncoder 2
#define rightEncoder 3

int leftMotorForward = 6;
int leftMotorBackward = 5;

int rightMotorForward = 9;
int rightMotorBackward = 10;

int Speed = 220;
int TurnSpeed = 100;

int lmsensor = 4;
int lsensor = 7;
int msensor = 8;
int rsensor = 11;
int rmsensor = 12;

int lms;
int ls;
int ms;
int rs;
int rms;


bool is_line = false;
bool isDone = false;

unsigned long prevMillis = 0;
const long interval = 200;

int turnCount = 0;
int counter = 0;

int rightEncoderTick = 0;
int leftEncoderTick = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(lmsensor, INPUT);
  pinMode(lsensor, INPUT);
  pinMode(msensor, INPUT);
  pinMode(rsensor, INPUT);
  pinMode(rmsensor, INPUT);

  Serial.begin(9600);
  Serial.println("Started");

  attachInterrupt(digitalPinToInterrupt(leftEncoder), leftEncoderFunc, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoder), rightEncoderFunc, RISING);

  // linefollowuntil(4);
  // // encoderBackward(20);
  // encoderLeft90(250);

  // linefollowuntil(3);
  // encoderLeft90(200);

  // linefollowuntil(4);
  // encoderRight90(180);

  // linefollowuntil(4);
  // encoderRight90(180);


  // linefollowuntil(4);


  // encoderRight90(60);
  // encoderForward(820);



  // stop();

  // linefollowuntil(4);
  // encoderLeft90(210);

  // linefollowuntil(3);
  // encoderLeft90(200);

  // linefollowuntil(4);
  // encoderRight90(190);

  // linefollowuntil(4);
  // encoderRight90(200);

  // linefollowuntil(4);
  // encoderRight90(200);

  // linefollowuntil(1);
  // encoderLeft90(200);

  // linefollowuntil(2);
    
   linefollowuntil(4);
   delay(100);
   encoderRight90(170);

   linefollowuntil(3);
   delay(100);
   encoderRight90(180);

   linefollowuntil(4);
   delay(100);
   encoderLeft90(180);

   linefollowuntil(4);
   delay(100);
   encoderLeft90(180);

   linefollowuntil(4);
   delay(100);
   encoderLeft90(180);

   linefollowuntil(1);
   delay(100);
   encoderRight90(180);

   linefollowuntil(2);


}

void loop() {
}

void linefollow() {
  lms = digitalRead(lmsensor);
  ls = digitalRead(lsensor);
  ms = digitalRead(msensor);
  rs = digitalRead(rsensor);
  rms = digitalRead(rmsensor);


  if (ls == 1 && ms == 0 && rs == 1) {
    forward();
  } else if (ls == 0 && ms == 0 && rs == 1) {
    left();
  } else if (ls == 0 && ms == 1 && rs == 1) {
    left();
  } else if (ls == 1 && ms == 0 && rs == 0) {
    right();
  } else if (ls == 1 && ms == 1 && rs == 0) {
    right();
  }

  // // 00111
  else if(!lms && !ls && ms && rs && rms)
  {
    left();
  }
  // 01111
  else if(!lms && ls && ms && rs && rms)
  {
    left();
  }
  // 10111
  else if(lms && !ls && ms && rs && rms)
  {
    left();
  }
  // 11100
  else if(lms && ls && ms && !rs && !rms)
  {
    right();
  }
  // 11110
  else if(lms && ls && ms && rs && !rms)
  {
    right();
  }
  // 11101
  else if(lms && ls && ms && !rs && rms)
  {
    right();
  }
}

void linefollowuntil(int count) {
  int strips_count = 0;
  while (true) {
    lms = digitalRead(lmsensor);
    ls = digitalRead(lsensor);
    ms = digitalRead(msensor);
    rs = digitalRead(rsensor);
    rms = digitalRead(rmsensor);

    if (!lms && !ls && !ms && !rs && !rms && !is_line) {
      strips_count++;
      is_line = true;
      prevMillis = millis();
    } else if (millis() - prevMillis > interval && is_line) {
      is_line = false;
    }

    if (strips_count < count) {
      linefollow();
      Serial.println(strips_count);
    } else {
      encoderBackward(45);
      stop();
      return;
    }
  }
}

void forward() {
  analogWrite(rightMotorForward, Speed);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, Speed);
  analogWrite(leftMotorBackward, 0);
}

void stop() {
  analogWrite(rightMotorForward, 0);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, 0);
  analogWrite(leftMotorBackward, 0);
}

void backward() {
  analogWrite(rightMotorForward, 0);
  analogWrite(rightMotorBackward, Speed);
  analogWrite(leftMotorForward, 0);
  analogWrite(leftMotorBackward, Speed);
}

void left() {
  analogWrite(rightMotorForward, Speed);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, TurnSpeed);
  analogWrite(leftMotorBackward, 0);
}

void left90() {
  analogWrite(rightMotorForward, Speed);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, 0);
  analogWrite(leftMotorBackward, Speed);
}

void right() {
  analogWrite(rightMotorForward, TurnSpeed);
  analogWrite(rightMotorBackward, 0);
  analogWrite(leftMotorForward, Speed);
  analogWrite(leftMotorBackward, 0);
}

void right90() {
  analogWrite(rightMotorForward, 0);
  analogWrite(rightMotorBackward, Speed);
  analogWrite(leftMotorForward, Speed);
  analogWrite(leftMotorBackward, 0);
}

void leftEncoderFunc() {
  leftEncoderTick++;
}

void rightEncoderFunc() {
  rightEncoderTick++;
}

void encoderForward(int value) {
  rightEncoderTick = 0;
  leftEncoderTick = 0;

  while (leftEncoderTick < value || rightEncoderTick < value) {

    Serial.print(leftEncoderTick);
    Serial.print("   ");
    Serial.println(rightEncoderTick);
    forward();
  }
  stop();
}

void encoderBackward(int value) {
  rightEncoderTick = 0;
  leftEncoderTick = 0;

  while (leftEncoderTick < value || rightEncoderTick < value) {

    Serial.print(leftEncoderTick);
    Serial.print("   ");
    Serial.println(rightEncoderTick);
    backward();
  }
  stop();
}

void encoderRight90(int value) {
  rightEncoderTick = 0;
  leftEncoderTick = 0;

  while (leftEncoderTick < value || rightEncoderTick < value) {

    Serial.print(leftEncoderTick);
    Serial.print("   ");
    Serial.println(rightEncoderTick);
    right90();
  }
  stop();
}

void encoderLeft90(int value) {
  rightEncoderTick = 0;
  leftEncoderTick = 0;

  while (leftEncoderTick < value || rightEncoderTick < value) {

    Serial.print(leftEncoderTick);
    Serial.print("   ");
    Serial.println(rightEncoderTick);
    left90();
  }
  stop();
}