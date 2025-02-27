#ifndef __PID_H
#define __PID_H

#ifdef __cplusplus
extern "C" {
#endif


#include <PID_v1.h>  // Include the PID library


// PID tuning parameters (declare them externally in the .c file)
extern double Kp, Ki, Kd;

// Setpoint and input/output for the PID controller (declare them externally)
extern double setpoint;
extern double input_pid;
extern double output;

// Create PID object
extern PID myPID;

// PWM parameters
#define PWM_FREQUENCY 5000  // PWM frequency (5 kHz)
#define PWM_RESOLUTION 8    // 8-bit resolution (0-255)
#define PWM_CHANNEL 0       // PWM channel (0-15)


void pid_init();
void pid_updateTemperature(double temperature);
void pid_setReferenceTemperature(double temperature);


#ifdef __cplusplus
}
#endif

#endif