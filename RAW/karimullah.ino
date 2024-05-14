//right motor
int r_enR = 23;
int l_enR= 25;
int r_forward = 2;
int r_backword =3;  

//left motor
int r_enL= 24;
int l_enL = 22;
int l_forward= 5;
int l_backword = 4;


double ch1=53;

double ch4=51;




//speeds control
int speed=255;
int turn=150;
int slow=255;
int stop=0;



void setup(){

 Serial.begin(9600);
 
 pinMode(30,OUTPUT);
 pinMode(32,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(36,OUTPUT);
 pinMode(34,OUTPUT);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(ch1,INPUT);
 pinMode(ch4,INPUT);


 digitalWrite(30,HIGH);
 digitalWrite(32,HIGH);
 digitalWrite(34,HIGH);
 digitalWrite(36,HIGH);






}


void loop() {


  ch1 = pulseIn(53,HIGH);
  ch4 = pulseIn(51,HIGH);
Serial.begin(9600);
Serial.println("");
Serial.print(ch1);
Serial.print('\t');
Serial.print(ch4);

if((ch1!=0)&&(ch4!=0))
{     
//  if(ch1>1600 && ch4>1500)
//  {     
//    right(200, 100);  
//  }
//  else if(ch1>1600 && ch4<1300)
//  {     
//    left(100, 200);  
//  }
  if(ch1>1600)
  {     
    forward();
  }
  else if(ch1<1200)
  {     
    backword();
  }
  else if(ch4>1600)
  {
//    right90(turnSpeed);
    right90();  

  }
  else if(ch4<1300)
  {
//    left90(turnSpeed);
       left90();  
  }
  else
  {
    halt();
  }
}

 
}

void forward(){
 analogWrite(r_forward,speed);
 analogWrite(r_backword,stop);
 analogWrite(l_forward,speed);
 analogWrite(l_backword,stop);
}

void backword(){
 analogWrite(r_forward,stop);
 analogWrite(r_backword,speed);
 analogWrite(l_forward,stop);
 analogWrite(l_backword,speed);
}


void forwardarc(){
 analogWrite(r_forward,speed-50);
 analogWrite(r_backword,stop);
 analogWrite(l_forward,speed);
 analogWrite(l_backword,stop);
}


void halt(){
 analogWrite(r_forward,10);
 analogWrite(r_backword,10);
 analogWrite(l_forward,10);
 analogWrite(l_backword,10);
}

void left(){
 analogWrite(r_forward,turn);
 analogWrite(r_backword,stop);
 analogWrite(l_forward,stop);
 analogWrite(l_backword,stop);
}
void right(){
 analogWrite(r_forward,stop);
 analogWrite(r_backword,stop);
 analogWrite(l_forward,turn);
 analogWrite(l_backword,stop);
}

void left90(){
 analogWrite(r_forward,turn);
 analogWrite(r_backword,stop);
 analogWrite(l_forward,stop);
 analogWrite(l_backword,turn);
}
void right90(){
 analogWrite(r_forward,stop);
 analogWrite(r_backword,turn);
 analogWrite(l_forward,turn);
 analogWrite(l_backword,stop);
}

