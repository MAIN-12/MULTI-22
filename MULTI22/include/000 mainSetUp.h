#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
// #include <RTClib.h>
// #include <OneButton.h>
// #include <LoRa.h>
// #include <ESP8266WiFi.h>
// #include <GoldenMotor.h>
// #include <Display.h>

#include <Config.h>
#include <Board_IO.h>

void Main12()
{
    Serial.println();
    Serial.println("===========================================");
    Serial.println("================= MAIN 12 =================");
    Serial.println("========= Multiplo COlombia S.A.S =========");
    Serial.println("===========================================");
    Serial.println();
    Serial.println("Script by: Juan C Botero");
    Serial.print("Version: 3.0.0");
    Serial.println("               [ main12.com ]              ");

    Serial.println();
}

void MainSetUp()
{
    Serial.begin(baudRate);
    while (!Serial)
        ;
    Main12();
}

void MainSetUp(int baud)
{
    Serial.begin(baud);
    while (!Serial)
        ;
    Main12();
}
