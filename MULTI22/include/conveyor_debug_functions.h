#ifndef CONVEYOR_DEBUG_FUNCTIONS_H
#define CONVEYOR_DEBUG_FUNCTIONS_H

/********************************************************************************
 * @file        conveyor_debug_functions.h
 * @author      Juan Carlos Botero
 * @date        04/12/2024
 * @version     1.0.0
 * @brief       Header file for generationg log documentation of the execution.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************
 */

#include "00_setup_functions.h"
#include "conveyor_controller.h"


void testGoldenOutput()
{
    analogWrite(CSpeed_o, VelMax);
    digitalWrite(CReverse_o, HIGH);
}

void stateDebug()
{
    if ((previousState != currentState) || (previousConveyorState != currentConveyorState))
    {
        previousState = currentState;
        previousConveyorState = currentConveyorState;
        Serial.print("General state: ");
        Serial.print(currentState);
        switch (currentState)
        {
        case 0:
            Serial.print("Stand By");
            break;
        case 1:
            Serial.print("Operational");
            break;
        case 2:
            Serial.print("CHARGING");
            break;
        case 3:
            Serial.print("E-STOP");
            break;
        case 4:
            Serial.print("Sleeping");
            Serial.print("....I got bored and fell asleep");
            break;
        default:
            Serial.print("State Error");
            break;
        }

        Serial.print(" | Conveyor state");

        switch (currentConveyorState)
        {
        case 0:
            Serial.print("stand by");
            break;
        case 1:
            Serial.print("FWR");
            break;
        case 2:
            Serial.print("RWD");
            break;

        default:
            Serial.print("conveyor state error");
            break;
        }
        Serial.println("");

        // Serial.printlnf("Start Sw: %d | E-STOP p: %d | FWR p: %d | RWD p: %d | Stop p: %d ",digitalRead(start_i),digitalRead(eStop_i),digitalRead(CFWR_i),digitalRead(CRWD_i),digitalRead(CStop_i));
        // Serial.printlnf("power: %d | SPEED: %d | REVERS: %d ",digitalRead(power_o),digitalRead(CSpeed_o),digitalRead(CReverse_o));
        // "you have %d hours to come to me",time
    }
}
#endif // CONVEYOR_DEBUG_FUNCTIONS_H
