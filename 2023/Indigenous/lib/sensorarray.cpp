#include "../include/sensorarray.h"

SensorArray::SensorArray(int sensorPins[], int size)
{
    this->sensors = new Sensor[size];
    for (int i = 0; i < size; i++)
    {
        this->sensors[i] = Sensor(DIGITAL, sensorPins[i]);
    }
}

void SensorArray::print()
{
    int s1 = this->sensors[0].getValue();
    int s2 = this->sensors[1].getValue();
    int s3 = this->sensors[2].getValue();
    int s4 = this->sensors[3].getValue();
    int s5 = this->sensors[4].getValue();

    Serial.print(s1);
    Serial.print(" ");
    Serial.print(s2);
    Serial.print(" ");
    Serial.print(s3);
    Serial.print(" ");
    Serial.print(s4);
    Serial.print(" ");
    Serial.println(s5);
    // Serial.print(" ");
    // Serial.println(this->getPosition());
    delay(100);
}

int SensorArray::getPosition()
{
    int s1 = this->sensors[0].getValue();
    int s2 = this->sensors[1].getValue();
    int s3 = this->sensors[2].getValue();
    int s4 = this->sensors[3].getValue();
    int s5 = this->sensors[4].getValue();

    /***************************
     *          LEFT
     ****************************/
    // 00011
    if (s1 == BLACK && s2 == BLACK && s3 == BLACK && s4 == WHITE && s5 == WHITE)
    {
        // 90 degree left
        return 55;
    }
    // 01111
    if (s1 == BLACK && s2 == WHITE && s3 == WHITE && s4 == WHITE && s5 == WHITE)
    {
        // Far left
        return 50;
    }
    // 10111
    else if (s1 == WHITE && s2 == BLACK && s3 == WHITE && s4 == WHITE && s5 == WHITE)
    {
        // Slightly left
        return 40;
    }
    // 00111
    else if (s1 == BLACK && s2 == BLACK && s3 == WHITE && s4 == WHITE && s5 == WHITE)
    {
        // Slightly left
        return 40;
    }
    /***************************
     *          MIDDLE
     ****************************/
    // 10011
    else if (s1 == WHITE && s2 == BLACK && s3 == BLACK && s4 == WHITE && s5 == WHITE)
    {
        // Middle position
        return 35;
    }
    // 11011
    else if (s1 == WHITE && s2 == WHITE && s3 == BLACK && s4 == WHITE && s5 == WHITE)
    {
        // Middle position
        return 30;
    }
    // 10001
    else if (s1 == WHITE && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == WHITE)
    {
        // Middle position
        return 30;
    }
    // 10000
    else if (s1 == WHITE && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == BLACK)
    {
        // Middle position
        return 30;
    }
    // 00001
    else if (s1 == BLACK && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == WHITE)
    {
        // Middle position
        return 30;
    }
    // 00000
    else if (s1 == BLACK && s2 == BLACK && s3 == BLACK && s4 == BLACK && s5 == BLACK)
    {
        // Middle position
        return 30;
    }
    // 11001
    else if (s1 == WHITE && s2 == WHITE && s3 == BLACK && s4 == BLACK && s5 == WHITE)
    {
        // Middle position
        return 25;
    }
    /***************************
     *          RIGHT
     ****************************/
    // 11101
    else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == BLACK && s5 == WHITE)
    {
        // Slightly right
        return 20;
    }
    // 11100
    else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == BLACK && s5 == BLACK)
    {
        // Slightly right
        return 20;
    }
    // 11110
    else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == WHITE && s5 == BLACK)
    {
        // Far right
        return 10;
    }
    // 11000
    else if (s1 == WHITE && s2 == WHITE && s3 == BLACK && s4 == BLACK && s5 == BLACK)
    {
        // 90 degree right
        return 5;
    }
    // Unknown position or multiple sensors active
    return 0;
}