#include <Conveyor.h>

void ConveyorStateCheck()
{
    if (digitalRead(CStop_i))
    {
        // dacWrite(CSpeed_o, ceil(VelMin));
        // analogWrite(CSpeed_o, ceil(VelMin));
        waitMillis = millis();
        oState = S;
    }
    else if (digitalRead(CFWR_i))
    {
        waitMillis = millis();
        oState = FWR;
    }

    else if (digitalRead(CRWD_i))
    {
        waitMillis = millis();
        oState = BWR;
    }
}

int ConveyorState(byte cState)
{
    switch (cState)
    {
    case S:
        analogWrite(CSpeed_o, VelMin);
        digitalWrite(CReverse_o, LOW);
        // ConveyorControl(VelMin);
        // dacWrite(CSpeed_o, ceil(VelMin));
        break;

    case FWR:
        analogWrite(CSpeed_o, VelMax);
        digitalWrite(CReverse_o, LOW);
        // ConveyorControl(VelMax);
        break;

    case BWR:
        analogWrite(CSpeed_o, VelMax);
        digitalWrite(CReverse_o, HIGH);
        // ConveyorControl(-VelMax);
        break;
    default:
        break;
    }
    return oState;
}

int StandBy()
{
    digitalWrite(power_o, LOW);
    analogWrite(CSpeed_o, LOW);
    digitalWrite(CReverse_o, LOW);
    oState = S;
    // batteryCheck();

    state = (digitalRead(start_i) && !digitalRead(eStop_i)) ? OPERATION
                                                            : STAND_BY;
    waitMillis = (state == OPERATION)    ? millis()
                 : !digitalRead(start_i) ? 0
                                         : waitMillis;
    return state;
}

int Operation()
{
    digitalWrite(power_o, HIGH);
    ConveyorStateCheck();
    ConveyorState(oState);
    // elevation();
    // batteryCheck();
    // illumination();

    return state = (digitalRead(eStop_i))               ? E_STOP
                   : (!digitalRead(start_i))            ? STAND_BY
                   : (millis() - waitMillis > waitTime) ? SLEEP
                                                        : OPERATION;
}

int Charging()
{
    digitalWrite(power_o, LOW);
    batteryCheck();
    return state = !digitalRead(charger_i) ? STAND_BY : CHARGING;
}

int EStop()
{
    EMERGENCY_STOP();
    return state = (!digitalRead(start_i) && !digitalRead(eStop_i)) ? STAND_BY
                                                                    : E_STOP;
}

int Sleep()
{
    digitalWrite(power_o, LOW);
    analogWrite(CSpeed_o, VelMin);
    digitalWrite(CReverse_o, LOW);
    oState = S;
    return state = (!digitalRead(start_i) && !digitalRead(eStop_i)) ? STAND_BY
                                                                    : E_STOP;
}

int UndefinedState()
{
    Serial.println("Undefined state");
    return state = STAND_BY;
}

void stateDebug()
{
    if ((oldState != state) || (oldOState != oState))
    {
        oldState = state;
        oldOState = oState;
        Serial.print("General state: ");
        Serial.print(state);
        switch (state)
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

        switch (oState)
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