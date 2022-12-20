
#include "Arduino.h"

// #include <EEPROM.h>
// #include <Wire.h>
// #include <SPI.h>
#include <Config.h>

// #include <RTClib.h>
// #include <OneButton.h>
// #include <LoRa.h>
// #include <ESP8266WiFi.h>
// #include <GoldenMotor.h>
// #include <Display.h>

void Main12()
{
    Serial.println();
    Serial.println("===========================================");
    Serial.println("================= MAIN 12 =================");
    Serial.println("========= Multiplo Colombia S.A.S =========");
    Serial.println("===========================================");
    Serial.println();
    Serial.println("Script by: Juan C Botero");
    Serial.print("Version: 3.0.0");
    Serial.println("               [ main12.com ]              ");

    Serial.println();
}

void ConveyorBegin()
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

void MainSetUp()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    Main12();

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

void MainSetUp(int baud)
{
    Serial.begin(baud);
    while (!Serial)
        ;
    Main12();
    ConveyorBegin();
}
