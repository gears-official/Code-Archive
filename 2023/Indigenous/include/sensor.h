#ifndef SENSOR_H
#define SENSOR_H

#define BLACK 0
#define WHITE 1

#define ANALOG 1
#define DIGITAL 2

class Sensor
{
  private:
      int pin;
      int mode;
  public:
      // Constructor      
      Sensor();
      Sensor(int mode, int pin);

      /////////////////////////
      //       getValue()
      /////////////////////////
      /**
       * Returns the value of the sensor
       * 
       * @return int
      */
      int getValue();

      /////////////////////////
      //       setPin()
      /////////////////////////
      /**
       * Sets the pin of the sensor
       * 
       * @return None
      */
      void setPin(int pin);

      /////////////////////////
      //        setMode()
      /////////////////////////
      /**
       * Sets the mode of the sensor
       * 
       * @return None
      */
      void setMode(int mode);

      /////////////////////////
      //        getPin()
      /////////////////////////
      /**
       * get the pin of the sensor
       * 
       * @return pin
      */
      int getPin();
      /////////////////////////
      //      getMode()
      /////////////////////////
      /**
       * set the mode of the sensor
       * 
       * @return mode
      */
      int getMode();
};

#include "../lib/sensor.cpp"

#endif