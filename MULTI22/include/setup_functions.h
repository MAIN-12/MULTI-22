#ifndef SETUP_FUNCTIONS_H
#define SETUP_FUNCTIONS_H

/********************************************************************************
 * @file        setup_functions.h
 * @author      Juan Carlos Botero
 * @date        04/12/2024
 * @version     2.0.0
 * @brief       Setup function to initialize the system.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************
 */

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
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
