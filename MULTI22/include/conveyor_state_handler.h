#ifndef CSTATE_H
#define CSTATE_H

/********************************************************************************
 * @file        conveyor_state_handler.h
 * @author      Juan Carlos Botero
 * @date        04/12/2024
 * @version     2.0.0
 * @brief       Header file for generationg log documentation of the execution.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************
 */

#include "conveyor_controller.h"
#include "battery_management.h"

enum MainFSMState
{
    STAND_BY = 0,  // main FSM state 1
    OPERATION = 1, // main FSM state 2
    CHARGING = 2,  // main FSM state 3
    E_STOP = 3,    // main FSM state 4
    SLEEP = 4      // main FSM state 5
};

enum ConveyorFSMState
{
    STOP = 0, // Operational state Stop
    FWR = 1,  // Operational state Forward
    BWR = 2   // Operational state Backward
};

MainFSMState currentState = STAND_BY;
MainFSMState previousState = STAND_BY;
ConveyorFSMState currentConveyorState = STOP;
ConveyorFSMState previousConveyorState = STOP;

int getConveyorState()
{
    return currentConveyorState;
}

int getGeneralState()
{
    return currentState;
}

void ConveyorStateCheck()
{
    if (digitalRead(CStop_i))
    {
        // dacWrite(CSpeed_o, ceil(VelMin));
        // analogWrite(CSpeed_o, ceil(VelMin));
        waitMillis = millis();
        currentConveyorState = STOP;
    }
    else if (digitalRead(CFWR_i))
    {
        waitMillis = millis();
        currentConveyorState = FWR;
    }

    else if (digitalRead(CRWD_i))
    {
        waitMillis = millis();
        currentConveyorState = BWR;
    }
}

int setConveyorState(byte cState)
{
    switch (cState)
    {
    case STOP:
        analogWrite(CSpeed_o, VelMin);
        digitalWrite(CReverse_o, LOW);
        break;

    case FWR:
        analogWrite(CSpeed_o, VelMax);
        digitalWrite(CReverse_o, LOW);
        break;

    case BWR:
        analogWrite(CSpeed_o, VelMax);
        digitalWrite(CReverse_o, HIGH);
        break;
    default:
        break;
    }
    return currentConveyorState;
}

int StandBy()
{
    digitalWrite(power_o, LOW);
    analogWrite(CSpeed_o, LOW);
    digitalWrite(CReverse_o, LOW);
    batteryCheckStandBy();
    currentConveyorState = STOP;

    currentState = (digitalRead(start_i) && !digitalRead(eStop_i)) ? OPERATION
                                                                   : STAND_BY;
    waitMillis = (currentState == OPERATION) ? millis()
                 : !digitalRead(start_i)     ? 0
                                             : waitMillis;
    return currentState;
}

int Operation()
{
    digitalWrite(power_o, HIGH);
    ConveyorStateCheck();
    setConveyorState(currentConveyorState);
    batteryCheck();
    // elevation();
    // illumination();

    return currentState = (digitalRead(eStop_i))               ? E_STOP
                          : (!digitalRead(start_i))            ? STAND_BY
                          : (millis() - waitMillis > waitTime) ? SLEEP
                                                               : OPERATION;
}

int Charging()
{
    digitalWrite(power_o, LOW);
    batteryCheck();
    return currentState = !digitalRead(charger_i) ? STAND_BY : CHARGING;
}

int EStop()
{
    EMERGENCY_STOP();
    return currentState = (!digitalRead(start_i) && !digitalRead(eStop_i)) ? STAND_BY
                                                                           : E_STOP;
}

int Sleep()
{
    digitalWrite(power_o, LOW);
    analogWrite(CSpeed_o, VelMin);
    digitalWrite(CReverse_o, LOW);
    batteryCheckStandBy();
    currentConveyorState = STOP;
    return currentState = (!digitalRead(start_i) && !digitalRead(eStop_i)) ? STAND_BY
                                                                           : E_STOP;
}

int UndefinedState()
{
    Serial.println("Undefined state");
    return currentState = STAND_BY;
}

void testGoldenOutput()
{
    analogWrite(CSpeed_o, VelMax);
    digitalWrite(CReverse_o, HIGH);
}

int conveyourMain()
{
    switch (currentState)
    {
    case STAND_BY:   return StandBy();
    case OPERATION:  return Operation();
    case CHARGING:   return Charging();
    case E_STOP:     return EStop();
    case SLEEP:      return Sleep();
    default:         return UndefinedState();
    }
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
#endif