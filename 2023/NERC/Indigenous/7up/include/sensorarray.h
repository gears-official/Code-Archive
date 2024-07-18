// include guard
#ifndef SENSORARRAY_H
#define SENSORARRAY_H

#include <Arduino.h>
#include "sensor.h"

class SensorArray
{
private:
    int size;

public:
    Sensor *sensors;
    SensorArray(int sensorPins[], int size);

    /**
     * @brief get position of the sensor array (only work with 5 sensors)
     */
    int getPosition();

    /**
     * @brief print sensor values and position on serial
     *  
    */
    void print();
};

#include "../lib/sensorarray.cpp"
#endif