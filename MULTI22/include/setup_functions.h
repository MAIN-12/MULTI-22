#ifndef SETUP_FUNCTIONS_H
#define SETUP_FUNCTIONS_H

#include "Arduino.h"
#include <Config.h>

bool debugMode = false;

void printHeader(const String& version) {
    Serial.println();
    Serial.println("===========================================");
    Serial.println("================= MAIN 12 =================");
    Serial.println("========= Multiplo Colombia S.A.S =========");
    Serial.println("===========================================");
    Serial.println();
    Serial.println("Script by: Juan C Botero");
    Serial.print("Version: ");
    Serial.println(version);
    Serial.println("               [ main12.com ]              ");
    Serial.println();
}

void configureConveyorPins()
{
    for (byte i = 0; i < sizeof(DIGITAL_INPUTS); i++)
    {
        pinMode(DIGITAL_INPUTS[i], INPUT);
    }
    for (byte i = 0; i < sizeof(DIGITAL_OUTPUTS); i++)
    {
        pinMode(DIGITAL_OUTPUTS[i], OUTPUT);
        digitalWrite(DIGITAL_OUTPUTS[i], LOW);
    }
}

void setupMain(int baud = 9600)
{
    Serial.begin(baud);
    while (!Serial);
    // printHeader();
    configureConveyorPins();
    initializeBMSviaSerial();
}

#endif // SETUP_FUNCTIONS_H
