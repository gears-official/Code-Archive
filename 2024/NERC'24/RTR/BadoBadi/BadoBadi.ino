int Right_R_Pwm = 6;
int Right_L_Pwm = 5;

int Left_R_Pwm = 9;
int Left_L_Pwm = 10;

int rightEncode = 2;
int leftEncode = 3;

int leftEncoderTicks = 0;
int rightEncoderTicks = 0;

int leftSpeed = 230;
int rightSpeed = 245;

int L_turnSpeed = 120;
int R_turnSpeed = 135;

void setup()
{
    // put your setup code here, to run once:
    pinMode(Left_L_Pwm, OUTPUT);
    pinMode(Left_R_Pwm, OUTPUT);

    pinMode(Right_L_Pwm, OUTPUT);
    pinMode(Right_R_Pwm, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(leftEncode), LencodeFunc, RISING);
    attachInterrupt(digitalPinToInterrupt(rightEncode), RencodeFunc, RISING);
    Serial.begin(9600);

    // forwardEncoder(1440, leftSpeed, rightSpeed);
    redArena();
    // blueArena();
}

void redArena()
{
    forwardEncoder(1500, leftSpeed, rightSpeed);
    delay(70);
    rightEncoder(200);
    delay(70);  

    forwardEncoder(1920, leftSpeed, rightSpeed);
    delay(80);
    rightEncoder(275);
    delay(70);
    
    forwardEncoder(1950, leftSpeed, rightSpeed);
    delay(70);
    leftEncoder(260);
    delay(70);
    
    forwardEncoder(720, leftSpeed, rightSpeed);
    delay(70);
    leftEncoder(290);
    delay(80);

    forwardEncoder(1800, leftSpeed, rightSpeed);
    delay(70);
    leftEncoder(250);
    delay(70);

    forwardEncoder(300, leftSpeed, rightSpeed);
    delay(70);
    rightEncoder(220);
    delay(70);
    forwardEncoder(600, leftSpeed, rightSpeed);
}

void blueArena()
{
    forwardEncoder(1470, leftSpeed, rightSpeed);
    delay(70);
    leftEncoder(220);
    delay(70);  

    forwardEncoder(1900, leftSpeed, rightSpeed);
    delay(80);
    leftEncoder(295);
    delay(70);
    
    forwardEncoder(1850, leftSpeed, rightSpeed);
    delay(70);
    rightEncoder(200);
    delay(70);
    
    forwardEncoder(750, leftSpeed, rightSpeed);
    delay(70);
    rightEncoder(320);
    delay(80);

    forwardEncoder(1800, leftSpeed, rightSpeed);
    delay(70);
    rightEncoder(235);
    delay(70);

    forwardEncoder(280, leftSpeed, rightSpeed);
    delay(70);
    leftEncoder(235);
    delay(70);
    forwardEncoder(500, leftSpeed, rightSpeed);
  
}


void forwardEncoder(int value, int lSpeed, int rSpeed)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        forward(lSpeed, rSpeed);
    }
    halt();
}

void rightEncoder(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        right90();
    }
    halt();
}

void leftEncoder(int value)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        left90();
    }
    halt();
}

void LencodeFunc()
{
    leftEncoderTicks++;
}

void RencodeFunc()
{
    rightEncoderTicks++;
}

void forward(int lSpeed, int rSpeed)
{
      analogWrite(Left_R_Pwm, lSpeed);
      analogWrite(Left_L_Pwm, 0);
      analogWrite(Right_R_Pwm, rSpeed);
      analogWrite(Right_L_Pwm, 0);
}

void backward()
{
    analogWrite(Left_L_Pwm, leftSpeed);
    analogWrite(Left_R_Pwm, 0);
    analogWrite(Right_R_Pwm, 0);
    analogWrite(Right_L_Pwm, rightSpeed);
}

void right90()
{
      analogWrite(Left_R_Pwm, L_turnSpeed);
      analogWrite(Right_R_Pwm, 0);
      analogWrite(Left_L_Pwm, 0);
      analogWrite(Right_L_Pwm, R_turnSpeed);
}

void left90()
{
      analogWrite(Left_R_Pwm, 0);
      analogWrite(Right_R_Pwm, R_turnSpeed);
      analogWrite(Left_L_Pwm, L_turnSpeed);
      analogWrite(Right_L_Pwm, 0);
}
void halt()
{
    analogWrite(Left_R_Pwm, 0);
    analogWrite(Right_R_Pwm, 0);
    
    analogWrite(Left_L_Pwm, 0);
    analogWrite(Right_L_Pwm,0);
   
}
void loop()
{
    // Serial.print(leftEncoderTicks);
    // Serial.print(" ");
    // Serial.println(rightEncoderTicks);
    // Serial.println("");
}