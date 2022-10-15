/* ==============================================================================
 * Script by: Juan Carlos Botero
 * Date: 08/08/2020
 * Version: 2.0.0
 * ==============================================================================
 *                      Copyright (c) 2020 Charlie Projects
 *                      github.com/CharlieProjects/MULTI-19
 * ==============================================================================
 * ======================== CONVEYOR MULTI-19 RESOURCES =========================
 * ========================   Multiplo Colombia S.A.S.  =========================
 * ==============================================================================
 *  MIT License
 *
 * Copyright (c) 2020 CHARLIE PROJECTS
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// #include <Config.h>
#include <000 mainSetUp.h>

// ================================= FUNCIONES ==================================
void dualWrite(byte pin1, byte pin2, byte S1, byte S2)
{
  digitalWrite(pin1, S1);
  digitalWrite(pin2, S2);
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
    dacWrite(CSpeed_o, abs(ceil(-u_apos)));
  }
  else
  {
    ReversState = false;
    dacWrite(CSpeed_o, abs(ceil(u_apos)));
  }
  digitalWrite(CReverse_o, ReversState);
  delay(delta * 1000);
}

void Coveyor()
{
}

byte batteryCheck()
{
  byte BCP = map(analogRead(shunt_i), 100, 1023, 0, 100); // Configure Shunt ranges or implementa a diferent eq if necesary.

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

void dataLog() {}

// void click() {}
// void doubleclick() {}
// void longPressStart() {}
// void longPressStop() {}
// void longPress() {}

// void OneButtonBegin()
// {
//   button1.attachClick(click);
//   button1.attachDoubleClick(doubleclick);
//   button1.attachLongPressStart(longPressStart);
//   button1.attachLongPressStop(longPressStop);
//   button1.attachDuringLongPress(longPress);
// }

void ConveyorBegin()
{
  for (byte i = 0; i < sizeof(DIGITAL_INPUTS); i++)
  {
    pinMode(DIGITAL_INPUTS[i], INPUT_PULLDOWN);
  }
  for (byte i = 0; i < sizeof(DIGITAL_OUTPUTS); i++)
  {
    pinMode(DIGITAL_OUTPUTS[i], OUTPUT);
    digitalWrite(DIGITAL_OUTPUTS[i], LOW);
  }
  // OneButtonBegin();
}

void EMERGENCY_STOP()
{
  digitalWrite(power_o, LOW);
  digitalWrite(FWR_o, LOW);
  digitalWrite(RWD_o, LOW);
  digitalWrite(up_o, LOW);
  digitalWrite(down_o, LOW);
}