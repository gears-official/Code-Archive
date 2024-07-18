#ifndef COLORSENSOR_H
#define COLORSENSOR_H

class ColorSensor
{
  private:
    int S0;
    int S1;
    int S2;
    int S3;
    int sensorOut;

    int getRedValue();
    int getGreenValue();
    int getBlueValue();

  public:
    ColorSensor(int S0, int S1, int S2, int S3, int sensorOut);
    String predict();  
    void printRGB();
};

#include "../lib/colorsensor.cpp"

#endif