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

#include <CStates.h>
#include "log_functions.h"

void setup()
{
  setupMain();
  // printHeader(version);
  attachInterrupt(CStop_i, ConveyorStateCheck, CHANGE);
  attachInterrupt(CFWR_i, ConveyorStateCheck, CHANGE);
  attachInterrupt(CRWD_i, ConveyorStateCheck, CHANGE);
}

void loop()
{
  testGoldenOutput();

  // processSerialCommands();
  // LogEntry logEntry;
  // logEntry.codeVersion = "3.0.0";
  // logEntry.timestamp = millis();
  // logEntry.state = conveyourMain();
  // logEntry.state = conveyourMain();
  // logEntry.batteryStatus = batteryCheck();
  // printLogEntry(logEntry);

  // writeToSD(logEntry);
}