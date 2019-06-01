#ifndef __OLED_H
#define __OLED_H



// Pin definitions
#define PIN_RESET 11  // Connect RST to pin 9 (req. for SPI and I2C)
#define PIN_DC    12  // Connect DC to pin 8 (required for SPI)
#define PIN_CS    10  // Connect CS to pin 10 (required for SPI)
#define DC_JUMPER 0


// Prototypes
void oled_init(void);
void oled_display(void);


#endif __OLED_H
