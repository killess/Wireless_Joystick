// ------------------------------------------------------------------
//  1-Cell Fuel Gauge for lithium-ion
//  ModelGauge and Low-Battery Alert
//
//  Part# MAX17043
// ------------------------------------------------------------------

#include <arduino.h>
#include "LiPo_Gauge.h"
#include <Wire.h>


lipo_t lipo={0};

unsigned int i2c_read16(regs_t reg);
void i2c_write16(regs_t reg, unsigned int data);


// ------------------------------------------------------------------
// Initialize
// ------------------------------------------------------------------
void lipo_init(void)
{
  byte percentBits;
  
  // Configure pin
  pinMode(BATT_ALERT, INPUT_PULLUP);

  // I2C
  Wire.begin();  // Master

  // Chip Version
  lipo.Version = i2c_read16(VERSION);  

  // Set alarm
  // Threshold 5-bits, Lsb = 1%, 1% to 32% in two's comp
  // Ex. 00000=32%, 00001=31%, 11111=1%
  if(ALARM_PERCENT > 32)
    percentBits = 0;
  else
    percentBits = 32 - ALARM_PERCENT;
  i2c_write16(CONFIG,(COMPENSATION | percentBits));

  // Restart fuel gauge
  i2c_write16(MODE,QUICK_START);  

}


// ------------------------------------------------------------------
// Read 16 bits data to 8-bit address and the next
// ------------------------------------------------------------------
unsigned int i2c_read16(regs_t reg)
{
  int data = 0;

  Wire.beginTransmission(ADR);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(ADR, 2);
  while (Wire.available() < 2);
  data = ((int) Wire.read()) << 8;
  data |= Wire.read();
  return data;
}


// ------------------------------------------------------------------
// Writes 16 bits data to 8-bit address and the next
// ------------------------------------------------------------------
void i2c_write16(regs_t reg, unsigned int data)
{
  Wire.beginTransmission(ADR);
  Wire.write(reg);
  Wire.write((byte)((data >> 8) & 0x00FF));
  Wire.write((byte)(data & 0x00FF));
  Wire.endTransmission();
}

// ------------------------------------------------------------------
// Read battery voltage
// Cell voltage over 0 to 5V, 12-bit ADC measurement
// 1.25mV / count
// ------------------------------------------------------------------
float lipo_read_vCell(void)
{
  lipo.vCell = i2c_read16(VCELL);
  lipo.vCell >>= 4;  

  // vcell reports battery in 1.25mV increments
  lipo.Voltage = (float)lipo.vCell * CNT2V;

  //SerialUSB.print(lipo.Voltage, 2); 
  return lipo.Voltage;
}

  
// ------------------------------------------------------------------
// Read Precent of battery, base on State of charge (SOC)
// High byte units of 1%, low byte units 1/256%
// ------------------------------------------------------------------
float lipo_read_percent(void)
{
  lipo.soc = i2c_read16(SOC);  
  lipo.Percent = (byte) (lipo.soc >> 8);  
  lipo.Percent += ((float)((byte)lipo.soc))/256;  // Low byte is 1/256%

  //SerialUSB.print(lipo.Percent, 2);
  return lipo.Percent;
}


// ------------------------------------------------------------------
// Read Alert pin status
// ------------------------------------------------------------------
byte lipo_alert(void)
{
  lipo.Alert = digitalRead(BATT_ALERT);
  return lipo.Alert;
}
