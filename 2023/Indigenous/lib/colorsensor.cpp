#include <Arduino.h>
#include "../include/colorsensor.h"

ColorSensor::ColorSensor(int S0, int S1, int S2, int S3, int sensorOut)
{
  this->S0 = S0;
  this->S1 = S1;
  this->S2 = S2;
  this->S3 = S3;

  this->sensorOut = sensorOut;
 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}
String ColorSensor::predict()
{
    int red = getRedValue();
    int green = getGreenValue();
    int blue = getBlueValue();

    if (red > 150 && green > 150 && blue > 150)
    {
      return "\0";
    }
    else if (red < green && red < blue && green < 150 && blue < 150)
    {
       return "Orange";
    }
    else if (green < red && green < blue  && red < 150 && blue < 150){
      return "green";
    }
    else if (blue < red && blue < green  && green < 150 && red < 150)
    {
      return "blue";
    }
    else {
        return "\0";
    }
}

int ColorSensor::getRedValue()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  int value = pulseIn(sensorOut, LOW);

  return value;
}
int ColorSensor::getGreenValue()
{
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  int value = pulseIn(sensorOut, LOW);

  return value;
}
int ColorSensor::getBlueValue()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  int value = pulseIn(sensorOut, LOW);

  return value;
}
void ColorSensor::printRGB()
{
  int red = getRedValue();
  int green = getGreenValue();
  int blue = getBlueValue();

  Serial.print("R: ");
  Serial.print(red);
  Serial.print(" G: ");
  Serial.print(green);
  Serial.print(" B: ");
  Serial.println(blue);
}