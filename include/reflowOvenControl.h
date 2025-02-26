#ifndef REFLOW_OVEN_CONTROL_H
#define REFLOW_OVEN_CONTROL_H


#include "Arduino.h"
#include "custom_ui.h"
#include "ui/ui.h"
#include "profile_management.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "temperatur_sensor.h"


extern bool startReflowProcess;

// C functions can be declared here if necessary
void determineReflowOvenPhase(int temp);
void setActiveReflowOvenProfile(ReflowProfile profile);
void processReflowState(int temp, bool start);
void reflowControl(void);
void reflowControlInit(void);

#ifdef __cplusplus
}
#endif


#endif