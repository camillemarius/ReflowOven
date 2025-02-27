#ifndef REFLOW_OVEN_CONTROL_H
#define REFLOW_OVEN_CONTROL_H


#include "Arduino.h"
#include "lvgl_custom_ui.h"
#include "ui/ui.h"
#include "memory_profile_management.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sensor_temperature.h"


extern bool startReflowProcess;

// C functions can be declared here if necessary
void setActiveReflowOvenProfile(ReflowProfile profile);
void reflowControlTask(void);
void reflowControlInit(void);

#ifdef __cplusplus
}
#endif


#endif