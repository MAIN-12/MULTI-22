// ================ INPUTS ======================================================
#define start_i           34 // START selector,  (Must be a hardware interrupt pin)
#define eStop_i           37 // STOP button,     (Must be a hardware interrupt pin)
#define CFWR_i            27 // Conveyor Forward switch input pin 
#define CRWD_i            14 // Conveyor Rewind switch input pin
#define CStop_i           12 // Conveyor stop switch input pin 
#define swUp_i             0 // Up switch input pin
#define swDown_i           0 // Down switch input pin
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
#define power_o 	      14 // Enables the power of all subsystems
#define beacon_o           0 // Beacon light output pin
#define reflector_o        0 // Reflector light output pin
#define up_o               0 // Up output pin
#define down_o             0 // Down output pin
#define FWR_o              0 // Forward output pin
#define RWD_o              0 // Rewind output pin
#define CSpeed_o          25 // Conveyor speed output pin [PWM]
#define CReverse_o        04 // Conveyor speed output pin 
#define brakeIn_o          0 // Brake IN output pin 
#define breakeOut_o        0 // Brake OUT output pin
#define batteryState1_o    0 // Battery indicator color 1 output pin 
#define batteryState2_o    2 // Battery indicator color 2 output pin
#define generalState1_o    0 // General state color 1 output pin
#define generalState2_o    0 // General state color 2 output pin