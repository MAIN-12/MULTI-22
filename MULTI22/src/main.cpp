/* ==============================================================================
 * Script by: Juan Carlos Botero
 * Date: 09/20/2022
 * Version: 3.0.0
 * ==============================================================================
 *                         Copyright (c) 2022 MAIN 12 LLC
 * ==============================================================================
 * ========================      CONVEYOR MULTI-22      =========================
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
 * Copyright (c) 2022 MAIN 12 LLC
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

#include <CStates.h>

void setup()
{
  MainSetUp();
  ConveyorBegin();
}

void loop()
{
  switch (state)
  {
  case STAND_BY:  StandBy();        break;
  case OPERATION: Operation();      break;
  case CHARGING:  Charging();       break;
  case E_STOP:    EStop();          break;
  default:        UndefinedState(); break;
  }

  stateDebug();
}