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
int batteryVoltage;

enum BatteryMode
{
  _NORMAL,
  _STAND_BY,
  _CHARGING
};

/**
 * Controls a traffic light by setting the states of its individual LEDs.
 *
 * @param greenState    The state (HIGH/LOW) to set the green LED.
 * @param yellowState   The state (HIGH/LOW) to set the yellow LED.
 * @param redState      The state (HIGH/LOW) to set the red LED.
 * @param greenPin      The pin number of the green LED. Default is batteryGreenLigth_o.
 * @param yellowPin     The pin number of the yellow LED. Default is batteryYellowLigth_o.
 * @param redPin        The pin number of the red LED. Default is batteryRedLigth_o.
 */
void controlTrafficLight(
    byte greenState,
    byte yellowState,
    byte redState,
    byte greenPin = batteryGreenLigth_o,
    byte yellowPin = batteryYellowLigth_o,
    byte redPin = batteryRedLigth_o)
{
  digitalWrite(greenPin, greenState);   // Set the state of the green LED
  digitalWrite(yellowPin, yellowState); // Set the state of the yellow LED
  digitalWrite(redPin, redState);       // Set the state of the red LED
}

/**
 * Updates the traffic light based on the battery voltage level.
 *
 * @param batteryVoltage The voltage level of the battery.
 * @return The input battery voltage.
 */
// updateTrafficLightByVoltage(int batteryVoltage)
int updateTrafficLightByVoltage(int batteryVoltage, BatteryMode mode = _NORMAL)
{
  bool isStandbyMode = (mode == _STAND_BY);
  switch (batteryVoltage)
  {
  case 0 ... 3:

    if ((millis() - blinkMillis >= blinkInterval) && !isStandbyMode)
    {
      controlTrafficLight(LOW, digitalRead(batteryRedLigth_o), !digitalRead(batteryRedLigth_o));
      blinkMillis = millis();
    }
    else
    {
      controlTrafficLight(LOW, LOW, LOW);
    }

    break;
  case 4 ... 39:
    controlTrafficLight(LOW, LOW, HIGH);
    break;

  case 40 ... 42: // Blinking Red

    if (millis() - blinkMillis >= blinkInterval)
    {
      controlTrafficLight(LOW, LOW, !digitalRead(batteryRedLigth_o));
      blinkMillis = millis();
    }

    break;
  case 43 ... 45: // Yellow
    isStandbyMode ? controlTrafficLight(LOW, LOW, LOW) : controlTrafficLight(LOW, HIGH, LOW);
    break;
  case 46 ... 55: // Green
    isStandbyMode ? controlTrafficLight(LOW, LOW, LOW) : controlTrafficLight(HIGH, LOW, LOW);
    break;
  }
  return batteryVoltage;
}

int standByBatteryCheck(int batteryVoltage)
{
  switch (batteryVoltage)
  {
  case 0 ... 42:
    if (millis() - blinkMillis >= blinkInterval)
    {
      controlTrafficLight(LOW, LOW, !digitalRead(batteryRedLigth_o));
      blinkMillis = millis();
    }
    break;

  case 43 ... 100:
    controlTrafficLight(LOW, LOW, LOW);
    break;
  }
  return batteryVoltage;
}

/**
 * Simulates battery indicator testing by controlling traffic light LEDs.
 *
 * @param greenState  The state (HIGH/LOW) of the green LED.
 * @param yellowState The state (HIGH/LOW) of the yellow LED.
 * @param redState    The state (HIGH/LOW) of the red LED.
 * @param duration    The duration (in milliseconds) to maintain the states.
 */
void simulateBatteryIndicator(byte greenState, byte yellowState, byte redState, int duration)
{
  controlTrafficLight(greenState, yellowState, redState);
  delay(duration);
}
/**
 * Tests the battery indicator by simulating different states.
 */
void testBatteryIndicator()
{
  simulateBatteryIndicator(HIGH, LOW, LOW, 1500);
  simulateBatteryIndicator(LOW, HIGH, LOW, 1500);
  simulateBatteryIndicator(LOW, LOW, HIGH, 500);
  simulateBatteryIndicator(LOW, LOW, LOW, 500);
  simulateBatteryIndicator(LOW, LOW, HIGH, 500);
  simulateBatteryIndicator(LOW, LOW, LOW, 500);
  simulateBatteryIndicator(LOW, LOW, HIGH, 500);
  simulateBatteryIndicator(LOW, LOW, LOW, 500);
}

/**
 * Performs a battery check based on the specified mode.
 *
 * @param mode The mode in which the battery check should be performed. Default is _NORMAL.
 *             Possible values are _NORMAL, _STAND_BY, and _CHARGING.
 *             - _NORMAL: Perform a normal battery check.
 *             - _STAND_BY: Perform a battery check in standby mode.
 *             - _CHARGING: Perform a battery check during charging.
 * @return The result of the battery check.
 */
int performBatteryCheck(BatteryMode mode = _NORMAL)
{
  bool isStandbyMode = (mode == _STAND_BY);
  bool shouldForceBatteryCheck = isStandbyMode ? !batteryForceCheck : batteryForceCheck;
  if (shouldForceBatteryCheck || millis() - batteryPreviousMillis >= batteryCheckInterval)
  {
    bms.update();
    batteryPreviousMillis = millis();
    batteryForceCheck = !isStandbyMode;
    batteryVoltage = bms.get.packVoltage;
  }
  return isStandbyMode ? standByBatteryCheck(batteryVoltage) : updateTrafficLightByVoltage(batteryVoltage);
}
int batteryCheck() { return performBatteryCheck(_NORMAL); }
int batteryCheckStandBy() { return performBatteryCheck(_STAND_BY); }

// int batteryCheck()
// {
//   if (batteryForceCheck || millis() - batteryPreviousMillis >= batteryInterval)
//   {
//     batteryPreviousMillis = millis();
//     batteryForceCheck = false;

//     bms.update();
//     batteryVoltage = bms.get.packVoltage;
//   }
//   return updateTrafficLightByVoltage(batteryVoltage);
// }

// int batteryCheckStandBy()
// {
//   if (!batteryForceCheck || millis() - batteryPreviousMillis >= batteryIntervalStandBy)
//   {
//     batteryPreviousMillis = millis();
//     batteryForceCheck = true;

//     bms.update();
//     batteryVoltage = bms.get.packVoltage;
//   }
//   return standByBatteryCheck(batteryVoltage);
// }
#endif // BATTERY_MANAGEMENT_H