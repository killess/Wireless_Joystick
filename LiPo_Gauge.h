#ifndef __LiPo_H
#define __LiPo_H

#include <arduino.h>

// Config
#define ALARM_PERCENT  10 // %  [1-32]

// General
#define COMPENSATION   0x9700
#define QUICK_START    0x4000
#define CNT2VOLT       0.001221f

// I2C
#define ADR       0x36

// Pin definitions
#define BATT_ALERT 7




// Chip Register Addresses
typedef enum LiPo_regs
{
  VCELL   = 0x02, // Reports 12-bit A/D measurement of battery voltage 
  SOC     = 0x04, // Reports 16-bit SOC result calculated by ModelGauge algorithm
  MODE    = 0x06, // Sends special commands to the IC
  VERSION = 0x08, // Returns IC version
  CONFIG  = 0x0C, // Battery compensation,  Default: 0x971C
  COMMAND = 0xFE, // Sends special commands to the IC
}regs_t;

typedef struct LiPo_data
{
  float Voltage;
  float Percent;
  unsigned char  Alert; 
  unsigned int   vCell;
  unsigned int   soc;
  unsigned int   Version;
}lipo_t;
extern lipo_t lipo;

// Prototypes
void lipo_init(void);
float lipo_read_vCell(void);
float lipo_read_percent(void);
byte lipo_alert(void);

#endif __LiPo_H
