/* ==============================================================================
 * Script by: Juan Carlos Botero
 * Date: 09/20/2022
 * Version: 3.0.0
 * ==============================================================================
 *                         Copyright (c) 2022 MAIN 12 LLC
 * ==============================================================================
 * ========================      CONVEYOR MULTI-22      =========================
 * ========================   Multiplo Colombia S.A.S.  =========================
 *  MIT License
 */

// =============== INCLUDE ======================================================

/* 
# VARIABLES & FUNCTIONS NAME NOTATION

    variableName_i input pin notation. 
    variableName_o output pin notation.
    _variableName: Object private property notation. 
    VARIABLE: State name notation. 

    functionName = Normal Function Name notation 
    FunctionName = Object methot name notation. 
    FUNCTION_NAME = Critical proces function notation. 

*/

#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include<MultiBoards.h>
#define MARIN_BOARD
MultiBoardsBegin();



// #include <RTClib.h>
// #include <OneButton.h>
// #include <LoRa.h>
// #include <ESP8266WiFi.h>
// #include <GoldenMotor.h>
// #include <Display.h>

// extern "C"
// {
// #include "user_interface.h"
// }

// =============== CODE VERSION =================================================
#define version '3.0.0'
char update[]= "09-20-2022";
char ID[]= "XXXX001MULTI22";



// ================== STATES ====================================================
#define STAND_BY         0 // main FSM state 1
#define OPERATION        1 // main FSM state 2
#define CHARGING         2 // main FSM state 3
#define E_STOP           3 // main FSM state 4

#define S                0 //Operational state Stop
#define FWR              1 //Operational state Foward
#define BWR              2 //Operational state Backward

byte state = STAND_BY;
byte oState = S; //Operational Stae 
byte oldstate =         -1;

byte elevationState =    0;
byte brakesState =       0;

// ============= CONVEYOR VARIABLES ================================================

const float ts = 5;
const float VelMin = 75;
const float VelMax = 160;
float u_apri = VelMin;
float u_apos = VelMin;
bool ReversState;


// ============= TIME VARIABLES ================================================
uintmax_t blinkMillis =       0;
uintmax_t waitMillis =        0;
uintmax_t brakeMillis =       0;
const int blinkInterval =   500;
const int waitTime =    30000;
const int brakeTime =      1000;

// =============== SETTINGS =====================================================
byte DIGITAL_INPUTS[] = {start_i, eStop_i, CFWR_i, CRWD_i, CStop_i, swUp_i, swDown_i, limitUp_i, limitDown_i, swBeacon_i, swReflector_i, charger_i, sw1_i, sw2_i, sw3_i, sw4_i }; //
byte DIGITAL_OUTPUTS[] = {beacon_o, reflector_o, up_o, down_o, FWR_o, RWD_o, batteryState1_o, batteryState2_o, generalState1_o, generalState2_o};//
// OneButton button1(swStop, true);
