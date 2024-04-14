# MULTI-19

[REPO](https://github.com/MAIN-12/MULTI-22)

## Description <a name="description"></a>

Our codebase is meticulously crafted to manage and monitor various aspects of our conveyor system. With a focus on continuous improvement, we ensure seamless operations, reliability, and efficiency.

This program serves as the central control structure for the CONVEYOR MULTI-22, developed by Multiplo Colombia S.A.S. It is designed to be compiled using Visual Studio Code with the PlatformIO plugin. The code is self-contained, comprising all necessary external libraries located in the "lib" folder, along with auxiliary functions and reusable resources in the "include" folder.

The programming architecture is founded on object-oriented finite state machines. For detailed documentation on the architecture, please refer to the accompanying documentation within the project folder or reach out directly to Main12 LLC.

![System Diagram](https://juancbotero.com/wp-content/uploads/2023/07/IMG_20191229_184527-1024x484.jpg)


## Table of Contents
1. [Description](#description)
2. [Key Features](#key-features)
3. [Getting Started](#getting-started)
4. [Instructions](#instructions)
5. [Documentation](#documentation)
6. [Version Control](#version-control)


## Key Features <a name="key-features"></a>
- **Comprehensive Control:** Regulate and oversee the entire conveyor system with precision.
- **Reliability:** Built to withstand rigorous industrial environments, ensuring uninterrupted operations.
- **Efficiency:** Optimized performance to enhance productivity and streamline processes.

## Getting Started <a name="getting-started"></a>
1. **Compilation:** Use Visual Studio Code with the PlatformIO plugin for easy compilation.
2. **Self-contained:** All necessary external libraries are included in the 'lib' folder.
3. **Architecture:** Built upon object-oriented finite state machines for efficient control.


## Instructions <a name="instructions"></a>
To use this code:

1. Install Visual Studio Code and PlatformIO.
2. Ensure you have either a Controlino micro or a Norvi IoT device available.
3. Modify the board definition in the PlatformIO configuration to match the device you are using on the config.h file.
4. Upload the code to the controller using PlatformIO Upload.
5. Once uploaded, open the serial monitor. If everything l  oads up as expected, you should see the current version of tee code in the serial monitor:

## Documentation <a name="documentation"></a>
For detailed documentation on the code architecture and usage, refer to the enclosed documentation within the project folder or reach out directly to Main12 LLC. at:
 - admin@main12.com 
 - https://main12.com/contact-us/

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