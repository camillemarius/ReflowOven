#include "temperatur_sensor.h"


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

float getTemperatur() {
    return thermocouple.readCelsius();
}