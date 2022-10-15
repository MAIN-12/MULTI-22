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

// ================ INPUTS ======================================================
#define start_i           36 // START selector,  (Must be a hardware interrupt pin)
#define eStop_i           37 // STOP button,     (Must be a hardware interrupt pin)
#define CFWR_i            35 // Conveyor Forward switch input pin 
#define CRWD_i            32 // Conveyor Rewind switch input pin
#define CStop_i           39 // Conveyor stop switch input pin 
#define swUp_i            33 // Up switch input pin
#define swDown_i          25 // Down switch input pin
#define limitUp_i          0 // Limit end switch input pin
#define limitDown_i        0 // Limit end switch input pin
#define swBeacon_i         0 // Beacon light switch input pin
#define swReflector_i      0 // Reflector light switch input pin
#define swBrake_i          0 // Breaker switch 
#define shunt_i            0 // Shunt sensor input pin
#define temp_i             0 // Temp sensor input pin
#define hum_i              0 // Hum sensor input pin
#define charger_i          0 // Charger input pin (Must be a hardware interrupt pin)
#define sw1_i              0 // Aux switch input pin
#define sw2_i              0 // Aux switch input pin
#define sw3_i              0 // Aux switch input pin
#define sw4_i              0 // Aux switch input pin
 
// ================== OUTPUTS ===================================================
#define power_o 	        14 // Enables the power of all subsystems
#define beacon_o           0 // Beacon light output pin
#define reflector_o        0 // Reflector light output pin
#define up_o               0 // Up output pin
#define down_o             0 // Down output pin
#define FWR_o              0 // Forward output pin
#define RWD_o              0 // Rewind output pin
#define CSpeed_o          25 // Conveyor speed output pin [PWM]
#define CReverse_o        27 // Conveyor speed output pin 
#define brakeIn_o          0 // Brake IN output pin 
#define breakeOut_o        0 // Brake OUT output pin
#define batteryState1_o    0 // Battery indicator color 1 output pin 
#define batteryState2_o    2 // Battery indicator color 2 output pin
#define generalState1_o    0 // General state color 1 output pin
#define generalState2_o    0 // General state color 2 output pin

// ================== STATES ====================================================
#define STAND_BY         0 // main FSM state 1
#define OPERATION        1 // main FSM state 2
#define CHARGING         2 // main FSM state 3
#define E_STOP           3 // main FSM state 4
byte state = STAND_BY;
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

// ============= OTHER VARIABLES ================================================
const int baudRate = 115200;
const long frequency = 915E6;  // LoRa Frequency
const int csPin =       10;    // LoRa radio chip select
const int resetPin =     9;    // LoRa radio reset
const int irqPin =       2;    // (Must be a hardware interrupt pin)

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
