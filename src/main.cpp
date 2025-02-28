/**
 * @file main.cpp
 * @brief Main loop function for handling periodic updates.
 * 
 * This function continuously checks the elapsed time and performs
 * updates for the GUI and temperature control at specified intervals.
 * It ensures the GUI is updated every 10 milliseconds and the
 * temperature is updated every 1000 milliseconds. A delay of 5
 * milliseconds is included at the end of each loop iteration to
 * prevent excessive CPU usage.
 */

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include "lvgl_init.h"
#include "memory_profile_management.h"
#include "reflow_oven_control.h"
#include "sensor_temperature.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
const uint32_t GUI_UPDATE_INTERVAL = 10;    
const uint32_t REFLOW_UPDATE_INTERVAL = 1000; 
const uint32_t TEMP_UPDATE_INTERVAL = 500;

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/

/**
 * @brief Setup function for initializing the system.
 * 
 * This function initializes the custom UI, loads profiles, and sets up
 * the reflow oven control system.
 */
void setup()
{
    initCustomLVGL(); 
    loadProfiles();
    ui_init();

    initChart();
    reflowControlInit();
}


/**
 * @brief Main loop function for handling updates.
 * 
 * This function handles periodic updates for the GUI and temperature
 * control based on predefined intervals.
 */
void loop() {
  static unsigned long last_gui_update = 0;
  static unsigned long last_temp_update = 0;
  static unsigned long last_reflow_update = 0;

  unsigned long current_time = millis();

  // Handle GUI updates
  if (current_time - last_gui_update >= GUI_UPDATE_INTERVAL) {
    lv_timer_handler(); 
    last_gui_update = current_time;
  }

  // Handle temperature updates
  if (current_time - last_temp_update >= TEMP_UPDATE_INTERVAL) {
    addTemperatureToFilter();
    last_temp_update = current_time;
  }

  // Handle temperature updates
  if (current_time - last_reflow_update >= REFLOW_UPDATE_INTERVAL) {
    reflowControlTask();
    last_reflow_update = current_time;
  }

  delay(5);
}