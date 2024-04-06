#ifndef LOG_FUNCTIONS_H
#define LOG_FUNCTIONS_H

struct LogEntry
{
    String codeVersion;      // Code version as a string
    unsigned long timestamp; // Time of the log entry (in milliseconds since start)
    int state;               // State of the conveyor
    int batteryStatus;       // Battery status
    bool hasError;           // Flag indicating if an error occurred
    int errorCode;           // Error code (if an error occurred)
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
    if (debugMode)
    {
        Serial.print("Timestamp: ");
        Serial.println(entry.timestamp);
        Serial.print("State: ");
        Serial.println(entry.state);
        Serial.print("Battery Status: ");
        Serial.println(entry.batteryStatus);
        Serial.print("Has Error: ");
        Serial.println(entry.hasError ? "Yes" : "No");
        if (entry.hasError)
        {
            Serial.print("Error Code: ");
            Serial.println(entry.errorCode);
        }
        Serial.print("Code Version: ");
        Serial.println(entry.codeVersion);
        // Print additional fields if added
    }
}
#endif // LOG_FUNCTIONS_H
