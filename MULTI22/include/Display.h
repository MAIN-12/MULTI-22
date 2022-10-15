/* ==============================================================================
 * Script by: Juan Carlos Botero 
 * Date: 08/08/2020
 * Version: 2.0.0
 * ==============================================================================
 *                      Copyright (c) 2020 Charlie Projects                      
 *                      github.com/CharlieProjects/MULTI-19                      
 * ==============================================================================
 * ========================  CONVEYOR MULTI-19 DISPLAY  =========================
 * ========================   Multiplo Colombia S.A.S.  =========================
 * ==============================================================================
 *  MIT License
 *
 * Copyright (c) 2020 CHARLIE PROJECTS
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
