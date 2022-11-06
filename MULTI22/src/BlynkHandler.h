#include "BlynkEdgent.h"
#include <CStates.h>
BlynkTimer timer;
WidgetTerminal terminal(V0);

#define GENERAL_STATE V1
#define CONVEYOR_STATE V2
#define S_BUTTON V3
#define FWR_BUTTON V4
#define BWR_BUTTON V5

BLYNK_CONNECTED()
{
    Blynk.syncAll();
    Blynk.syncVirtual(GENERAL_STATE);
    Blynk.syncVirtual(CONVEYOR_STATE);
}

BLYNK_WRITE(S_BUTTON)
{
    if (param.asInt())
    {
        SetState(0);
    }
}

BLYNK_WRITE(FWR_BUTTON)
{
    if (param.asInt())
    {
        SetState(1);
    }
}
BLYNK_WRITE(BWR_BUTTON)
{
    if (param.asInt())
    {
        SetState(2);
    }
}

void InternatParameters() //<-----------------check this
{
    Blynk.virtualWrite(GENERAL_STATE, state);
    Blynk.virtualWrite(CONVEYOR_STATE, oState);
}
