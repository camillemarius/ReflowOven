#ifndef CUSTOM_UI_H
#define CUSTOM_UI_H

#ifdef __cplusplus
extern "C" {
#endif
#include "Arduino.h"
#include "profile_management.h"

void drawChart(ReflowProfile reflowProfile);
void drawTemperaturePoint(int temp);

#ifdef __cplusplus
}
#endif

#endif