#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include <math.h>



// Simple sensor fusion AHRS using an accelerometer and magnetometer.
class Conversion 
{
public:
  
  
  bool getOrientation(sensors_vec_t* orientation);

private:
  Adafruit_Sensor* _accel;
  Adafruit_Sensor* _mag;

};

#endif
