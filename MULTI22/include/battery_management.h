#ifndef BATTERY_MANAGEMENT_H
#define BATTERY_MANAGEMENT_H

/********************************************************************************
 * @file        battery_management.h
 * @author      Juan Carlos Botero
 * @date        04/12/2024
 * @version     1.0.0
 * @brief       Header file for battery management functions.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************
 */

#include "00_setup_functions.h"
unsigned long batteryPreviousMillis = 0;
int Batteryvoltage;

void TrafficLight(byte pin1, byte pin2, byte pin3, byte S1, byte S2, byte S3)
{
  digitalWrite(pin1, S1);
  digitalWrite(pin2, S2);
  digitalWrite(pin3, S3);
}

int batteryCheck_3ligths(int BCP)
{
  // byte BCP = map(analogRead(voltage), batteryMaxVoltage, batteryMaxVoltage, 0, 100); // Configure Shunt ranges or implementa a diferent eq if necesary.
  switch (BCP)
  {
  case 0 ... 39:
    TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, HIGH);
    break;
  case 40 ... 42:

    if (millis() - blinkMillis >= blinkInterval)
    {
      TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, !digitalRead(batteryRedLigth_o));
      blinkMillis = millis();
    }

    break;
  case 43 ... 45:
    TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, HIGH, LOW);
    break;
  case 46 ... 55:
    TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, HIGH, LOW, LOW);
    break;
  }
  return BCP;
}

int standByBatteryCheck(int BCP)
{
  switch (BCP)
  {
  case 0 ... 39:
    if (millis() - blinkMillis >= blinkInterval)
    {
      TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, !digitalRead(batteryRedLigth_o));
      blinkMillis = millis();
    }
    break;
  case 40 ... 42:

    if (millis() - blinkMillis >= blinkInterval)
    {
      TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, !digitalRead(batteryRedLigth_o));
      blinkMillis = millis();
    }

    break;
  case 43 ... 100:
    TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, LOW);
    break;
  }
  return BCP;
}

byte bateryLightTesting()
{
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, HIGH, LOW, LOW);
  delay(1500);
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, HIGH, LOW);
  delay(1500);
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, LOW);
  delay(500);
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, LOW);
  delay(500);
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth_o, batteryYellowLigth_o, batteryRedLigth_o, LOW, LOW, LOW);
  delay(500);
  return 0;
}
void testBatteryIndicator()
{
  bateryLightTesting();
}

int batteryCheck()
{
  if (batteryForceCheck || millis() - batteryPreviousMillis >= batteryInterval)
  {
    batteryPreviousMillis = millis();
    batteryForceCheck = false;

    bms.update();
    Batteryvoltage = bms.get.packVoltage;
  }
  return batteryCheck_3ligths(Batteryvoltage);
}

int batteryCheckStandBy()
{
  if (!batteryForceCheck || millis() - batteryPreviousMillis >= batteryIntervalStandBy)
  {
    batteryPreviousMillis = millis();
    batteryForceCheck = true;

    bms.update();
    Batteryvoltage = bms.get.packVoltage;
  }
  
  return standByBatteryCheck(Batteryvoltage);
}

// byte performBatteryCheck(unsigned long &previousMillis, unsigned long interval, byte (*checkFunction)(int))
// {
//   if (batteryForceCheck || millis() - previousMillis >= interval)
//   {
//     previousMillis = millis();
//     batteryForceCheck = false;

//     bms.update();
//     int voltage = bms.get.packVoltage;

//     return checkFunction(voltage);
//   }
//   else
//   {
//     return 0;
//   }
// }

// byte batteryCheck()
// {
//   return performBatteryCheck(batteryPreviousMillis, batteryInterval, batteryCheck_3ligths);
// }

// byte batteryCheckStandBy()
// {
//   batteryForceCheck = true;
//   return performBatteryCheck(batteryPreviousMillis, batteryIntervalStandBy, standByBatteryCheck);
// }
#endif // BATTERY_MANAGEMENT_H