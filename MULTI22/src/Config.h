/********************************************************************************
 * @file        battery_management.h
 * @author      Juan Carlos Botero
 * @date        09/20/2022
 * @version     3.0.0
 * @brief       Header file for battery management functions.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************

# VARIABLES & FUNCTIONS NAME NOTATION

    variableName_i input pin notation.
    variableName_o output pin notation.
    _variableName: Object private property notation.
    VARIABLE: State name notation.

    functionName = Normal Function Name notation
    FunctionName = Object methot name notation.
    FUNCTION_NAME = Critical proces function notation.

*/

// =============== CODE VERSION =================================================
const String version = "3.0.5.";
char update[] = "04-12-2024";
char ID[] = "XXXX001MULTI22";

// ================ INPUTS ======================================================
#define start_i            3 // START selector,  (Must be a hardware interrupt pin)
#define eStop_i            2 // STOP button,     (Must be a hardware interrupt pin)
#define CFWR_i            A0 // Conveyor Forward switch input pin
#define CRWD_i            A1 // Conveyor Rewind switch input pin
#define CStop_i           A2 // Conveyor stop switch input pin
#define batteryVoltage_i   0 // Shunt sensor input pin
#define charger_i          0 // Charger input pin
#define swUp_i             0 // Up switch input pin
#define swDown_i           0 // Down switch input pin
#define limitUp_i          0 // Limit end switch input pin
#define limitDown_i        0 // Limit end switch input pin
#define swBeacon_i         0 // Beacon light switch input pin
#define swReflector_i      0 // Reflector light switch input pin
#define swBrake_i          0 // Breaker switch
#define temp_i             0 // Temp sensor input pin
#define hum_i              0 // Hum sensor input pin
#define sw1_i              0 // Aux switch input pin
#define sw2_i              0 // Aux switch input pin
#define sw3_i              0 // Aux switch input pin
#define sw4_i              0 // Aux switch input pin

// ================== OUTPUTS ===================================================
#define power_o            8 // Enables the power of all subsystems
#define CSpeed_o           5 // Conveyor speed output pin [PWM]
#define CReverse_o         4 // Conveyor speed output pin

#define beacon_o           0 // Beacon light output pin
#define reflector_o        0 // Reflector light output pin
#define up_o               0 // Up output pin
#define down_o             0 // Down output pin
#define FWR_o              0 // Forward output pin
#define RWD_o              0 // Rewind output pin
#define brakeIn_o          0 // Brake IN output pin
#define breakeOut_o        0 // Brake OUT output pin

#define batteryState1_o    0 // Battery indicator color 1 output pin
#define batteryState2_o    0 // Battery indicator color 2 output pin
#define generalState1_o    0 // General state color 1 output pin
#define generalState2_o    0 // General state color 2 output pin

#define batteryGreenLigth_o  A5 // Battery indicator color 1 output pin
#define batteryYellowLigth_o A4 // Battery indicator color 1 output pin
#define batteryRedLigth_o     9 // Battery indicator color 1 output pin

// ============= CONVEYOR VARIABLES ================================================
const float ts = 5;
const float VelMin = 75; // 75
const float VelMax = 160;
float u_apri = VelMin;
float u_apos = VelMin;
bool ReversState;

// ============= OTHER VARIABLES ================================================
// const int baudRate = 115200;
const long frequency = 915E6; // LoRa Frequency
const int csPin = 10;         // LoRa radio chip select
const int resetPin = 9;       // LoRa radio reset
const int irqPin = 2;         // (Must be a hardware interrupt pin)

// ============= TIME VARIABLES ================================================
uintmax_t blinkMillis = 0;
uintmax_t waitMillis = 0;
const unsigned long waitTime = 30 * 60000;
uintmax_t brakeMillis = 0;
const int blinkInterval = 500;
const int brakeTime = 1000;

//============== BATTERY ========================================================
bool batteryForceCheck = true;
float batteryMinVoltage = 38;     // [v]
float batteryMaxVoltage = 55;     // [v]
float batteryCharginVoltage = 58; // [v]

byte BatteryLowLevel = 43;
byte BatteryMidLevel = 45;
byte BatteryFullCharge = 55;

const long batteryInterval = 30000;
const long batteryIntervalStandBy = 120000;
const int rxPin = 11; // Define custom RX pin for the BMS
const int txPin = 12; // Define custom TX pin for the BMS
