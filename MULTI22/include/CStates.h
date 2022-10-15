#include <Conveyor.h>

int StandBy()
{
    digitalWrite(power_o, LOW);
    // batteryCheck();

    state = (digitalRead(start_i) && !digitalRead(eStop_i) && !waitMillis) ? OPERATION
                                                                               : STAND_BY;
    waitMillis = (state == OPERATION)     ? millis()
                 : !digitalRead(start_i) ? 0
                                          : waitMillis;
    return state;
}

int Operation()
{
    digitalWrite(power_o, HIGH);
    // elevation();
    // batteryCheck();
    // illumination();

    if (digitalRead(CStop_i)) //<-----------------------------------------Check
    {
        digitalWrite(CReverse_o, HIGH);
        dacWrite(CSpeed_o, ceil(VelMin));
    }
    else if (digitalRead(CFWR_i))
        ConveyorControl(VelMax);
    else if (digitalRead(CRWD_i))
        ConveyorControl(-VelMax);

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
    state = (!digitalRead(start_i) && !digitalRead(eStop_i)) ? STAND_BY
                                                                 : E_STOP;
}

int UndefinedState()
{
    Serial.println("Undefined state");
    state = STAND_BY;
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