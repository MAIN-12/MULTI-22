#ifndef MultiBoards_h
#define MultiBoards_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



#ifdef  BOARD_Marin_v3
#include <MarinBoard.h>
#else

#ifdef  BOARD_NORVI_IOT
#include <NORVI_IOT.h>
#endif
#endif


byte DIGITAL_INPUTS[] = {start_i, eStop_i, CFWR_i, CRWD_i, CStop_i, swUp_i, swDown_i, limitUp_i, limitDown_i, swBeacon_i, swReflector_i, charger_i, sw1_i, sw2_i, sw3_i, sw4_i }; //
byte DIGITAL_OUTPUTS[] = {beacon_o, reflector_o, up_o, down_o, FWR_o, RWD_o, batteryState1_o, batteryState2_o, generalState1_o, generalState2_o};//


#endif
