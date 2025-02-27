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

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/

float getTemperatur() {
    return thermocouple.readCelsius();
}