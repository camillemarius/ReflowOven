/**
 * @file sensor_temperature.cpp
 * @brief Reads the temperature from a thermocouple sensor.
 * 
 * Utilizes the MAX6675 library to read the temperature
 * in Celsius from a thermocouple connected to specified pins.
 * 
 */


/* Includes ------------------------------------------------------------------*/
#include "sensor_temperature.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define FILTER_SIZE 3  // Number of readings to average

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
// Declare constants for the pins
//  FSPIQ:    Data out
//  FSPID:    Data in
//  FSPIHD:   Hold
//  FSPIWP:   Write protet
//  FSPICLK:  Clock
//  FSPICSO:  Chip select 
const int PIN_SCK = 12; //FSPICLK
const int PIN_SO = 13; //FSPIQ
const int PIN_CS = 11; //FSPICSO // 10 // 19

MAX6675 thermocouple(PIN_SCK, PIN_CS, PIN_SO);

float tempReadings[FILTER_SIZE] = {0};  // Array to store recent temperature readings
int tempReadingsIndex = 0;              // Index for circular buffer

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
static float getTemperatureFiltered(void) {
    float sum = 0;
    for (int i = 0; i < FILTER_SIZE; i++) {
        sum += tempReadings[i];
    }
    return sum / FILTER_SIZE;  // Return the moving average
}

float getTemperature(void) {
    //float rawTemp = thermocouple.readCelsius();
    
    // Store new reading in circular buffer
    //tempReadings[tempReadingsIndex] = rawTemp;
    //tempReadingsIndex = (tempReadingsIndex + 1) % FILTER_SIZE;

    return getTemperatureFiltered();
}

void addTemperatureToFilter(void) {
    float rawTemp = thermocouple.readCelsius();
    
    // Store new reading in circular buffer
    tempReadings[tempReadingsIndex] = rawTemp;
    tempReadingsIndex = (tempReadingsIndex + 1) % FILTER_SIZE;
}

