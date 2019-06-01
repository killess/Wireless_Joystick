// ------------------------------------------------------------------
// Wireless Joystick Controller
// For use with the Sparkfun Wireless Joystick Kit
// https://www.sparkfun.com/products/14051
//
// Board: Sparkfun SAMD21 Dev Breakout
//
// By Greg Hughes
// 5/27/2019
// ------------------------------------------------------------------

//TODO debounce buttons
//TODO Timer set message rate out (xbee) 

// ------------------------------------------------------------------

#include "Controller.h"
#include "LiPo_Gauge.h"
#include "oled.h"


raw_t raw={0};
com_t com={0};
byte btn;



void setup() 
{
  // Configure serial ports
  SerialUSB.begin(BAUDRATE);  // SerialUSB (Serial monitor)
  Serial1.begin(BAUDRATE);    // Xbee


  // Wait for ports to open
  while(!Serial1);

  // Configure pins
  pinMode(LT_TRIG,INPUT_PULLUP); 
  pinMode(RT_TRIG,INPUT_PULLUP); 
  pinMode(UP_ARROW,INPUT_PULLUP); 
  pinMode(DN_ARROW,INPUT_PULLUP); 
  pinMode(LT_ARROW,INPUT_PULLUP); 
  pinMode(RT_ARROW,INPUT_PULLUP); 
  pinMode(B_JOYSTICK,INPUT_PULLUP); 

  // Battery Gauge
  lipo_init();

  // Display
  oled_init();
}

//----------------------------------------
void loop() 
{
  unsigned char i;

  // Read data
  raw.xAxis = analogRead(X_JOYSTICK);
  raw.yAxis = analogRead(Y_JOYSTICK);
  raw.ltTrig = digitalRead(LT_TRIG);
  raw.rtTrig = digitalRead(RT_TRIG);
  raw.upBtn = digitalRead(UP_ARROW);
  raw.downBtn = digitalRead(DN_ARROW);
  raw.leftBtn = digitalRead(LT_ARROW);
  raw.rightBtn = digitalRead(RT_ARROW);
  raw.joyBtn = digitalRead(B_JOYSTICK);

  // Pack buttons bits
  btn = 0x80;
  btn |= (raw.ltTrig<<6);
  btn |= (raw.rtTrig<<5);
  btn |= (raw.upBtn<<4);
  btn |= (raw.downBtn<<3);
  btn |= (raw.leftBtn<<2);
  btn |= (raw.rightBtn<<1);
  btn |= raw.joyBtn;

  // Create Xbee message out
  i=0;
  com.xbee[i++] = 0xA9;
  com.xbee[i++] = 0x65;
  com.xbee[i++] = highByte(raw.xAxis);
  com.xbee[i++] = lowByte(raw.xAxis);
  com.xbee[i++] = highByte(raw.yAxis);
  com.xbee[i++] = lowByte(raw.yAxis);
  com.xbee[i++] = btn;
  com.xbee[i++] = 0x0D; // CR
  com.xbee[i++] = 0x0A; // LF
  Serial1.write(com.xbee,i); // Send to Xbee

  // Read Battery Gauge
  lipo_read_vCell();
  lipo_read_percent();
  lipo_alert();

  // Display
  oled_display();


  // USB Serial Monitor (Debugging)
  //sprintf(com.usb,"%d %d %d %d %d %d %d %d %d\n\r",raw.xAxis,raw.yAxis,raw.ltTrig,raw.rtTrig,raw.upBtn,raw.downBtn,raw.leftBtn,raw.rightBtn,raw.joyBtn);
  //sprintf(com.usb,"%x %x %x %x %x \n\r",com.xbee[2],com.xbee[3],com.xbee[4],com.xbee[5],com.xbee[6]);
  //sprintf(com.usb,"%d %d %d %d \n\r",lipo.vCell,lipo.soc,lipo.Version,lipo.Alert);
  //SerialUSB.print(com.usb);

  //SerialUSB.print(lipo.Voltage, 2);SerialUSB.println(" V");
  //SerialUSB.print(lipo.Percent, 2);SerialUSB.println(" %"); 
  
  delay(100); // ms

}
