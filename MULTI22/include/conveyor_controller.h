/* ******************************************************************************
 * File:        conveyor_controller.h
 * Date:        04/12/2024
 * Version:     2.4.0
 * Version:     2.4.0
 * Description: Header file for controlling the conveyor belt system.
 * License:     [License Type]
 * Website:     [Project Website or Repository]
 * ******************************************************************************
 */

#ifndef CONVEYOR_CONTROLLER_H
#define CONVEYOR_CONTROLLER_H

#include "setup_functions.h"
#include "battery_management.h"

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

void EMERGENCY_STOP()
{
  digitalWrite(power_o, LOW);
  analogWrite(CSpeed_o, LOW);
  digitalWrite(CReverse_o, LOW);

  for (byte i = 0; i < sizeof(DIGITAL_OUTPUTS); i++)
  {
    pinMode(DIGITAL_OUTPUTS[i], OUTPUT);
    digitalWrite(DIGITAL_OUTPUTS[i], LOW);
  }
}
#endif //CONVEYOR_H