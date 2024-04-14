#ifndef CONVEYOR_CONTROLLER_H
#define CONVEYOR_CONTROLLER_H

/********************************************************************************
 * @file        conveyor_controller.h
 * @author      Juan Carlos Botero
 * @date        08/08/2020
 * @version     2.4.0
 * @brief       Header file for controlling the conveyor belt system.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************
 */

#include "00_setup_functions.h"
byte elevationState = 0;
byte brakesState = 0;

// ================================= FUNCIONES ==================================

void ConveyorControl(float ref)
{
  float Tau = ts / 5;
  float delta = 0.01;
  u_apri = u_apos;
  u_apos = (ref - u_apri) * delta / Tau + u_apri;
  u_apri = u_apos;
  if (u_apos < 0)
  {
    ReversState = true;
    // dacWrite(CSpeed_o, abs(ceil(-u_apos)));
    analogWrite(CSpeed_o, abs(ceil(-u_apos)));
  }
  else
  {
    ReversState = false;
    // dacWrite(CSpeed_o, abs(ceil(u_apos)));
    analogWrite(CSpeed_o, abs(ceil(u_apos)));
  }
  digitalWrite(CReverse_o, ReversState);
  delay(delta * 1000);
}

// const float time_step = 5;
// const float VelMin = 75; // 75
// const float VelMax = 160;
// float current_control_signal = VelMin;
// float previous_control_signal = VelMin;
// bool is_reversed;

// void ConveyorControl(float reference_speed)
// {
//   float Tau = time_step / 5;                                                                                    // Set the time constant (Tau) for the control system
//   float delta = 0.01;                                                                                           // Set the time increment for the control calculation
//   float previous_control_signal = current_control_signal;                                                       // Store the previous control signal value
//   current_control_signal = (reference_speed - previous_control_signal) * delta / Tau + previous_control_signal; // Calculate the new control signal using a first-order system approximation
//   previous_control_signal = current_control_signal;                                                             // Store the current control signal for future reference
//   bool is_reversed = (current_control_signal < 0);                                                              // Determine the direction of rotation based on the control signal
//   analogWrite(CSpeed_o, abs(ceil(current_control_signal)));                                    // Set the motor speed based on the absolute value of the control signal
//   digitalWrite(CReverse_o, is_reversed);                                                       // Set the motor direction based on the direction of rotation
//   delay(delta * 1000);
// }

void brakes()
{
  switch (brakesState)
  {
  case 0: // OFF
    brakesState = 0;
    break;
  case 1: // ON
    brakesState = 0;
    break;
  default:
    brakesState = 0;
    break;
  }
}

void dualWrite(byte pin1, byte pin2, byte S1, byte S2)
{
  digitalWrite(pin1, S1);
  digitalWrite(pin2, S2);
}

void elevation()
{
  switch (elevationState)
  {
  case 0: // STAND_BY
    dualWrite(up_o, down_o, LOW, LOW);
    elevationState = digitalRead(swUp_i) ? 1 : digitalRead(swDown_i) ? 2
                                                                     : 0;
    break;
  case 1: // UP
    dualWrite(up_o, down_o, HIGH, LOW);
    elevationState = (digitalRead(limitUp_i) || !digitalRead(swUp_i)) ? 0 : 1;
    break;
  case 2: // DOWN
    dualWrite(up_o, down_o, LOW, HIGH);
    elevationState = (digitalRead(limitDown_i) || !digitalRead(swDown_i)) ? 0 : 2;
    break;
  default:
    elevationState = 0;
    break;
  }
}

void illumination()
{
  dualWrite(beacon_o, reflector_o, digitalRead(swBeacon_i), digitalRead(swReflector_i));
}


#endif // CONVEYOR_CONTROLLER_H