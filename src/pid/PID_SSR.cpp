/**
 * @file pid_ssr.cpp
 * @brief This file contains the implementation of a PID controller for temperature regulation using a Solid State Relay (SSR).
 *
 * The code initializes and manages a PID controller to maintain a desired temperature setpoint. It uses PWM to control
 * the SSR, which in turn regulates the power to a heating element. The PID controller is configured with specific tuning
 * parameters (Kp, Ki, Kd) and operates in automatic mode. The functions provided allow for initialization, updating the
 * current temperature, and setting a new reference temperature.
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "pid_ssr.h"
#include <Arduino.h>

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

// Pin Definitions
const int SSR_PIN = 17;        // Solid State Relay control pin

// Define global PID tuning parameters
double Kp = 2.0, Ki = 5.0, Kd = 1.0;

// Setpoint and input/output for the PID controller
double setpoint = 25.0;     // Desired temperature in Celsius
double input_pid = 0.0;     // Actual temperature from sensor
double output = 0.0;        // Output to SSR (0-255)

// Define the PID object
PID myPID(&input_pid, &output, &setpoint, Kp, Ki, Kd, DIRECT);

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/

void pid_init() {
  // Set SSR_PIN as an output pin
  pinMode(SSR_PIN, OUTPUT);

  // Configure the LEDC (PWM) properties for ESP32
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  
  // Attach the PWM signal to the SSR_PIN
  ledcAttachPin(SSR_PIN, PWM_CHANNEL);

  // Initialize the PID controller
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255);  // Output limits for PWM control
}

void pid_updateTemperature(double temperature) {
  input_pid = temperature;
  
  // Run the PID controller to adjust the output
  myPID.Compute();
  
  // Control the SSR using PWM (0-255)
  ledcWrite(PWM_CHANNEL, output);
}

void pid_setReferenceTemperature(double temperature) {
    setpoint = temperature;
}
