#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "global.h"
//driver includes
#include "driver/gpio.h"

///////////
#include "gpio/pininit.h"
#include "rcc/rcc.h"
#include "taskmanager.h"

//103012 with spi display
//#define BOARD_103012
#ifdef BOARD_103012
#include "gpio/pinout_103012.h"		
#include "display/ST7789/st7789-103012.h"  //spi lcd interface
#include "display/display.h"
#include "display/gui.h"
#endif 

//T-Display with parallel interface
#define BOARD_T_DISPLAY
#ifdef BOARD_T_DISPLAY
#include "gpio/pinout_T_display.h"	
#include "display/ST7789/st7789-t-display.h" //parallel lcd interface
#include "display/display.h"
#include "display/gui.h"
#endif