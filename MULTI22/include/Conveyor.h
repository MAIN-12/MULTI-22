/* ==============================================================================
 * Script by: Juan Carlos Botero
 * Date: 08/08/2020
 * Version: 2.3.0
 * ==============================================================================
 *                      Copyright (c) 2020 Charlie Projects
 *                      github.com/CharlieProjects/MULTI-19
 * ==============================================================================
 * ======================== CONVEYOR MULTI-19 RESOURCES =========================
 * ========================   Multiplo Colombia S.A.S.  =========================
 * ==============================================================================
 *  MIT License
 * Copyright (c) 2020 CHARLIE PROJECTS
 */

#include "setup_functions.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// ================================= FUNCIONES ==================================
void dualWrite(byte pin1, byte pin2, byte S1, byte S2)
{
  digitalWrite(pin1, S1);
  digitalWrite(pin2, S2);
}
void TrafficLight(byte pin1, byte pin2, byte pin3, byte S1, byte S2, byte S3)
{
  digitalWrite(pin1, S1);
  digitalWrite(pin2, S2);
  digitalWrite(pin3, S3);
}

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

byte batteryCheck_2ligths()
{
  bms.update();
  float voltage = bms.get.packVoltage;
  byte BCP = map(analogRead(voltage), batteryMaxVoltage, batteryMaxVoltage, 0, 100); // Configure Shunt ranges or implementa a diferent eq if necesary.
  switch (BCP)
  {
  case 0 ... 25:
    if (millis() - blinkMillis >= blinkInterval)
    {
      dualWrite(batteryState1_o, batteryState2_o, LOW, !digitalRead(batteryState2_o));
      blinkMillis = millis();
    }
    break;
  case 26 ... 50:
    dualWrite(batteryState1_o, batteryState2_o, LOW, HIGH);
    break;
  case 51 ... 75:
    dualWrite(batteryState1_o, batteryState2_o, HIGH, LOW);
    break;
  case 76 ... 100:
    dualWrite(batteryState1_o, batteryState2_o, LOW, LOW);
    break;
  }
  return BCP;
}
byte batteryCheck_3ligths()
{
  bms.update();
  float voltage = bms.get.packVoltage;
  byte BCP = int(voltage);

  // byte BCP = map(analogRead(voltage), batteryMaxVoltage, batteryMaxVoltage, 0, 100); // Configure Shunt ranges or implementa a diferent eq if necesary.
  switch (BCP)
  {
  case 0 ... 39:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
    break;
  case 40 ... 42:

    if (millis() - blinkMillis >= blinkInterval)
    {
      TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, !digitalRead(batteryRedLigth));
      blinkMillis = millis();
    }

    break;
  case 43 ... 45:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, HIGH, LOW);
    break;
  case 46 ... 55:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, HIGH, LOW, LOW);
    break;
  }
  return BCP;
}
byte bateryLightTesting()
{
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, HIGH, LOW, LOW);
  delay(1500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, HIGH, LOW);
  delay(1500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, LOW);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, LOW);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, LOW);
  delay(500);
  return 0;
}
void testBatteryIndicator()
{
  bateryLightTesting();
}

byte batteryCheck()
{
  // Check if it's time to run the function
  if (millis() - batteryPreviousMillis >= bateryInterval)
  {
    // Save the current time for the next interval
    batteryPreviousMillis = millis();

    return batteryCheck_3ligths();
  }
  else
  {
    return 0;
  }
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