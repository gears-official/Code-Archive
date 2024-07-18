// 10 +9 -8
#define LMPWM 11
#define LMP 13
#define LMN 12

// 11 +12 -13
#define RMPWM 10
#define RMP 9
#define RMN 8

#define LSPEED 200
#define RSPEED 200

//#define bLSPEED 90
//#define bRSPEED 90

void right() {
  analogWrite(LMPWM, LSPEED-80);
  analogWrite(RMPWM, RSPEED-80);
  digitalWrite(RMP, LOW);
  digitalWrite(RMN, HIGH);
  digitalWrite(LMP, HIGH);
  digitalWrite(LMN, LOW);
}
void left() {
  analogWrite(LMPWM,LSPEED-80);  
  analogWrite(RMPWM,RSPEED-80);  
  digitalWrite(RMP,HIGH);  
  digitalWrite(RMN,LOW);  
  digitalWrite(LMP,LOW);  
  digitalWrite(LMN,HIGH);
}
void backward() {
  analogWrite(LMPWM, LSPEED);
  analogWrite(RMPWM, RSPEED);
  digitalWrite(RMP, HIGH);
  digitalWrite(RMN, LOW);
  digitalWrite(LMP, HIGH);
  digitalWrite(LMN, LOW);
}
void straight() {
  analogWrite(LMPWM, LSPEED);
  analogWrite(RMPWM, RSPEED);
  digitalWrite(RMP, LOW);
  digitalWrite(RMN, HIGH);
  digitalWrite(LMP, LOW);
  digitalWrite(LMN, HIGH);
}
void halt() {
  analogWrite(LMPWM, 0);
  analogWrite(RMPWM, 0);
}
