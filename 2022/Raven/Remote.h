//#define CH1 6
#define CH2 5
#define CH4 3


void startRemote() {
  pinMode(CH4, INPUT);
  pinMode(CH2, INPUT);
}
int getChannel(int channel) {  
  return pulseIn(channel, HIGH);
}
