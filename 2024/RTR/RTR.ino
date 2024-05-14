RTR
Syntax error
Usama Tauqir,kinza, Mariam
2024
===================
int motor1_pin1 = 9;
int motor1_pin2 = 8;
int motor1_pwm = 7;
int motor2_pin1 = 11;
int motor2_pin2 = 10;
int motor2_pwm = 12;
int speed = 57;

  int ml = "mostLeft";
  int l = "left";
  int c = "center";
  int r = "right";
  int mr = "mostRight";
  int mostLeft = 6;


int left = 5;
int center = 4;
int right = 3;
int mostRight = 2;
int black = 0;
int white = 1;

int flage = 0;



void setup() {
  Serial.begin(9600);
  pinMode(motor1_pin1, OUTPUT);
  pinMode(motor1_pin2, OUTPUT);
  pinMode(motor1_pwm, OUTPUT);
  pinMode(motor2_pin1, OUTPUT);
  pinMode(motor2_pin2, OUTPUT);
  pinMode(motor2_pwm, OUTPUT);

  pinMode(2, INPUT);  //defines pin mode (output/input)
  pinMode(3, INPUT);  //defines pin mode (output/input)
  pinMode(4, INPUT);  //defines pin mode (output/input)
  pinMode(5, INPUT);  //defines pin mode (output/input)
  pinMode(6, INPUT);  //defines pin mode (output/input)


  while(1)
  {
    sensorArray();
    
  }
  



}


void loop() {



}

void sensorArray()
{
  
    int ml = digitalRead(mostLeft);
    int l = digitalRead(left);
    int c = digitalRead(center);
    int r = digitalRead(right);
    int mr = digitalRead(mostRight);

    Serial.println("");
    Serial.print(ml);
    Serial.print(l);
    Serial.print(c);
    Serial.print(r);
    Serial.print(mr);


    if( l==white && c==black && r==white  ) {  //move forward
     forward();
   }
    else if ( l==white && c==black && r==black  ) {  //move forward
     right90();
   }
    else if ( l==black && c==black && r==white  ) {  //move forward
     left90();
   }
    else if ( l==white && c==white && r==black  ) {  //move forward
     right90();
   }
    else if ( l==black && c==white && r==white  ) {  //move forward
     left90();
   }
   else if ( ml==black && c==white && mr==white  ) {  //move forward
     left90();
   }
   else if ( ml==white && c==white && mr==black  ) {  //move forward
     right90();
   }
   else if ( ml==black && l==black && c==white  ) {  //move forward
     left90();
   }
   else if ( mr==black && r==black && c==white  ) {  //move forward
     right90();
   }
  
  //  else if ( ml==white && l==white && c==black ) {  //move forward
  //    left90();
  //  }
  //  else if ( mr==white && r==white && c==black) {  //move forward
  //    right90();
  //  }
   

}
void forward() {

  digitalWrite(motor1_pin1, LOW);
  digitalWrite(motor1_pin2, HIGH);
  analogWrite(motor1_pwm, speed);
  digitalWrite(motor2_pin1, LOW);
  digitalWrite(motor2_pin2, HIGH);
  analogWrite(motor2_pwm, speed);
}
void stop() {
  digitalWrite(motor1_pin1, LOW);
  digitalWrite(motor1_pin2, LOW);
  analogWrite(motor1_pwm, speed);
  digitalWrite(motor2_pin1, LOW);
  digitalWrite(motor2_pin2, LOW);
  analogWrite(motor2_pwm, speed);
}
void backward() {
  digitalWrite(motor1_pin1, HIGH);
  digitalWrite(motor1_pin2, LOW);
  analogWrite(motor1_pwm, speed);
  digitalWrite(motor2_pin1, HIGH);
  digitalWrite(motor2_pin2, LOW);
  analogWrite(motor2_pwm, speed);
}

void right90() {
  digitalWrite(motor1_pin1, LOW);
  digitalWrite(motor1_pin2, HIGH);
  analogWrite(motor1_pwm, 45);
  digitalWrite(motor2_pin1, HIGH);
  digitalWrite(motor2_pin2, LOW);
  analogWrite(motor2_pwm, 45);
}

void left90() {
  digitalWrite(motor1_pin1, HIGH);
  digitalWrite(motor1_pin2, LOW);
  analogWrite(motor1_pwm, 45);
  digitalWrite(motor2_pin1, LOW);
  digitalWrite(motor2_pin2, HIGH);
  analogWrite(motor2_pwm, 45);
}