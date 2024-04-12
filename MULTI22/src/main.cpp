/* ==============================================================================
 * Script by: Juan Carlos Botero
 * Date: 04/06/2024
 * ==============================================================================
 *                   Copyright (c) 2024 MAIN 12 LLC
 * ==============================================================================
 * ========================      CONVEYOR MULTI-22      =========================
 * ========================   Multiplo Colombia S.A.S.  =========================
 * ==============================================================================
 * Description:
 * This script serves as the primary control structure for the CONVEYOR MULTI-22,
 * developed by Multiplo Colombia S.A.S. It is designed to be compiled with Visual
 * Studio Code using the PlatformIO plugin. The code is self-contained, including
 * all necessary external libraries located in the "lib" folder, as well as 
 * auxiliary functions and reusable resources in the "include" folder.
 *
 * The programming architecture is built upon object-oriented finite state machines.
 * For detailed documentation on the architecture, please refer to the attached
 * documentation within the project folder, or reach out directly to Main12 LLC.
 *
 * ==============================================================================
 * MIT License
 * Copyright (c) 2024 MAIN 12 LLC
 */

#include "conveyor_state_handler.h"
#include "log_functions.h"

void setup()
{
  setupMain();
  attachInterrupt(CStop_i, ConveyorStateCheck, CHANGE);
  attachInterrupt(CFWR_i, ConveyorStateCheck, CHANGE);
  attachInterrupt(CRWD_i, ConveyorStateCheck, CHANGE);

}

void loop()
{
  // processSerialCommands();
  conveyourMain();
  // testGoldenOutput();
  // writeToSD(logEntry);
}