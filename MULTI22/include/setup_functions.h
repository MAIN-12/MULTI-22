#ifndef SETUP_FUNCTIONS_H
#define SETUP_FUNCTIONS_H

#include "Arduino.h"
#include <Config.h>

#ifdef Debug_Mode
bool debugMode = true;
#else
bool debugMode = false;
#endif

void printHeader()
{
    Serial.println();
    Serial.println("===========================================");
    Serial.println("================= MAIN 12 =================");
    Serial.println("========= Multiplo Colombia S.A.S =========");
    Serial.println("===========================================");
    Serial.println();
    Serial.println("Author: Juan C Botero");
    Serial.println("Support: https://main12.com/");
    Serial.print("Version: ");
    Serial.println(version);
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
    while (!Serial)
        ;
    printHeader();
    configureConveyorPins();
    initializeBMSviaSerial();
}

#endif // SETUP_FUNCTIONS_H
