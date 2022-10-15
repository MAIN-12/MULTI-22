/* ==============================================================================
 * Script by: Juan Carlos Botero 
 * Date: 08/08/2020
 * Version: 2.0.0
 * ==============================================================================
 *                      Copyright (c) 2020 Charlie Projects                      
 *                      github.com/CharlieProjects/MULTI-19                      
 * ==============================================================================
 * ========================      CONVEYOR MULTI-19      =========================
 * ========================   Multiplo Colombia S.A.S.  =========================
 * ==============================================================================
 *  Description:
 *  This is the main code of the control structure of the conveyor MULTI-19 is 
 *  intend to be compiled whit Visual Studio Code using the Platformio plug, this
 *  code works by itself, including all the external libraries in the project path
 *  in the "lib" folder as well as the auxiliary functions and reusable resources
 *  in the "include" folder.
 * 
 *  The proposed programming architecture is based on object-oriented finite state 
 *  machines the architecture documentation can be found attached to the project 
 *  path, otherwise request directly from Charlie projects.
 * 
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

#include <Conveyor.h>
char incomingByte = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println();
  Serial.println("========== CHARLIE PROJECT ==========");
  Serial.println("projectsbycharlie.com");
  Serial.println("...Set Up...");

  // display.init();
  // displayBegin();
  ConveyorBegin();
}

void loop()
{
  switch (state)
  {
  case STAND_BY:
    digitalWrite(POWER, LOW);
    brakes();
    batteryCheck();
    dataLog();

    state = (digitalRead(START) && !digitalRead(STOP) && !waitMillis) ? OPERATION : STAND_BY;
    waitMillis = (state == OPERATION) ? millis() : !digitalRead(START) ? 0 : waitMillis;
    break;
  case OPERATION:
    digitalWrite(POWER, HIGH);
    elevation();
    brakes();
    batteryCheck();
    illumination();
    dataLog();

    state = digitalRead(STOP) ? E_STOP : (!digitalRead(START) || (millis() - waitMillis > waitTime)) ? STAND_BY : OPERATION;
    break;
  case CHARGING:
    digitalWrite(POWER, LOW);
    batteryCheck();

    state = !digitalRead(charger) ? STAND_BY : CHARGING;
    break;
  case E_STOP:
    digitalWrite(POWER, LOW);
    digitalWrite(FWR, LOW);
    digitalWrite(RWD, LOW);
    digitalWrite(up, LOW);
    digitalWrite(down, LOW);
    dataLog();

    state = (!digitalRead(START) && !digitalRead(STOP)) ? STAND_BY : E_STOP;
    break;
  default:
    Serial.println("Undefined state");

    state = STAND_BY;
    break;
  }

  if (oldstate != state)
  {
    oldstate = state;
    Serial.print("STATE: ");
    Serial.println(state);
  }

  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}