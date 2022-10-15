
#include "Arduino.h"
#include <Config.h>

void Main12()
{
    Serial.println();
    Serial.println("===========================================");
    Serial.println("================= MAIN 12 =================");
    Serial.println("========= Multiplo COlombia S.A.S =========");
    Serial.println("===========================================");
    Serial.println();
    Serial.println("Script by: Juan C Botero");
    Serial.printf("Version: %d", version);
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
