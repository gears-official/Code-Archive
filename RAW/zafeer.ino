//right motor
int r_enR = 30;
int l_enR= 32;
int r_forward = 5;
int r_backword = 4;  

//left motor
int r_enL= 34;
int l_enL = 36;
int l_forward= 3;
int l_backword = 2;

//sensors code
int smrv=12;
int srv=11;
int scv=10;
int slv=9;
int smlv=8;

//speeds control
int speed=80;
int turn=80;
int slow=80;
int stop=0;

//sensor logic
int black=0;
int white=1;


   int smr=digitalRead(smrv);
   int sr=digitalRead(srv);
   int sc=digitalRead(scv);
   int sl=digitalRead(slv);
   int sml=digitalRead(smlv);



bool allSensorsOnBlack = false;
bool sensorsInBlack=false;


int count=0;


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


 digitalWrite(30,HIGH);
 digitalWrite(32,HIGH);
 digitalWrite(34,HIGH);
 digitalWrite(36,HIGH);

 pinMode(8,INPUT);
 pinMode(9,INPUT);
 pinMode(10,INPUT);
 pinMode(11,INPUT);
 pinMode(12,INPUT);




  //start fom all black
 while(1){
   updateSensor();
   if(smr==0 && sr==0 && sc==0 && sl==0 && sml==0){
    forward();
  }
  else{
    halt();
    delay(100);
    break;
  }
 }



while(1){
  updateSensor();
  if(smr==0 && sr==0 && sc==0 && sl==0 && sml==0)
  {
    halt();
    delay(100);
    break;
  }
  line();

}


forward();
delay(300);
halt();
delay(200);
right90();
delay(700);
halt();


//step 2 pass
while(1){
  updateSensor();
  //00011 0r 00111
  if(sml==0 && sl==0 && sc==0 && smr==1 && sr==1 )
  {
       break;
  }
  if(sml==0 && sl==0 && sc==1 && smr==1 && sr==1 )
  {
       break;
  }
  line();
}
forward();
delay(300);
halt();
delay(200);


while(1){
    updateSensor();
  if (sc==0){
    break;
  }
  left90();
}

//step 3 start 
while(1){
  updateSensor();
  //00011 0r 00111
  if(sml==0 && sl==0 && sc==0 && sr==1 && smr==1 )
  {
       break;
  }
  if(sml==0 && sl==0 && sc==1 && sr==1 && smr==1 )
  {
       break;
  }
  line();
}

forward();
delay(300);
halt();
delay(200);

while(1){
    updateSensor();
  if (sc==0){
    break;
  }
  left90();
}
// halt();
// delay(5000);



while(1){
  updateSensor();
  //11100 0r 11000
  if(sml==1 && sl==1 && sc==0 && smr==0 && sr==0 )
  {
       break;
  }
  if(sml==1 && sl==1 && sc==1 && smr==0 && sr==0 )
  {
       break;
  }
  line();
}

forwardarc();
delay(200);

while(1){
    updateSensor();
  if (sc==0){
    break;
  }
  right90();
}
halt();
delay(200);


//step 4 start 90dgree trun 
while(1){
  if(smr==0)
  {
    break;
  }
  line();

}
halt();
delay(200);
forward();
delay(200);

//step 5 
while(1){
    updateSensor();
  if (sc==0){
    halt();
    delay(200);
    break;
  }
  right90();
}

//11000. 11100 
while(1){
  if(sl==1 && smr==0){
    break;
  }
  
  line();

}
halt();
delay(200);
forward();
delay(200);


//step 5 
while(1){
    updateSensor();
  if (sc==0){
    halt();
    delay(200);
    break;
  }
  right90();
}



while(1){
  if(smr==0)
  {
    break;
  }
  line();

}
halt();
delay(200);
forward();
delay(200);


while(1){
    updateSensor();
  if (sc==0){
    halt();
    delay(200);
    break;
  }
  right90();
}
while(1){
  if(smr==0)
  {
    forward();
    delay(200);
    halt();
    delay(200);
    break;
  }
  line();
}



while(1){
    updateSensor();
  if (sc==0){
    forward();
    delay(200);
    halt();
    delay(200);
  
    break;
  }
  right90();

}

while(1){
    updateSensor();
  if (sc==0){
    forward();
    delay(200);
    halt();
    delay(200);
  
    break;
  }
  line();

}



while(1){
    updateSensor();
  if (sc==0){

    halt();
    delay(200);
  
    break;
  }
  left90();

}

while(1){
    updateSensor();
  if (sml==0){
    forward();
    delay(200);
    halt();
    delay(200);
  
    break;
  }
  line();

}



while(1){
    updateSensor();
  if (sc==0){
    
    halt();
    delay(200);
  
    break;
  }
  forward();
  delay(200);
  left90();

}

while(1){
  line();
}


























 







}


void loop(){
   
}






void line(){
updateSensor();

if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}
if(sml==1 && sl==1 && sc==1 && sr==1 && smr==1){

}







}



void updateSensor(){
  smr=digitalRead(smrv);
  sr=digitalRead(srv);
  sc=digitalRead(scv);
  sl=digitalRead(slv);
  sml=digitalRead(smlv);

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

