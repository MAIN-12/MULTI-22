#ifndef DISPLAY_HANDELER_H
#define DISPLAY_HANDELER_H

/********************************************************************************
 * @file        display_handeler.h
 * @author      Juan Carlos Botero
 * @date        08/08/2020
 * @version     2.0.0
 * @brief       Header the Oled display for an ESP 32 TTGO board.
 * @license     MIT License
 * @website     https://www.main12.com
 * ******************************************************************************
 */

// #include <SSD1306.h>
#include <SH1106.h>

// ================================== SETTINGS ==================================
// SSD1306 display(0x3c, 5, 4); // display(Adr, SDA, SCL)   GPIO 5 = D1, GPIO 4 = D2
SH1106  display(0x3c, 5, 4); // display(Adr, SDA, SCL)   GPIO 5 = D1, GPIO 4 = D2

#define flipDisplay false

// ================================= FUNCIONES ==================================
void displayBegin(){
  if (flipDisplay)
    display.flipScreenVertically();

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,  0, "===MULTI-19===");
  display.drawString(0, 16, "MultiploColombia");
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 40, "Copyright (c) 2020");
  display.drawString(0, 50, "CARLIE PROJECTS");
  display.display();
  delay(2500);
}
#endif // DISPLAY_HANDELER_H