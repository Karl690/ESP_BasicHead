#pragma once
#include "configure.h"
#ifdef BOARD_T_DISPLAY

#define PIN_POWER_ON                GPIO_NUM_15
#define PIN_HEARTBEAT				GPIO_NUM_38 //LCD_BL

#define HEARTBEAT_SET				gpio_set_level(PIN_HEARTBEAT, 1);
#define HEARTBEAT_CLR				gpio_set_level(PIN_HEARTBEAT, 0);


#define PIN_LCD_RST                  GPIO_NUM_5
#define PIN_LCD_CS                   GPIO_NUM_6
#define PIN_LCD_SCK                   GPIO_NUM_7   
#define PIN_LCD_MOSI                 GPIO_NUM_8   //PIN_LCD_WR
#define PIN_LCD_RS                  GPIO_NUM_9    //PIN_LCD_RD

#define PIN_LCD_BL                   GPIO_NUM_38

#define PIN_LCD_D0                   GPIO_NUM_39
#define PIN_LCD_D1                   GPIO_NUM_40
#define PIN_LCD_D2                   GPIO_NUM_41
#define PIN_LCD_D3                   GPIO_NUM_42
#define PIN_LCD_D4                   GPIO_NUM_45
#define PIN_LCD_D5                   GPIO_NUM_46
#define PIN_LCD_D6                   GPIO_NUM_47
#define PIN_LCD_D7                   GPIO_NUM_48

#define PIN_TOUCH_INT                16
#define PIN_TOUCH_RES                21


#endif // BOARD_T_DISPLAY