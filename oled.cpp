// ------------------------------------------------------------------
// SparkFun Micro OLED Breakout
// https://www.sparkfun.com/products/13003?_ga=2.191788259.859843221.1559402046-314298193.1522812308&_gac=1.250421938.1559402046.EAIaIQobChMI2IbO3cTI4gIViKnICh2JpgmxEAEYASAAEgL6YfD_BwE
//
// Oled Library
// https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/archive/master.zip
// ------------------------------------------------------------------
// Connections:
// Wireless Joystick - OLED
// 3.3V - 3V3
//  GND - GND
// MOSI - SDI
//  SCK - SCK
//  D12 - D/C
//  D11 - RST
//  D10 - CS
// ------------------------------------------------------------------
#include "oled.h"
#include <SPI.h>
#include <SFE_MicroOLED.h>
#include "LiPo_Gauge.h"

MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);
int ledPin = 13;   // This is the pin the led is connected to


// ------------------------------------------------------------------
// Initialize
// ------------------------------------------------------------------
void oled_init(void)
{
  oled.begin();  // Start OLED

  pinMode(ledPin, OUTPUT);

  oled.setFontType(0);  // Set the text to small (10 columns, 6 rows worth of characters)
}

// ------------------------------------------------------------------
// Update the display data
// ------------------------------------------------------------------
void oled_display(void)
{
  oled.clear(PAGE); // clears the screen
  oled.setCursor(0,0);  // move cursor to top left corner
  oled.print(lipo.Percent, 2);
  oled.println(" %\n");
  oled.print(lipo.Voltage, 2);
  oled.println(" V\n\n");
  oled.print("VBAT : ");
  if(lipo.Alert == LOW)
  {
    digitalWrite(ledPin, HIGH);
    oled.print("LOW");
  }
  else
  {
    digitalWrite(ledPin, LOW);
    oled.print("OK");
  }
  oled.display();
  //delay(10); 
}
