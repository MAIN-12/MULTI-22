#ifndef LOG_FUNCTIONS_H
#define LOG_FUNCTIONS_H

struct LogEntry
{
    String codeVersion;
    int status;
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

    bool variablesUpdated;

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

    void printLogEntry() const
    {
        if (debugMode && variablesUpdated)
        {
            Serial.println();
            Serial.println("-------------------------------------------");
            Serial.print("Timestamp: ");
            Serial.print(timestamp);
            Serial.print(" | General State: ");
            Serial.print(generalState);
            Serial.print(" | Conveyor State: ");
            Serial.println(conveyorState);
            Serial.print("Battery Status: ");
            Serial.print(battery.status);
            Serial.print(" | Voltage: ");
            Serial.print(battery.voltage);
            Serial.print(" | Current: ");
            Serial.print(battery.current);
            Serial.print(" | Temperature: ");
            Serial.print(battery.temp);
            Serial.println();
            Serial.println("-------------------------------------------");

            // Reset the flag after printing
            resetUpdatedFlag();
        }
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

int previousState = -1;

void printLogEntry(const LogEntry &entry)
{
    if (debugMode && entry.variablesUpdated)
    {
        Serial.println();
        Serial.println("-------------------------------------------");
        Serial.print("Timestamp: ");
        Serial.print(entry.timestamp);
        Serial.println();
        Serial.print(" | General State: ");
        Serial.print(entry.generalState);
        Serial.print(" | Conveyor State: ");
        Serial.print(entry.conveyorState);
        Serial.println();
        Serial.print("Battery Status: ");
        Serial.print(entry.battery.status);
        Serial.println();
        Serial.print(" | Voltage: ");
        Serial.print(entry.battery.voltage);
        Serial.print(" | Current: ");
        Serial.print(entry.battery.current);
        Serial.print(" | Temperature: ");
        Serial.print(entry.battery.temp);
        Serial.println();
        Serial.println("-------------------------------------------");

        // Reset the flag after printing
        entry.resetUpdatedFlag();
    }
}

#endif // LOG_FUNCTIONS_H
