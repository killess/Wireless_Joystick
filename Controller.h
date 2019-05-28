#ifndef __controller_H
#define __controller_H


// Config
#define BUFFER_USB_SIZE   80
#define BUFFER_XBEE_SIZE  10
#define BAUDRATE          9600


// Pin definitions
#define LT_TRIG 6        
#define RT_TRIG 3       
#define UP_ARROW 8
#define DN_ARROW 2
#define LT_ARROW 4
#define RT_ARROW 9
#define X_JOYSTICK A2   
#define Y_JOYSTICK A3  
#define B_JOYSTICK 5



// Custom Types
typedef struct rawData
{
  unsigned int xAxis;
  unsigned int yAxis;
  unsigned char ltTrig;
  unsigned char rtTrig;
  unsigned char upBtn;
  unsigned char downBtn;
  unsigned char leftBtn;
  unsigned char rightBtn;
  unsigned char joyBtn;
}raw_t;

typedef struct comms
{
  unsigned char xbee[BUFFER_XBEE_SIZE];
  char usb[BUFFER_USB_SIZE];
}com_t;


#endif __controller_H
