#ifndef TEMPERATUR_SENSOR_H
#define TEMPERATUR_SENSOR_H

#include "Arduino.h"



#ifdef __cplusplus
#include "max6675.h"  // Include C++ class here
#endif

#ifdef __cplusplus
extern "C" {
#endif

// C functions can be declared here if necessary
float getTemperatur();

#ifdef __cplusplus
}
#endif

#endif