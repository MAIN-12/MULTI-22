/* ==============================================================================
 * Script by: Juan Carlos Botero
 * Date: 04/06/2024
 * ==============================================================================
 *                         Copyright (c) 2024 MAIN 12 LLC
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
 * MIT License
 * Copyright (c) 2024 MAIN 12 LLC
 */

#define Debug_Mode
#include <CStates.h>
#include "log_functions.h"
LogEntry conveyor;

void setup()
{
  setupMain();
  attachInterrupt(CStop_i, ConveyorStateCheck, CHANGE);
  attachInterrupt(CFWR_i, ConveyorStateCheck, CHANGE);
  attachInterrupt(CRWD_i, ConveyorStateCheck, CHANGE);

  bms.update();

  conveyor.timestamp = millis();
  conveyor.codeVersion = version;
  conveyor.setState(getGeneralState(), getConveyorState());
  conveyor.battery.status = bms.get.packSOC;
  conveyor.battery.voltage = bms.get.packVoltage;
  conveyor.battery.current = bms.get.packCurrent;
  conveyor.battery.temp = bms.get.tempAverage;
  printLogEntry(conveyor);
}

void loop()
{
  // testGoldenOutput();
  // processSerialCommands();
  conveyourMain();
  conveyor.codeVersion = version;
  conveyor.timestamp = millis();
  conveyor.setState(getGeneralState(), getConveyorState());

  conveyor.battery.voltage = batteryCheck();
  printLogEntry(conveyor);

  // writeToSD(conveyor);
}