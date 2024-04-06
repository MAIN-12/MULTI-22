#ifndef LOG_FUNCTIONS_H
#define LOG_FUNCTIONS_H

struct LogEntry
{
    String codeVersion; // Code version as a string
    int status;
    unsigned long timestamp; // Time of the log entry (in milliseconds since start)
    int state;               // State of the conveyor
    int batteryStatus;       // Battery status
    int errorCode[12];
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
    if (debugMode)
    {
        // Check if the current state is different from the previous state
        if (entry.state != previousState)
        {
            // Print only if the state changes
            Serial.print("Code Version: ");
            Serial.print(entry.codeVersion);
            Serial.print(" | Timestamp: ");
            Serial.print(entry.timestamp);
            Serial.print(" | State: ");
            Serial.println(entry.state);
            Serial.print(" | Battery Status: ");
            Serial.println(entry.batteryStatus);

            previousState = entry.state;
        }
    }
}
#endif // LOG_FUNCTIONS_H
