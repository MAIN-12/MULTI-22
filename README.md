# MULTI-19

## Table of Contents
1. [Description](#description)
2. [Instructions](#instructions)
3. [Version Control](#version-control)

## Description <a name="description"></a>

The provided codebase manages a system responsible for controlling and monitoring various aspects of a conveyor system. It undergoes continuous development and enhancement to ensure smooth operation, reliability, and efficiency.

[REPO](https://github.com/CharlieProjects/MULTI-19)

## Instructions <a name="instructions"></a>
To use this code:

1. Install Visual Studio Code and PlatformIO.
2. Ensure you have either a Controlino micro or a Norvi IoT device available.
3. Modify the board definition in the PlatformIO configuration to match the device you are using.
4. Upload the code to the controller using PlatformIO.
5. Once uploaded, open the serial monitor. If everything l  oads up as expected, you should see the current version of tee code in the serial monitor:


## Version Control Log <a name="version-control"></a>

### Version 3.1.0:
- Code Clean Up
- Fixed bugs of the battery indicator systems
- Organized the documentation of the code
- Reorganized the internal functions architecture

### Version 3.0.4:
- Fixed a bug of the battery indicator causing delay when switching from standby to operation.

### Version 3.0.3:
- Implemented the feature to stop showing the indicator of the battery when in standby mode.

### Version 3.0.2:
- Trafic Light (3 Light) Battery State indicator. 

### Version 3.0.1:
- Implemented the BMS battery lib.
- Battery Telemetry integration.
- 2 Light Battery State indicator

### Version 3.0.0:
- Organized the version 2.0 libraries.
- Optimized the operational functions and internal variables memory usage.
- Pin Layout redefinition.

### Version 2.3.0:
- Implementation of a Shunt battery reader (never tested)
- Optimization of the State Handeler Function.

### Version 2.1.1:
- Fixed bugs cousing inestabilities in the Conveyor State ahndeler. 

### Version 2.1.0:
- Implementation of Breaking Routin functions. (Never implemented in the Real Conveyor)
- Set up the pin Layout to work with the controller COntrolino Mini.

### Version 2.0.3:
- Ambient control variables Temp and Humidity lib install. (Never actually used.)
- Controler Watch dog Function Set Up.
- Implemented Elevation Control functions.

### Version 2.0.2:
- Serial.log function define to debug ESP32 behabior.
- Fix bugs on the LCD print. 

### Version 2.0.1:
- Implementing Norvi LCD Display feedback. 

### Version 2.0.0:
- Implemented the State Machine protocols for conveyor control.
- Set up the pin Layout to work with the controller Norvi IoT using ESP32. 

### Version 1.0.0:
- Implemented Conveyor Control automation.
- Code design to work with Arduino Mega 2560.
- Custom Boar design and pinout. 