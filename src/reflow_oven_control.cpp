/**
 * @file  reflowOvenControl.cpp
 * @brief Manages the reflow oven control process by determining the current phase
 *        based on the temperature and updating the system state accordingly.
 * 
 * This code includes functions to initialize the reflow control system, set the active
 * reflow oven profile, and process the reflow state. It transitions through different
 * phases of the reflow process (IDLE, PREHEAT, SOAK, RAMPPEAK, REFLOW, COOLDOWN)
 * based on temperature readings and time durations specified in the active profile.
 * The system updates the PID controller's reference temperature and manages UI elements
 * to reflect the current state of the reflow process.
 */


/* Includes ------------------------------------------------------------------*/
#include "reflow_oven_control.h"
#include "pid_ssr.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
static ReflowProfile  activeProfile;
static ReflowPhases   activReflowPhase = IDLE;

bool startReflowProcess = false;  // Definition

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
static void determineReflowOvenPhase(int temp) {
  
  static unsigned long phaseStartTime = 0;

  switch (activReflowPhase)
  {
  case IDLE:
    /* code */
    activReflowPhase = PREHEAT;
    break;

  case PREHEAT:
    /* code */
    pid_setReferenceTemperature(activeProfile.soak_temp);
    if(temp >= activeProfile.soak_temp) {
      phaseStartTime = millis();  // Start the timer for the SOAK phase
      activReflowPhase = SOAK;
    }
    break;

  case SOAK:
    /* code */
    pid_setReferenceTemperature(activeProfile.soak_temp);
    if (millis() - phaseStartTime >= (activeProfile.soak_duration*1000)) {
      phaseStartTime = 0;
      activReflowPhase = RAMPPEAK;
    }
    break;

  case RAMPPEAK:
    /* code */
    pid_setReferenceTemperature(activeProfile.reflow_temp);
    if(temp >= activeProfile.reflow_temp) {
      phaseStartTime = millis();  // Start the timer for the SOAK phase
      activReflowPhase = REFLOW;
    }
    break;

  case REFLOW:
    /* code */
    pid_setReferenceTemperature(activeProfile.reflow_temp);
    if (millis() - phaseStartTime >= (activeProfile.reflow_duration*1000)) {
      phaseStartTime = 0;
      activReflowPhase = COOLDOWN;
    }
    break;

  case COOLDOWN:
    /* code */
    pid_setReferenceTemperature(activeProfile.cooldown_temp);
    if(temp <= activeProfile.cooldown_temp) {
      //startReflowProcess = false;
      activReflowPhase = IDLE;
    }
    break;
  
  default:
    break;
  }
}

static void processReflowState(int temp, bool start) {
  static bool wasReflowActive = true;  // Tracks if reflow process was active before

  if (start) {
      determineReflowOvenPhase(temp);
      pid_updateTemperature(temp);

      setIconStateBasedOnReflowPhase(activReflowPhase);
      addTemperaturePointToChart(temp);
      wasReflowActive = true;
  } 
  else if (wasReflowActive) {  
      // Only call deleteTemperatureSeries() once when transitioning from true → false
      activReflowPhase = IDLE;
      pid_setReferenceTemperature(0);
      pid_updateTemperature(temp);
      setIconStateBasedOnReflowPhase(activReflowPhase);
      setStartButtonBakgroundColor(start);
      deleteTemperatureSeries();
      wasReflowActive = false;
  }
}

void reflowControlInit(void) {
  pid_init();
}

void setActiveReflowOvenProfile(ReflowProfile profile) {
  activeProfile = profile;
}

void reflowControlTask(void) {
  // Read Temperature
  float temp = getTemperatur();

  // Print Temperture periodically
  char temp_str[10];  
  snprintf(temp_str, sizeof(temp_str), "%.1f°C", temp);
  lv_label_set_text(ui_LaActualTemperature, temp_str);

  // Actuall Reflow Oven Processing
  processReflowState(temp, startReflowProcess);
}


