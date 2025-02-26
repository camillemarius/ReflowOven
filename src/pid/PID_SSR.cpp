#include "PID_SSR.h"  // Include your header file

#include <Arduino.h>   // Ensure Arduino functions like pinMode, ledcSetup, etc. are available

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

// Define the setup function for the PID controller
void pid_setup() {
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

// Define the function to calculate the PID output based on the temperature
void pid_updateControl(double temperature) {
  input_pid = temperature;
  
  // Run the PID controller to adjust the output
  myPID.Compute();
  
  // Control the SSR using PWM (0-255)
  ledcWrite(PWM_CHANNEL, output);
}


void pid_setRefTemperature(double temperature) {
    setpoint = temperature;
}
