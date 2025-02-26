#include "reflowOvenControl.h"
#include "PID_SSR.h"

static ReflowProfile  activeProfile;
static ReflowPhases   activReflowPhase = IDLE;

bool startReflowProcess = false;  // Definition

void setActiveReflowOvenProfile(ReflowProfile profile) {
  activeProfile = profile;
}

void determineReflowOvenPhase(int temp) {
  
  static unsigned long phaseStartTime = 0;

  switch (activReflowPhase)
  {
  case IDLE:
    /* code */
    activReflowPhase = PREHEAT;
    break;

  case PREHEAT:
    /* code */
    pid_setRefTemperature(activeProfile.soak_temp);
    if(temp >= activeProfile.soak_temp) {
      phaseStartTime = millis();  // Start the timer for the SOAK phase
      activReflowPhase = SOAK;
    }
    break;

  case SOAK:
    /* code */
    pid_setRefTemperature(activeProfile.soak_temp);
    if (millis() - phaseStartTime >= (activeProfile.soak_duration*1000)) {
      phaseStartTime = 0;
      activReflowPhase = RAMPPEAK;
    }
    break;

  case RAMPPEAK:
    /* code */
    pid_setRefTemperature(activeProfile.reflow_temp);
    if(temp >= activeProfile.reflow_temp) {
      phaseStartTime = millis();  // Start the timer for the SOAK phase
      activReflowPhase = REFLOW;
    }
    break;

  case REFLOW:
    /* code */
    pid_setRefTemperature(activeProfile.reflow_temp);
    if (millis() - phaseStartTime >= (activeProfile.reflow_duration*1000)) {
      phaseStartTime = 0;
      activReflowPhase = COOLDOWN;
    }
    break;

  case COOLDOWN:
    /* code */
    pid_setRefTemperature(activeProfile.cooldown_temp);
    if(temp <= activeProfile.cooldown_temp) {
      //startReflowProcess = false;
      activReflowPhase = IDLE;
    }
    break;
  
  default:
    break;
  }
}

void processReflowState(int temp, bool start) {
  static bool wasReflowActive = true;  // Tracks if reflow process was active before

  if (start) {
      determineReflowOvenPhase(temp);
      pid_updateControl(temp);

      setIconStateBasedOnReflowPhase(activReflowPhase);
      addTemperaturePointToChart(temp);
      wasReflowActive = true;
  } 
  else if (wasReflowActive) {  
      // Only call deleteTemperatureSeries() once when transitioning from true → false
      activReflowPhase = IDLE;
      pid_setRefTemperature(0);
      pid_updateControl(temp);
      setIconStateBasedOnReflowPhase(activReflowPhase);
      setStartButtonBakgroundColor(start);
      deleteTemperatureSeries();
      wasReflowActive = false;
  }
}

  
void reflowControl(void) {
  // Read Temperature
  float temp = getTemperatur();

  // Print Temperture periodically
  char temp_str[10];  
  snprintf(temp_str, sizeof(temp_str), "%.1f°C", temp);
  lv_label_set_text(ui_LaActualTemperature, temp_str);

  // Actuall Reflow Oven Processing
  processReflowState(temp, startReflowProcess);
}

void reflowControlInit(void) {
  pid_setup();
}
