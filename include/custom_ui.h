#ifndef CUSTOM_UI_H
#define CUSTOM_UI_H

#ifdef __cplusplus
extern "C" {
#endif
#include "Arduino.h"
#include "profile_management.h"

typedef enum {
    IDLE,
    PREHEAT,
    SOAK,
    RAMPPEAK,
    REFLOW,
    COOLDOWN
} ReflowPhases;

void initChart(void);
void addTemperatureProfileToChart(ReflowProfile reflowProfile);
void addTemperaturePointToChart(int temp);
void deleteTemperatureSeries(void);
void setIconStateBasedOnReflowPhase(ReflowPhases phase);
void setStartButtonBakgroundColor(bool start);

#ifdef __cplusplus
}
#endif

#endif