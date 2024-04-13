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
5. Once uploaded, open the serial monitor. If everything loads up as expected, you should see the following message in the serial monitor:

==============================================
================== MAIN 12 ===================
========== Multiplo Colombia S.A.S ===========
==============================================

Author: Juan C Botero
Support: https://main12.com/
Version: {current version}


## Version Control Log <a name="description"></a>

### Version 3.1.0:
- Code Clean Up
- Fixed bugs of the battery indicator systems
- Organized the documentation of the code
- Reorganized the internal functions architecture

### Version 3.0.4:
- Fixed a bug of the battery indicator causing delay when switching from standby to operation

### Version 3.0.3:
- Implemented the feature to stop showing the indicator of the battery when in standby mode

### Version 3.0.2:
- Implemented the BMS battery

### Version 3.0.1:
- Implemented BMS reading

### Version 3.0.0:
- Organized the version 2.0 libraries
- Optimized the operational functions and internal variables memory usage

### Version 2.3.0:
- Fixed bugs

### Version 2.2.0:
- Fixed bugs

### Version 2.1.0:
- Implemented Elevation Control functions

### Version 2.0.0:
- Implemented the State Machine protocols for conveyor control

### Version 1.0.0:
- Implemented Conveyor Control automation