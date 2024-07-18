int Right_R_Pwm = 11;
int Right_L_Pwm = 10;

int Left_R_Pwm = 9;
int Left_L_Pwm = 8;

int rightEncode = 2;
int leftEncode = 3;

int leftEncoderTicks = 0;
int rightEncoderTicks = 0;

int leftSpeed = 120;
int rightSpeed = 110;

int R_turnSpeed = 150;
int L_turnSpeed = 150;

int mostLeft = 30;
int left = 29;
int center = 28;
int right = 27;
int mostRight = 26;

  int ml ;
  int l ;
  int c ;
  int r ;
  int mr ;
 

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

  pinMode(mostLeft,INPUT);
  pinMode(left,INPUT);
  pinMode(center,INPUT);
  pinMode(right,INPUT);
  pinMode(mostRight,INPUT);

  // forwardEncoder(1100,120, 110);

    // redArena();
    blueArena();
    // blueArena(); 
    // forwardEncoder(1000);
    // delay(2000);
    // rightEncoder(350);
}

void blueArena()
{
    // delay(300);
    // forwardEncoder(300,120, 110);
    forwardEncoder(1800,leftSpeed, rightSpeed);
    delay(300);
    leftEncoder(285);
    delay(300);  
    forwardEncoder(1800,leftSpeed, rightSpeed);

    delay(300);
    leftEncoder(413);
    delay(300);

    forwardEncoder(1790,leftSpeed, rightSpeed);
    
    delay(300);
    rightEncoder(230);
    delay(300);
    
    forwardEncoder(800,leftSpeed, rightSpeed);
    delay(310);
    rightEncoder(340);
    delay(300);

    forwardEncoder(1550,leftSpeed, rightSpeed);
    delay(300);
    rightEncoder(100);
    delay(300);

    forwardEncoder(880,leftSpeed, rightSpeed);

    // ---------------
    // delay(2000);
    // leftEncoder(220);
    // // delay(2000);

    // forwardEncoder(200,leftSpeed, rightSpeed);
}

void redArena()
{

    // delay(500);
    delay(1000);
    // forwardEncoder(300,120, 110);
    forwardEncoder(1930,leftSpeed, rightSpeed);
    delay(300);
    rightEncoder(280);
    delay(300);  
    forwardEncoder(1900,leftSpeed, rightSpeed);

    delay(300);
    rightEncoder(425);
    delay(300);

    forwardEncoder(1850,leftSpeed, rightSpeed);
    
    delay(300);
    leftEncoder(280);
    delay(300);
    
    forwardEncoder(600,leftSpeed, rightSpeed);
    delay(300);
    leftEncoder(300);
    delay(300);

    forwardEncoder(1400,leftSpeed, rightSpeed);
    delay(300);
    leftEncoder(130);
    delay(300);

    forwardEncoder(900,leftSpeed, rightSpeed);



    // -------------------------------------------
    // rightEncoder(80);
    // delay(300);

    // forwardEncoder(800);
    // delay(2000); //from here the robot is in the finish line 
    // leftEncoder(220);
    // delay(2000)

    // forwardEncoder(600);
}


void forwardEncoder(int value, int l, int r)
{
    leftEncoderTicks = 0;
    rightEncoderTicks = 0;
    while (leftEncoderTicks < value || rightEncoderTicks < value)
    {
        Serial.print(leftEncoderTicks);
        Serial.print(" ");
        Serial.println(rightEncoderTicks);
        forward(l, r);
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

void forward(int l, int r)
{
      analogWrite(Left_R_Pwm, l);
      analogWrite(Left_L_Pwm, 0);
      analogWrite(Right_R_Pwm, r);
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
    analogWrite(Left_R_Pwm, 255);
    analogWrite(Right_R_Pwm, 255);
    
    analogWrite(Left_L_Pwm, 255);
    analogWrite(Right_L_Pwm,255);
   
}
void loop()
{
    // Serial.print(leftEncoderTicks);
    // Serial.print(" ");
    // Serial.println(rightEncoderTicks);
    // Serial.println("");
}


// void lineFollow()
// {
//   ml=digitalRead(mostLeft);
//   l=digitalRead(left);
//   c=digitalRead(center);
//   r=digitalRead(right);
//   mr=digitalRead(mostRight);


//   if (l==1 && c==0 && r==1)
//   {
//     forwardEncoder(1200,130,130);
//   }
//     if (l==0 && c==1 && r==1)
//   {
//     leftEncoder(230);    
//   }
//     if (l==1 && c==1 && r==0)
//   {
//     rightEncoder(230);    
//   }
//       if (l==0 && c==0 && r==1)
//   {
//     leftEncoder(230);    
//   }
//     if (l==1 && c==0 && r==0)
//   {
//     rightEncoder(230);    
//   }
//   if (l==0 && c==0 && r==0)
//   {
//     forwardEncoder(230);   
//   }
// }
