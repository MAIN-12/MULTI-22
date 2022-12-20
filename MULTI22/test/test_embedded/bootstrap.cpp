#include <Arduino.h>
#include <unity.h>


void setup()
{
    Serial.begin(115200);
    delay(1000);

    UNITY_BEGIN();
    RUN_TEST();

    UNITY_END();
}

void loop()
{
    
}