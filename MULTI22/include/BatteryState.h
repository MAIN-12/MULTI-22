#include <000 mainSetUp.h>

void BatteryIndicator(byte S1, byte S2, byte S3)
{
    digitalWrite(batteryIndicator1_o, S1);
    digitalWrite(batteryIndicator2_o, S2);
    digitalWrite(batteryIndicator3_o, S3);
}

byte batteryCheck()
{
    int BCP = map(analogRead(battery_i), 100, 1023, 0, 100); // Configure Shunt ranges or implementa a diferent eq if necesary.
    byte BLevel = map(BCP, 0, 80, 0, 100);

    switch (BLevel)
    {
    case 0 ... 25:
        if (millis() - blinkMillis >= blinkInterval)
        {
            digitalWrite(batteryIndicator3_o, !digitalRead(batteryIndicator3_o));
            blinkMillis = millis();
        }
        break;
    case 26 ... 50:
        BatteryIndicator(LOW, LOW, HIGH);
        break;
    case 51 ... 75:
        BatteryIndicator(LOW, HIGH, HIGH);
        break;
    case 76 ... 100:
        BatteryIndicator(HIGH, LOW, HIGH);
        break;
    }
    return BLevel;
}