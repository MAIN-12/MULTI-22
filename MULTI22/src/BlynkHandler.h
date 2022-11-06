#include "BlynkEdgent.h"
#include <CStates.h>
BlynkTimer timer;
WidgetTerminal terminal(V0);

#define GENERAL_STATE V1
#define CONVEYOR_STATE V2

BLYNK_CONNECTED()
{
    Blynk.syncAll();
    Blynk.syncVirtual(GENERAL_STATE);
    Blynk.syncVirtual(CONVEYOR_STATE);
}

void InternatParameters() //<-----------------check this
{
    Blynk.virtualWrite(GENERAL_STATE, state);
    Blynk.virtualWrite(CONVEYOR_STATE, oState);
}
