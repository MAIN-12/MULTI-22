/* ==============================================================================
 * Script by: Juan Carlos Botero 
 * Date: 08/23/2020
 * Version: 1.0.0
 * ==============================================================================
 *                      Copyright (c) 2020 CHARLIE PROJECTS                      
 *                      github.com/CharlieProjects/MULTI-19                      
 * ==============================================================================
 * =======================  GOLDEN MOTOR FOC CONTROLLER  ========================
 * ==============================================================================
 * MIT license. See LICENSE file in the project root for full license information
 */

#ifndef GoldenMotor_h
#define GoldenMotor_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**************************************************************************/
/*!
    @brief  Simple general-purpose date/time class (no TZ / DST / leap
            seconds).

    This class stores date and time information in a broken-down form, as a
    tuple (year, month, day, hour, minute, second). The day of the week is
    not stored, but computed on request. The class has no notion of time
    zones, daylight saving time, or
    [leap seconds](http://en.wikipedia.org/wiki/Leap_second): time is stored
    in whatever time zone the user chooses to use.

    The class supports dates in the range from 1 Jan 2000 to 31 Dec 2099
    inclusive.
*/
/**************************************************************************/
class GoldenMotor
{
public:
    // void GoldenMotor(byte throttle, byte brake, byte highBrake, byte reverse, byte speedCruise);
    // void begin();
    

    /*! @brief  Test for the lib compatibility.*/
    // void test();

private:
};
#endif