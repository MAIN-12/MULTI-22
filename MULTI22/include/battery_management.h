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

#include "setup_functions.h"

void dualWrite(byte pin1, byte pin2, byte S1, byte S2)
{
  digitalWrite(pin1, S1);
  digitalWrite(pin2, S2);
}

void TrafficLight(byte pin1, byte pin2, byte pin3, byte S1, byte S2, byte S3)
{
  digitalWrite(pin1, S1);
  digitalWrite(pin2, S2);
  digitalWrite(pin3, S3);
}

byte batteryCheck_3ligths(int BCP)
{
  // byte BCP = map(analogRead(voltage), batteryMaxVoltage, batteryMaxVoltage, 0, 100); // Configure Shunt ranges or implementa a diferent eq if necesary.
  switch (BCP)
  {
  case 0 ... 39:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
    break;
  case 40 ... 42:

    if (millis() - blinkMillis >= blinkInterval)
    {
      TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, !digitalRead(batteryRedLigth));
      blinkMillis = millis();
    }

    break;
  case 43 ... 45:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, HIGH, LOW);
    break;
  case 46 ... 55:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, HIGH, LOW, LOW);
    break;
  }
  return BCP;
}

byte standByBatteryCheck(int BCP)
{
  switch (BCP)
  {
  case 0 ... 39:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
    break;
  case 40 ... 42:

    if (millis() - blinkMillis >= blinkInterval)
    {
      TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, !digitalRead(batteryRedLigth));
      blinkMillis = millis();
    }

    break;
  case 43 ... 100:
    TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, LOW);
    break;
  }
  return BCP;
}

byte bateryLightTesting()
{
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, HIGH, LOW, LOW);
  delay(1500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, HIGH, LOW);
  delay(1500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, LOW);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, LOW);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, HIGH);
  delay(500);
  TrafficLight(batteryGreenLigth, batteryYellowLigth, batteryRedLigth, LOW, LOW, LOW);
  delay(500);
  return 0;
}
void testBatteryIndicator()
{
  bateryLightTesting();
}


byte batteryCheck()
{
  // Check if it's time to run the function
  if (!batteryForceCheck && millis() - batteryPreviousMillis >= bateryInterval)
  {
    batteryPreviousMillis = millis();

    bms.update();
    float voltage = bms.get.packVoltage;
    byte BCP = int(voltage);

    return batteryCheck_3ligths(int(voltage));
  }
  else
  {
    return 0;
  }
}

byte batteryCheckStandBy()
{
  batteryForceCheck = true;
  if (!batteryForceCheck && millis() - batteryPreviousMillis >= bateryIntervalStandBy)
  {
    batteryPreviousMillis = millis();

    bms.update();
    float voltage = bms.get.packVoltage;
    byte BCP = int(voltage);

    return standByBatteryCheck(int(voltage));
  }
  else
  {
    return 0;
  }
}


// byte performBatteryCheck(unsigned long &previousMillis, unsigned long interval, byte (*checkFunction)(int))
// {
//   if (!batteryForceCheck && millis() - previousMillis >= interval)
//   {
//     previousMillis = millis();
//     batteryForceCheck = false;

//     bms.update();
//     float voltage = bms.get.packVoltage;
//     byte BCP = int(voltage);

//     return checkFunction(int(voltage));
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
#endif