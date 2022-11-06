#include <Conveyor.h>

void ConveyorStateCheck()
{

    if (digitalRead(CStop_i))
    {
        dacWrite(CSpeed_o, ceil(VelMin));
        oState = S;
    }
    else if (digitalRead(CFWR_i))
    {
        oState = FWR;
    }

    else if (digitalRead(CRWD_i))
    {
        oState = BWR;
    }
}

int ConveyorState(byte cState)
{
    switch (cState)
    {
    case S:
        digitalWrite(CReverse_o, HIGH);
        dacWrite(CSpeed_o, ceil(VelMin));
        break;

    case FWR:
        ConveyorControl(VelMax);
        break;

    case BWR:
        ConveyorControl(-VelMax);
        break;
    default:
        break;
    }
    return oState;
}

int StandBy()
{
    digitalWrite(power_o, LOW);
    // batteryCheck();

    state = (digitalRead(start_i) && !digitalRead(eStop_i) && !waitMillis) ? OPERATION
                                                                           : STAND_BY;
    waitMillis = (state == OPERATION)    ? millis()
                 : !digitalRead(start_i) ? 0
                                         : waitMillis;
    return state;
}

int Operation()
{
    digitalWrite(power_o, HIGH);
    ConveyorState(oState);
    // elevation();
    // batteryCheck();
    // illumination();

    return state = digitalRead(eStop_i)                                            ? E_STOP
                   : (!digitalRead(start_i) || (millis() - waitMillis > waitTime)) ? STAND_BY
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

int UndefinedState()
{
    Serial.println("Undefined state");
    return state = STAND_BY;
}

void stateDebug()
{
    if (oldstate != state)
    {
        oldstate = state;
        Serial.print("STATE: ");
        Serial.println(state);
    }
}