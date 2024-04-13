#ifndef LOG_FUNCTIONS_H
#define LOG_FUNCTIONS_H

/********************************************************************************
 * @file        log_functions.h
 * @author      Juan Carlos Botero
 * @date        08/08/2020
 * @version     1.2.0
 * @brief       Header file for generationg log documentation of the execution.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************
 */

struct LogEntry
{
    String codeVersion;
    int status;
    mutable bool variablesUpdated;
    unsigned long timestamp;
    int generalState;
    int conveyorState;

    struct BatteryProperties
    {
        int status;
        float voltage;
        float current;
        float temp;
    } battery;

    int errorCode[12];

    void setState(int newGeneralState, int newConveyorState)
    {
        if (generalState != newGeneralState || conveyorState != newConveyorState)
        {
            generalState = newGeneralState;
            conveyorState = newConveyorState;
            variablesUpdated = true;
        }
    }

    void update()
    {
        variablesUpdated = true;
    }

    void resetUpdatedFlag()
    {
        variablesUpdated = false;
    }
};

void processSerialCommands()
{
    if (Serial.available() > 0)
    {
        String command = Serial.readStringUntil('\n');
        command.trim(); // Remove leading and trailing whitespace

        // Check for debug mode commands
        if (command.equals("debug mode"))
        {
            debugMode = true;
            Serial.println("Debug mode enabled.");
        }
        else if (command.equals("end debug"))
        {
            debugMode = false;
            Serial.println("Debug mode disabled.");
        }
        else if (command.equals("test battery indicator"))
        {
            // Call function to test battery indicator
            testBatteryIndicator();
        }
        else
        {
            Serial.println("Unknown command.");
        }
    }
}

void printLogEntry(const LogEntry &entry)
{
    if (debugMode && entry.variablesUpdated)
    {
        Serial.println();
        Serial.println("-------------------------------------------");
        Serial.print("New Log Entry | ");
        Serial.print("Timestamp: ");
        Serial.print(entry.timestamp);
        Serial.println();
        Serial.print("General State: ");
        Serial.print(entry.generalState);
        Serial.print(" | Conveyor State: ");
        Serial.println(entry.conveyorState);
        Serial.print("Battery Status: ");
        Serial.print(entry.battery.status);
        Serial.println();
        Serial.print("Voltage: ");
        Serial.print(entry.battery.voltage);
        Serial.print(" | Current: ");
        Serial.print(entry.battery.current);
        Serial.print(" | Temperature: ");
        Serial.print(entry.battery.temp);
        Serial.println();
        Serial.println("-------------------------------------------");

        entry.variablesUpdated = false;
    }
}

void initLog()
{

    // bms.update();
    // conveyor.timestamp = millis();
    // conveyor.codeVersion = version;
    // conveyor.setState(getGeneralState(), getConveyorState());
    // conveyor.battery.status = bms.get.packSOC;
    // conveyor.battery.voltage = bms.get.packVoltage;
    // conveyor.battery.current = bms.get.packCurrent;
    // conveyor.battery.temp = bms.get.tempAverage;
    // conveyor.update();
    // printLogEntry(conveyor);
}
#endif // LOG_FUNCTIONS_H
